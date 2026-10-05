Module version: **$MODULE** — Pythia **$PYTHIA_VERSION**, compiled to WebAssembly with the common driver of
TreeLevel Tools $MODULE. This page always keeps the same name: TreeLevel on iPad (1.4 and later) takes the latest
version from it, reads its number in `module.json` and shows it in its settings, offers the update when a newer
version is published, and checks every file against the fingerprint that `module.json` gives for it. It runs the
module in a web view, without sending anything anywhere.

What this module can do: `$FEATURES`. "spacetime": placing partons and hadrons in the interaction zone, which
TreeLevel shows at the femtometre.

| file | role |
|---|---|
| `module.json` | version of the module and of Pythia, what it can do, the fingerprint of every file |
| `treelevel-pythia-web.wasm`, `.js` | Pythia $PYTHIA_VERSION and the driver, in WebAssembly |
| `runner.js` | runs a TreeLevel job: plan, parts, merge |
| `leptons.pack` | Pythia data (xmldoc, tunes, setups) — lepton beams |
| `pdfdata.pack` | parton densities — hadron beams, optional |
| `$SOURCES` | the sources of Pythia $PYTHIA_VERSION, as published on pythia.org |
| `COPYING.pythia8` | the Pythia licence (GPL v2 or later) |

TreeLevel 1.3 on iPad downloads its module from
[ipad-pythia-8.318](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia-8.318), whose fingerprints it
fixes: that page does not change.

**Pythia 8 and its authors.** Pythia 8 is © Torbjörn Sjöstrand and the Pythia collaboration —
[pythia.org](https://pythia.org) — and distributed under the GPL v2 or later. All the physics of this module is
theirs. If you publish a result obtained with it, cite: C. Bierlich et al., "A comprehensive guide to the physics
and usage of PYTHIA 8.3", *SciPost Phys. Codebases* 8 (2022), [arXiv:2203.11601](https://arxiv.org/abs/2203.11601).
The other generators driven by TreeLevel Tools, and their authors:
[CREDITS.md](https://github.com/gpasa/treelevel-tools/blob/main/CREDITS.md).

It remains a program separate from TreeLevel: the app hands it a job and reads back the result. The sources of the
driver and of `runner.js` are in this repository (`Backends/pythia`), at the tag `ipad-pythia-module-$MODULE`.
Checksums in `SHA256SUMS.txt`.
