// Runs one TreeLevel job with Pythia compiled to WebAssembly — the page side of the iPad's Pythia module.
//
//   const r = await TreeLevelPythiaRunner.run({
//     base: "./",                       // where treelevel-pythia-web.js, .wasm and the packs are served
//     job: jobJSONText,                 // job.json, as TreeLevel writes it
//     files: { "events.lhe": text },    // other files of the job folder, if any
//     part: "beams", seedOffset: 0,     // as the engine passes them (a machine is drawn in two parts)
//     hadrons: false,                   // true: mount the parton densities too (53 MB)
//   });
//   r.code, r.hepmc, r.stdout, r.stderr, r.seconds     (options.bytes : r.hepmcBytes, un Uint8Array, à la place de r.hepmc)
//
// options.onProgress(fraction), facultatif : le pilote dit où il en est (lignes « progress n N » de sa sortie
// d'erreur, demandées par TREELEVEL_PROGRESS) ; elles vont à onProgress et pas au journal. Un lanceur dans un
// Web Worker les fait suivre à la page pendant que Pythia tourne.
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
      printErr: function (s) {
        var p = /^progress (\d+) (\d+)$/.exec(s);
        if (p) { if (options.onProgress && +p[2] > 0) options.onProgress(+p[1] / +p[2]); return; }
        stderr += s + "\n";
      },
      preRun: [function (m) {
        loaded.forEach(function (p) { mount(m.FS, p); });
        m.FS.mkdirTree("/job");
        m.FS.writeFile("/job/job.json", options.job);
        Object.keys(options.files || {}).forEach(function (name) { m.FS.writeFile("/job/" + name, options.files[name]); });
        m.FS.chdir("/job");
        m.ENV.PYTHIA8DATA = "/pythia/xmldoc";
        if (options.onProgress) m.ENV.TREELEVEL_PROGRESS = "1";
      }],
    });
    var args = options.plan ? ["--job", "job.json", "--plan"] : ["--job", "job.json", "--out", "events.hepmc"];
    if (options.part) args.push("--part", options.part, "--seed-offset", String(options.seedOffset || 0));
    var code;
    try { code = module.callMain(args); }
    catch (e) { code = (e && typeof e.status === "number") ? e.status : -1; if (code === -1) stderr += String(e) + "\n"; }
    // options.bytes : le fichier tel quel, en octets, sans le décoder — quelques milliers d'événements pp font des
    // centaines de Mo, et leur chaîne JavaScript (deux octets par caractère) dépassait ce qu'un iPad tient.
    var hepmc = null, hepmcBytes = null;
    try {
      if (options.bytes) hepmcBytes = module.FS.readFile("/job/events.hepmc");
      else hepmc = module.FS.readFile("/job/events.hepmc", { encoding: "utf8" });
    } catch (e) {}
    return { code: code, hepmc: hepmc, hepmcBytes: hepmcBytes, stdout: stdout, stderr: stderr, seconds: (performance.now() - started) / 1000 };
  }

  // Le résumé sur les octets : les lignes « E » comptées, et le dernier GenCrossSection lu dans la fin du fichier.
  function summaryOfBytes(bytes) {
    if (!bytes || !bytes.length) return null;
    var events = 0;
    for (var i = 0; i + 2 < bytes.length; i++) {
      if (bytes[i] === 10 && bytes[i + 1] === 69 && bytes[i + 2] === 32) events++;
    }
    if (bytes[0] === 69 && bytes[1] === 32) events++;
    var tail = new TextDecoder().decode(bytes.subarray(Math.max(0, bytes.length - 262144)));
    var all = tail.match(/^A 0 GenCrossSection .*/gm);
    if (!events || !all) return null;
    var f = all[all.length - 1].split(/\s+/);
    return { events: events, sigma: +f[3], error: +f[4] };
  }

  // Comme le moteur : le nombre d'événements et la section efficace du dernier attribut GenCrossSection, en pb —
  // la ligne « written … sigma = … mb » du pilote n'en garde que quatre chiffres.
  function summary(hepmc) {
    if (!hepmc) return null;
    var events = (hepmc.match(/^E /gm) || []).length;
    var all = hepmc.match(/^A 0 GenCrossSection .*/gm);
    if (!events || !all) return null;
    var f = all[all.length - 1].split(/\s+/);
    return { events: events, sigma: +f[3], error: +f[4] };
  }

  function split(text) {
    var lines = text.split("\n"), header = [], events = [];
    for (var i = 0; i < lines.length; i++) {
      var l = lines[i].replace(/[\r ]+$/, "");
      if (l.indexOf("END_EVENT_LISTING") >= 0) break;
      if (l.lastIndexOf("E ", 0) === 0) events.push([]);
      (events.length ? events[events.length - 1] : header).push(l);
    }
    return { header: header, events: events };
  }

  // Deux échantillons réunis comme le moteur C++ les réunit (Backends/engine, merge) : de chacun la part que sa
  // section efficace lui vaut, ou la moitié à parts égales, pris à tour de rôle ; les poids suivent.
  function merge(a, b, wanted, sa, sb, equal) {
    var A = split(a), B = split(b).events, total = sa.sigma + sb.sigma, fromA, fromB;
    if (equal) { fromA = Math.min(Math.floor(wanted / 2), A.events.length); fromB = Math.min(wanted - fromA, B.length); }
    else {
      fromA = Math.max(0, Math.min(Math.floor(wanted * sa.sigma / total + 0.5), A.events.length));
      fromB = Math.max(0, Math.min(wanted - fromA, B.length));
    }
    var wA = fromA > 0 ? sa.sigma / fromA * (fromA + fromB) / total : 1;
    var wB = fromB > 0 ? sb.sigma / fromB * (fromA + fromB) / total : 1;
    var err = Math.sqrt(sa.error * sa.error + sb.error * sb.error);
    var out = A.header.slice(), takenA = 0, takenB = 0, n = 0;
    while (takenA < fromA || takenB < fromB) {
      var takeA = takenA < fromA && (takenB >= fromB || takenA / fromA <= takenB / fromB);
      var ev = takeA ? A.events[takenA++] : B[takenB++], w = takeA ? wA : wB;
      ev.forEach(function (line) {
        if (line.lastIndexOf("E ", 0) === 0) { var f = line.split(/\s+/); out.push("E " + n + " " + f[2] + " " + f[3]); }
        else if (line.lastIndexOf("W ", 0) === 0) out.push("W " + w.toExponential(10));
        else if (line.lastIndexOf("A 0 GenCrossSection", 0) === 0) out.push("A 0 GenCrossSection " + total.toExponential(10) + " " + err.toExponential(10) + " -1 -1");
        else out.push(line);
      });
      n += 1;
    }
    out.push("HepMC::Asciiv3-END_EVENT_LISTING");
    return { hepmc: out.join("\n") + "\n", events: n, sigma: total, error: err };
  }

  // Un travail entier, comme le moteur le mène : le plan du pilote, une ou deux parties, leur réunion.
  // Rend { ok, message, hepmc, events, sigma (pb), error (pb), log, seconds }.
  async function runJob(options) {
    var started = performance.now(), log = "";
    var job = JSON.parse(options.job);
    var beams = (job.hardProcess && job.hardProcess.beams) || [];
    var hadrons = beams.some(function (b) { return Math.abs(b) > 100; });
    var planRun = await run({ base: options.base, job: options.job, files: options.files, plan: true });
    var plan;
    try { plan = JSON.parse(planRun.stdout.trim().split("\n").pop()); }
    catch (e) { return { ok: false, message: "le pilote n'a pas su lire le travail : " + (planRun.stderr || planRun.stdout).slice(-300), log: planRun.stderr }; }
    if (plan.objection) return { ok: false, message: plan.objection, log: "" };
    var results = [];
    for (var i = 0; i < plan.parts.length; i++) {
      var part = plan.parts[i];
      var report = options.onProgress ? (function (k, n) {
        return function (f) { options.onProgress((k + f) / n); };
      })(i, plan.parts.length) : null;
      // Une seule partie et options.bytes : le résultat reste en octets de bout en bout. Deux parties se
      // réunissent événement par événement, sur le texte.
      var asBytes = !!options.bytes && plan.parts.length === 1;
      var r = await run({ base: options.base, job: options.job, files: options.files, hadrons: hadrons,
                          part: part || null, seedOffset: i, onProgress: report, bytes: asBytes });
      log += (part ? "=== " + part + "\n" : "") + r.stdout + r.stderr;
      var s = asBytes ? summaryOfBytes(r.hepmcBytes) : summary(r.hepmc);
      if (r.code !== 0 || !(r.hepmc || r.hepmcBytes) || !s) {
        return { ok: false, message: "Pythia s'est arrêté (code " + r.code + ")" + (part ? " sur la partie « " + part + " »" : ""), log: log };
      }
      results.push({ hepmc: r.hepmc, hepmcBytes: r.hepmcBytes, summary: s });
    }
    var seconds = (performance.now() - started) / 1000;
    if (results.length === 1) {
      var only = results[0];
      return { ok: true, hepmc: only.hepmc, hepmcBytes: only.hepmcBytes, events: only.summary.events, sigma: only.summary.sigma,
               error: only.summary.error, log: log, seconds: seconds };
    }
    var m = merge(results[0].hepmc, results[1].hepmc, job.events || results[0].summary.events,
                  results[0].summary, results[1].summary, !!(job.hardProcess && job.hardProcess.mixEqualShares));
    return { ok: true, hepmc: m.hepmc, events: m.events, sigma: m.sigma, error: m.error, log: log, seconds: seconds };
  }

  global.TreeLevelPythiaRunner = { run: run, runJob: runJob };
})(typeof window !== "undefined" ? window : globalThis);
