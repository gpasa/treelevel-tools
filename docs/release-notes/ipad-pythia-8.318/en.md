Pythia 8 compiled to WebAssembly, with the common driver of TreeLevel Tools. TreeLevel on iPad downloads it
from this page, file by file, and checks each one against a fingerprint fixed in the app; it runs it
in a web view, without sending anything anywhere. Events come out of it showered and hadronised, and
TreeLevel's Machine source becomes available on iPad.

| file | role |
|---|---|
| `treelevel-pythia-web.wasm`, `.js` | Pythia 8.318 and the driver, in WebAssembly |
| `runner.js` | runs a TreeLevel job: plan, parts, merge |
| `leptons.pack` | Pythia data (xmldoc, tunes, setups) — lepton beams |
| `pdfdata.pack` | parton densities — hadron beams, optional |
| `pythia8318-sources.tgz` | the sources of Pythia 8.318, as published on pythia.org |
| `COPYING.pythia8` | the Pythia licence (GPL v2 or later) |

### Pythia 8, its authors

Pythia 8 is © Torbjörn Sjöstrand and the Pythia collaboration — [pythia.org](https://pythia.org) — and distributed
under GPL v2 or later. All the physics of this module is theirs. If you publish a result obtained with it,
cite: C. Bierlich et al., “A comprehensive guide to the physics and usage of PYTHIA 8.3”,
*SciPost Phys. Codebases* 8 (2022), [arXiv:2203.11601](https://arxiv.org/abs/2203.11601).

The other generators driven by TreeLevel Tools, and their authors:
[CREDITS.md](https://github.com/gpasa/treelevel-tools/blob/1.3-dev/CREDITS.md).
It remains a program separate from TreeLevel: the app hands it a job and reads back the result. The sources of the
driver and of `runner.js` are in this repository, at this release's tag (`Backends/pythia`).
Checksums in `SHA256SUMS.txt`.
