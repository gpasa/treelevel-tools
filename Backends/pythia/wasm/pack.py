#!/usr/bin/env python3
"""Packs Pythia's data folders into one file the WebAssembly module mounts in memory.

    pack.py leptons.pack  share/Pythia8/xmldoc@/pythia/xmldoc  share/Pythia8/tunes@/pythia/tunes  …

Format: a 4-byte little-endian length, a UTF-8 JSON manifest [{"path", "offset", "size"}], then the files one
after the other. runner.js reads it with one fetch and writes each file into Emscripten's file system. Two packs
rather than one: the leptons need 5 MB, the parton densities of the hadrons add 53 MB, fetched only when a beam
is a hadron.
"""
import json, os, struct, sys

out, specs = sys.argv[1], sys.argv[2:]
entries, blobs, offset = [], [], 0
for spec in specs:
    source, mount = spec.split("@", 1)
    for root, _, files in os.walk(source):
        for name in sorted(files):
            if name.startswith("."):
                continue
            full = os.path.join(root, name)
            data = open(full, "rb").read()
            path = mount + "/" + os.path.relpath(full, source).replace(os.sep, "/")
            entries.append({"path": path, "offset": offset, "size": len(data)})
            blobs.append(data)
            offset += len(data)
manifest = json.dumps(entries, separators=(",", ":")).encode()
with open(out, "wb") as f:
    f.write(struct.pack("<I", len(manifest)))
    f.write(manifest)
    for b in blobs:
        f.write(b)
print(f"{out}: {len(entries)} fichiers, {offset / 1e6:.1f} Mo")
