// Runs one TreeLevel job with Pythia compiled to WebAssembly — the page side of the iPad's Pythia module.
//
//   const r = await TreeLevelPythiaRunner.run({
//     base: "./",                       // where treelevel-pythia-web.js, .wasm and the packs are served
//     job: jobJSONText,                 // job.json, as TreeLevel writes it
//     files: { "events.lhe": text },    // other files of the job folder, if any
//     part: "beams", seedOffset: 0,     // as the engine passes them (a machine is drawn in two parts)
//     hadrons: false,                   // true: mount the parton densities too (53 MB)
//   });
//   r.code, r.hepmc, r.stdout, r.stderr, r.seconds
//
// Each job gets a fresh instance of the module: Pythia keeps global state, and a clean start is what the native
// driver has too. The packs are fetched once and kept.
(function (global) {
  "use strict";
  var packs = {};

  function loadPack(url) {
    if (!packs[url]) {
      packs[url] = fetch(url).then(function (r) {
        if (!r.ok) throw new Error("pack " + url + " : " + r.status);
        return r.arrayBuffer();
      }).then(function (buf) {
        var n = new DataView(buf).getUint32(0, true);
        var manifest = JSON.parse(new TextDecoder().decode(new Uint8Array(buf, 4, n)));
        return { buf: buf, base: 4 + n, manifest: manifest };
      });
    }
    return packs[url];
  }

  function mount(FS, pack) {
    pack.manifest.forEach(function (e) {
      var dir = e.path.substring(0, e.path.lastIndexOf("/"));
      FS.mkdirTree(dir);
      FS.writeFile(e.path, new Uint8Array(pack.buf, pack.base + e.offset, e.size));
    });
  }

  async function run(options) {
    var base = options.base || "./";
    var wanted = [base + "leptons.pack"];
    if (options.hadrons) wanted.push(base + "pdfdata.pack");
    var loaded = await Promise.all(wanted.map(loadPack));
    var stdout = "", stderr = "";
    var started = performance.now();
    var module = await global.TreeLevelPythia({
      locateFile: function (p) { return base + p; },
      print: function (s) { stdout += s + "\n"; },
      printErr: function (s) { stderr += s + "\n"; },
      preRun: [function (m) {
        loaded.forEach(function (p) { mount(m.FS, p); });
        m.FS.mkdirTree("/job");
        m.FS.writeFile("/job/job.json", options.job);
        Object.keys(options.files || {}).forEach(function (name) { m.FS.writeFile("/job/" + name, options.files[name]); });
        m.FS.chdir("/job");
        m.ENV.PYTHIA8DATA = "/pythia/xmldoc";
      }],
    });
    var args = ["--job", "job.json", "--out", "events.hepmc"];
    if (options.part) args.push("--part", options.part, "--seed-offset", String(options.seedOffset || 0));
    var code;
    try { code = module.callMain(args); }
    catch (e) { code = (e && typeof e.status === "number") ? e.status : -1; if (code === -1) stderr += String(e) + "\n"; }
    var hepmc = null;
    try { hepmc = module.FS.readFile("/job/events.hepmc", { encoding: "utf8" }); } catch (e) {}
    return { code: code, hepmc: hepmc, stdout: stdout, stderr: stderr, seconds: (performance.now() - started) / 1000 };
  }

  global.TreeLevelPythiaRunner = { run: run };
})(typeof window !== "undefined" ? window : globalThis);
