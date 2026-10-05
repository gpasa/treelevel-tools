> **Superseded by [0.3.1](https://github.com/gpasa/treelevel-tools/releases/tag/win-0.3.1).** This one only recognises the image under the `:0.3.0` tag; 0.3.1 also accepts `:latest`, the one that `docker pull` pulls without a number.

The engine that runs the Monte Carlo generators for TreeLevel on Windows. It is installed by unfolding the archive into `%LOCALAPPDATA%\Programs` — no installer, nothing in the registry.

Choose the archive for your machine: `arm64` for a Copilot+ PC or an ARM tablet, `x64` everywhere else. When in doubt, the x64 one also works on ARM, under emulation.

**What the archive contains**: the engine and the Pythia 8 module compiled for this architecture. Herwig, Sherpa, WHIZARD and CalcHEP go through the container image `ghcr.io/gpasa/treelevel-tools`, which requires Docker. Pull it **with its number**:

```
docker pull ghcr.io/gpasa/treelevel-tools:0.3.0
```

This version of the engine only recognises this tag: an image pulled without a number (hence `:latest`) is indeed on the machine, but TreeLevel does not offer its generators. Both tags designate the same image; if you already have `latest`, the command above only adds the tag. Docker Desktop must be running when TreeLevel starts.

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

### New in this version

- **Collider mode.** The generator receives only the beams and the energy, never a final state: it produces the whole mixture, like a real machine, and TreeLevel then counts the events that carry the signature of the drawn process — which measures a cross section instead of computing it. Six families of channels, including hard QCD, photoproduction and the total cross section. Pythia 8 for now.
- **Two machine configurations combined.** A lepton beam enters as a lepton or as the photon flux it radiates, never both in the same draw: the engine draws both and keeps from each the share that its cross section earns it.
- **The reported cross section is the one after the last event.** Pythia normalises after its loop; the driver wrote the running estimate, off by 12% over a few hundred events.
- **The program is called TreeLevel Tools**, and the executable `treelevel-tools.exe`. It no longer carries only Monte Carlo engines.

### Also

- Jobs numbered, timestamped and kept in a list, which TreeLevel reopens.
- Cross section read where each generator puts it: `C` line of Asciiv3, `GenCrossSection` attribute, or integration table.

### Known issue

If Sherpa runs in a personal WSL installation rather than in the image, its cross section on lepton beams comes out too high: QED initial-state radiation stays switched on there, and e⁻e⁺ → b b̄ at 200 GeV gives some fifteen picobarns instead of 3.2. Through the image `ghcr.io/gpasa/treelevel-tools`, this is fixed.

TreeLevel Tools is under GPL v3 or later (see `LICENSE.txt` in the archive); each generator keeps its own licence, below.
