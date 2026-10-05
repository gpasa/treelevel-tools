The engine that runs the Monte Carlo generators for TreeLevel on Windows. It is installed by unfolding the archive into `%LOCALAPPDATA%\Programs` — no installer, nothing in the registry. **To update** a previous version: close TreeLevel, then unfold the archive in the same place, replacing the files.

Choose the archive for your machine: `arm64` for a Copilot+ PC or an ARM tablet, `x64` everywhere else. When in doubt, the x64 one also works on ARM, under emulation.

**What the archive contains**: the engine and the Pythia 8 module compiled for this architecture. Herwig, Sherpa, WHIZARD and CalcHEP go through the container image, which requires Docker Desktop:

```
docker pull ghcr.io/gpasa/treelevel-tools
```

Nothing else to do: TreeLevel itself creates an ephemeral container for each job. Docker Desktop must be running when TreeLevel starts; the image's generators then appear, marked “(Docker)”.

**The engine has no window.** TreeLevel launches it, whenever needed. If you double-click `treelevel-tools.exe`, Windows SmartScreen warns of an unrecognised app — the engine is not signed — and, once past the warning, a console shows its usage and closes again. This is normal, and harmless: you never have to launch it yourself.

### Fixes in this version

- **The image pulled without a number is recognised.** 0.3.0 only recognised the `:0.3.0` tag; yet the command that the package page suggests, and the one everyone types, pulls `:latest`. The image was on the machine, answered when launched by hand, and yet TreeLevel offered only Pythia. Both tags designate the same image, and both are now recognised.
- **Sherpa on lepton beams**, when it runs outside the image: its cross section is no longer inflated by QED initial-state radiation (some fifteen picobarns instead of 3.2 for e⁻e⁺ → b b̄ at 200 GeV). The route that depended on it — Sherpa installed yourself in WSL — will be removed in a coming version: Docker is the intended route.

### Five generators, two families

**Pythia 8** and **Herwig 7** dress the partonic events that TreeLevel gives them: shower, hadronisation, decays.

**Sherpa 3**, **WHIZARD 3** and **CalcHEP 3** have no Les Houches reader — they compute the process described by the diagram themselves. The protocol therefore passes them a description of the process (beams, energies, final state, coupling orders) alongside the events.

### Measured: e⁻e⁺ → W⁺W⁻ at 200 GeV

| engine | σ |
|---|---|
| TreeLevel | 19.22 pb |
| WHIZARD 3.1.6 | 19.441 ± 0.006 pb |
| CalcHEP 3.9.2 | 20.42 pb |
| Sherpa 3.0.5 | 18.2 ± 1.1 pb |

The differences are choices of coupling scheme, not errors.

### Reminder: what 0.3.0 brought

- **Collider mode.** The generator receives only the beams and the energy, never a final state: it produces the whole mixture, like a real machine, and TreeLevel then counts the events that carry the signature of the drawn process — which measures a cross section instead of computing it. Six families of channels, including hard QCD, photoproduction and the total cross section. Pythia 8 for now.
- **Two machine configurations combined.** A lepton beam enters as a lepton or as the photon flux it radiates, never both in the same draw: the engine draws both and keeps from each the share that its cross section earns it.
- **The reported cross section is the one after the last event.** Pythia normalises after its loop; the driver wrote the running estimate, off by 12% over a few hundred events.
- **The program is called TreeLevel Tools**, and the executable `treelevel-tools.exe`.
- Jobs numbered, timestamped and kept in a list, which TreeLevel reopens; cross section read where each generator puts it.

TreeLevel Tools is under GPL v3 or later (see `LICENSE.txt` in the archive); each generator keeps its own licence, below.
