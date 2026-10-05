The event generators of [TreeLevel](https://treelevel.pasahome.org), on your machine. TreeLevel writes a job into a
local folder; this program hands it to **Pythia 8**, **Herwig 7**, **Sherpa 3**, **WHIZARD 3** or **CalcHEP 3** —
shower and hadronisation of its events, or whole collisions of a machine — and writes the result back in HepMC3,
which TreeLevel reads. Nothing goes over the network, no account, no service. On iPad, Pythia 8 compiled to
WebAssembly plays the same part, downloaded from [its release](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia).

It is distributed separately because these generators are under the **GPL**: this repository is GPL v3, and
TreeLevel contains none of their code.

| system | download | what it contains |
|---|---|---|
| **macOS** 13 or later, Apple Silicon and Intel | [TreeLevelTools-0.5.0.dmg](https://github.com/gpasa/treelevel-tools/releases/download/mac-0.5.0/TreeLevelTools-0.5.0.dmg) | Pythia 8, Herwig 7, Sherpa 3 and CalcHEP 3, ready to run |
| **Windows** 10 and 11 | [x64](https://github.com/gpasa/treelevel-tools/releases/download/win-0.5.1/TreeLevelTools-0.5.1-x64.zip) · [ARM64](https://github.com/gpasa/treelevel-tools/releases/download/win-0.5.1/TreeLevelTools-0.5.1-arm64.zip) | Pythia 8; the others through the Docker image |
| **iPad** | from TreeLevel's settings ([the release](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia)) | Pythia 8 in WebAssembly |
| **Docker**, any system | `docker pull ghcr.io/gpasa/treelevel-tools:latest` | the five generators, WHIZARD 3 included |

**Mac**: drag `TreeLevel Tools.app` into `/Applications` and launch it once; TreeLevel then offers its generators
in the Generation workspace. **Windows**: unfold the archive into `%LOCALAPPDATA%\Programs`. **iPad**: the
*Pythia 8 module* card of the settings downloads it and checks every file. **Docker**: with the image present,
TreeLevel Tools runs in it the generators that no module provides (on the Mac, a box makes it run every job).
