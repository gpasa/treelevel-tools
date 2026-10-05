The engine that runs the Monte Carlo generators for TreeLevel 1.4 on Windows (and still 1.3). It is installed by unfolding the archive into `%LOCALAPPDATA%\Programs` — no installer, nothing in the registry. **To update** a previous version: close TreeLevel, then unfold the archive in the same place, replacing the files.

Choose the archive for your machine: `arm64` for a Copilot+ PC or an ARM tablet, `x64` everywhere else. When in doubt, the x64 one also works on ARM, under emulation.

**What the archive contains**: `treelevel-tools.exe`, which TreeLevel launches; `treelevel-engine.exe`, the engine that writes each generator's card and runs it; the Pythia 8 module compiled for this architecture; `CREDITS.md`. Herwig, Sherpa, WHIZARD and CalcHEP go through the container image, which requires Docker Desktop:

```
docker pull ghcr.io/gpasa/treelevel-tools:latest
```

Nothing else to do: TreeLevel itself creates an ephemeral container for each job. Docker Desktop must be running when TreeLevel starts; the image's generators then appear, marked “(Docker)”.

**The engine has no window.** TreeLevel launches it, whenever needed. If you double-click `treelevel-tools.exe`, Windows SmartScreen warns of an unrecognised app — the engine is not signed — and, once past the warning, a console shows its usage and closes again. This is normal, and harmless.

### What changes

- **The interaction zone, at the femtometre.** For TreeLevel 1.4, the Pythia driver can place each partonic interaction in the overlap of the two hadrons and each hadron where its string broke (job key `spaceTime`: `PartonVertex:setVertex`, `Fragmentation:setVertices`). It writes, for each parton, its colour flow and its Pythia status, and for each particle born away from its vertex, its own birthplace — which the enlarged cross-section and the 3D view of TreeLevel 1.4 draw. This is the generator's model, nothing measured.
- **A single offset of the luminous region.** With these positions, Pythia shifted the hadrons twice; the driver now places the event itself, by a single vector. Without the key, nothing changes.
- **The engine says what it can do**: `treelevel-tools capabilities` announces `spaceTimeGenerators` (native Pythia when its driver answers “spacetime”, and whatever the image announces). TreeLevel 1.4 only shows the “positions in the interaction zone” box when it is listed there.
- **Compatible with TreeLevel 1.3**: a job without the `spaceTime` key runs exactly as with 0.4.0.
- **Docker image 0.5** follows: until then, `:latest` is image 0.4.0, and Herwig, Sherpa, WHIZARD and CalcHEP run in it as before; the interaction zone goes through this archive's native Pythia.
- **The same engine as `mac-0.5.0`**: same Pythia driver (`Backends/pythia/main.cpp`), same job keys, same attributes written.
