The engine that runs the Monte Carlo generators for TreeLevel 1.4 on Windows (and still 1.3). It is installed by unfolding the archive into `%LOCALAPPDATA%\Programs` — no installer, nothing in the registry. **To update** a previous version: close TreeLevel, then unfold the archive in the same place, replacing the files.

Choose the archive for your machine: `arm64` for a Copilot+ PC or an ARM tablet, `x64` everywhere else. When in doubt, the x64 one also works on ARM, under emulation.

**What the archive contains**: `treelevel-tools.exe`, which TreeLevel launches; `treelevel-engine.exe`, the engine that writes each generator's card and runs it; the Pythia 8 module compiled for this architecture; `CREDITS.md`. Herwig, Sherpa, WHIZARD and CalcHEP go through the container image, which requires Docker Desktop:

```
docker pull ghcr.io/gpasa/treelevel-tools:latest
```

Nothing else to do: TreeLevel itself creates an ephemeral container for each job. Docker Desktop must be running when TreeLevel starts; the image's generators then appear, marked “(Docker)”.

**The engine has no window.** TreeLevel launches it, whenever needed. If you double-click `treelevel-tools.exe`, Windows SmartScreen warns of an unrecognised app — the engine is not signed — and, once past the warning, a console shows its usage and closes again. This is normal, and harmless.

### What changes

- **The host asks for image 0.5.0.** It is published and `:latest` points to it; the Windows engine looks first for `ghcr.io/gpasa/treelevel-tools:0.5.0`, then `:latest`, as before. With image 0.5.0, the “Tout faire tourner dans l'image Docker” box also gives the interaction zone (the image announces `spaceTimeGenerators`).
- **To benefit from it with Docker**: `docker pull ghcr.io/gpasa/treelevel-tools:latest` (or `:0.5.0`) replaces image 0.4.0.
- **Nothing else moves**: same Pythia driver and same job keys as `win-0.5.0`; compatible with TreeLevel 1.3 and 1.4.
