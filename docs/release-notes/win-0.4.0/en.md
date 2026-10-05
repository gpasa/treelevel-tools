The engine that runs the Monte Carlo generators for TreeLevel 1.3 on Windows. It is installed by unfolding the archive into `%LOCALAPPDATA%\Programs` — no installer, nothing in the registry. **To update** a previous version: close TreeLevel, then unfold the archive in the same place, replacing the files.

Choose the archive for your machine: `arm64` for a Copilot+ PC or an ARM tablet, `x64` everywhere else. When in doubt, the x64 one also works on ARM, under emulation.

**What the archive contains**: `treelevel-tools.exe`, which TreeLevel launches; `treelevel-engine.exe`, the engine that writes each generator's card and runs it; the Pythia 8 module compiled for this architecture; `CREDITS.md`. Herwig, Sherpa, WHIZARD and CalcHEP go through the container image, which requires Docker Desktop:

```
docker pull ghcr.io/gpasa/treelevel-tools:0.4.0
```

Nothing else to do: TreeLevel itself creates an ephemeral container for each job. Docker Desktop must be running when TreeLevel starts; the image's generators then appear, marked “(Docker)”.

**The engine has no window.** TreeLevel launches it, whenever needed. If you double-click `treelevel-tools.exe`, Windows SmartScreen warns of an unrecognised app — the engine is not signed — and, once past the warning, a console shows its usage and closes again. This is normal, and harmless.

### What changes

- **A single engine for Windows, the Mac and the image.** The generators' cards are now written only once, in C++ (`Backends/engine`), and the same program runs here, on the Mac and in the container. The Windows part now only finds Docker, the image and the Pythia module.
- **“Tout faire tourner dans l'image Docker”**, a box in TreeLevel 1.3's Settings. When ticked, the image runs all jobs, Pythia included, and nothing is offered when Docker or the image is missing. When unticked, Pythia runs natively and the rest goes through the image.
- **What the experiment records**: TreeLevel 1.3's Machine source chooses a phenomenon — everything the detector sees, scattering by a photon, annihilation into γ*/Z, the W exchanged or produced, boson pairs, jets, photoproduction, soft collisions —, and the engine opens it with the threshold that suits it (Q² for scatterings, p_T for jets).
- **Where each particle was born**: the Pythia driver writes the position of the vertices, and the hard process of each event; TreeLevel draws them and filters on them.
- **Pythia 8.318** everywhere, with its tunes (`Monash 2013`, `A14`…) translated into Pythia's numbers.
- **Accented paths**: a job folder under a user name with accents opens like any other.
- Removed: the WSL route (Herwig or Sherpa installed by hand in a distribution) — Docker is the intended route.

TreeLevel Tools is under GPL v3 or later (see `LICENSE.txt` in the archive); each generator keeps its own licence — see `CREDITS.md`, and below.
