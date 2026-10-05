The GPL tools that TreeLevel cannot contain, on your machine — nothing leaves it. TreeLevel is sandboxed and
launches no program; this package is what is allowed to run them.

### New in 0.5.0

- **Pythia 8 places the particles in the interaction zone** when TreeLevel 1.4 asks for it (the option
  "positions in the interaction zone"): where each hadron is born, at the femtometre, the colour flow and the
  status of the partons, and a single offset of the luminous region for the whole event. TreeLevel shows it at
  the femtometre, in the cuts and in 3D.
- TreeLevel 1.3 asks for none of this and receives the same events as with 0.4.0; same generators, same versions.
- Tried on an Apple Silicon Mac and on an Intel iMac: each bundled generator runs a real job.

### Install

- For **Apple Silicon and Intel** Macs, macOS 13 or later.
- Drag `TreeLevel Tools.app` into `/Applications` and launch it once.
- Four generators are **already inside**, nothing else to install:
  - **Pythia 8** and **Herwig 7** dress TreeLevel's events between two leptons: shower, hadronisation, decays.
    **Pythia 8** also drives the Machine source: two beams, an energy, and everything the collision produces.
  - **Sherpa 3** and **CalcHEP 3** compute the process described by the diagram themselves.
- TreeLevel then offers them in the Generation workspace.

The cards of all generators are written by the same C++ engine as inside the Docker image: the same job gives the
same card on the Mac and on Linux.

**WHIZARD 3** is not included: it compiles each process with gfortran, which neither macOS nor Xcode provides.
Two ways to have it, to tick in the TreeLevel Tools window:

- the **Docker image** `ghcr.io/gpasa/treelevel-tools:latest`, which carries the five tools; when ticked, it runs
  **all** jobs, and the generators bundled here stay silent;
- your **own installation** (MacPorts, Homebrew), if you have one.

Neither is used by default: out of the box only the generators bundled here are offered, so that the same document
gives the same result on two machines.

Signed and notarised by Apple. Checksums in `SHA256SUMS.txt`.
