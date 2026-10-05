The GPL tools that TreeLevel cannot contain, on your machine — nothing leaves it.
TreeLevel is sandboxed and launches no program; this package is what is allowed to run them.

- Drag `TreeLevel Tools.app` into `/Applications` and launch it once.
- Four generators are **already inside**, nothing else to install:
  - **Pythia 8** and **Herwig 7** dress TreeLevel's events: shower, hadronisation, decays.
  - **Sherpa 3** and **CalcHEP 3** have no Les Houches reader: they compute the process described
    by the diagram themselves, from a description of the process (beams, energies, final state, coupling orders)
    that the protocol passes them alongside the events.
- TreeLevel then offers them in the Generation workspace.

**WHIZARD 3** is not included: it compiles each process with gfortran, which neither macOS nor Xcode provides.
Two ways to have it, both to tick in the TreeLevel Tools window:

- the **Docker image** `ghcr.io/gpasa/treelevel-tools:0.3.0`, which carries the five tools in a consistent environment;
- your **own installation** (MacPorts, Homebrew), if you have one.

Neither is used by default: out of the box only the generators bundled here are offered, so that the same
document gives the same result on two machines.

### Measured: e⁻e⁺ → W⁺W⁻ at 200 GeV

| engine | σ |
|---|---|
| TreeLevel | 19.22 pb |
| WHIZARD 3.1.6 | 19.441 ± 0.006 pb |
| CalcHEP 3.9.2 | 20.42 pb |
| Sherpa 3.0.5 | 18.2 ± 1.1 pb |

The differences are choices of coupling scheme, not errors.

### Also

- Jobs numbered, timestamped and kept in a list.
- Library paths of a module corrected at run time: a module compiled elsewhere works without touching its binaries.
- Cross section read where each generator puts it: `C` line of Asciiv3, `GenCrossSection` attribute, or integration table.

The README gives the recipes for compiling the modules on macOS 26, with the four or five pitfalls that the
2026 toolchain holds in store for 2023 code.

Signed and notarised by Apple. Checksums in `SHA256SUMS.txt`.
