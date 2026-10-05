## Contents

- [Links and credits](#links-and-credits) — [the generators](#the-generators), [what they bundle](#what-they-bundle),
  [the libraries](#the-libraries), [the formats](#the-formats), [the tools](#the-tools-that-build-and-run-them)
- [What it does](#what-it-does)
- [Where the executables live](#where-the-executables-live)
- [Installation](#installation) — [the other way: the container](#the-other-way-the-container)
- [On the command line](#on-the-command-line)
- [Building the modules](#building-the-modules) — [the Pythia driver](#building-the-pythia-driver)
- [Building the Herwig 7 module](#building-the-herwig-7-module)
- [Building the Sherpa, WHIZARD and CalcHEP modules](#building-the-sherpa-whizard-and-calchep-modules) —
  [what each one expects](#what-each-one-expects)
- [Publishing a version](#publishing-a-version)
- [Licence](#licence)
- [Windows](#windows)

## Links and credits

TreeLevel Tools only drives these programs: it hands them a job and reads back what they return. The physics —
showers, hadronisation, matrix elements, integration — is entirely theirs, the fruit of decades of work by their
authors. They are distributed here as they are, under their own licences, with their sources. When you publish a
result obtained with one of them, cite it: that is what its authors ask, and it is what lets them carry on.

### The generators

| program | authors | site | licence | to cite |
|---|---|---|---|---|
| **Pythia 8** | © Torbjörn Sjöstrand and the Pythia collaboration | [pythia.org](https://pythia.org) | GPL v2 or later | C. Bierlich et al., "A comprehensive guide to the physics and usage of PYTHIA 8.3", *SciPost Phys. Codebases* 8 (2022), [arXiv:2203.11601](https://arxiv.org/abs/2203.11601) |
| **Herwig 7** | © the Herwig collaboration | [herwig.hepforge.org](https://herwig.hepforge.org) | GPL v3 | J. Bellm et al., "Herwig 7.0 / Herwig++ 3.0 release note", *Eur. Phys. J. C* 76 (2016) 196, [arXiv:1512.01178](https://arxiv.org/abs/1512.01178) |
| **Sherpa 3** | © the Sherpa authors (SHERPA-MC Authors) | [sherpa-team.gitlab.io](https://sherpa-team.gitlab.io) | GPL v3 or later | E. Bothmann et al., "Event generation with Sherpa 3", [arXiv:2410.22148](https://arxiv.org/abs/2410.22148) |
| **WHIZARD 3** | © 1999–2025 Wolfgang Kilian, Thorsten Ohl, Jürgen Reuter and their contributors | [whizard.hepforge.org](https://whizard.hepforge.org) | GPL v2 or later | W. Kilian, T. Ohl, J. Reuter, "WHIZARD: Simulating Multi-Particle Processes at LHC and ILC", *Eur. Phys. J. C* 71 (2011) 1742, [arXiv:0708.4233](https://arxiv.org/abs/0708.4233) |
| **CalcHEP 3** | Alexander Pukhov, Alexander Belyaev, Neil Christensen, with code from the CompHEP group | [theory.sinp.msu.ru/~pukhov/calchep.html](https://theory.sinp.msu.ru/~pukhov/calchep.html) | GPL v3 | A. Belyaev, N. Christensen, A. Pukhov, "CalcHEP 3.4 for collider physics within and beyond the Standard Model", *Comput. Phys. Commun.* 184 (2013) 1729, [arXiv:1207.6082](https://arxiv.org/abs/1207.6082) |

### What they bundle

| component | in | authors | site | to cite |
|---|---|---|---|---|
| **O'Mega** (optimised amplitudes) | WHIZARD | Mauro Moretti, Thorsten Ohl, Jürgen Reuter | [whizard.hepforge.org](https://whizard.hepforge.org) | M. Moretti, T. Ohl, J. Reuter, "O'Mega: An Optimizing Matrix Element Generator", [arXiv:hep-ph/0102195](https://arxiv.org/abs/hep-ph/0102195) |
| **CompHEP** (from which CalcHEP descends) | CalcHEP | E. Boos, V. Bunichev, M. Dubinin, L. Dudko, V. Ilyin, A. Kryukov, V. Edneral, V. Savrin, A. Semenov, A. Sherstnev | [comphep.sinp.msu.ru](https://comphep.sinp.msu.ru) | E. Boos et al., "CompHEP 4.4", *Nucl. Instrum. Meth. A* 534 (2004) 250, [arXiv:hep-ph/0403113](https://arxiv.org/abs/hep-ph/0403113) |
| **StdHEP / mcfio** (event formats) | WHIZARD | Fermilab | [cd-docdb.fnal.gov](https://cd-docdb.fnal.gov) | — |

### The libraries

| library | authors | site | licence | to cite |
|---|---|---|---|---|
| **ThePEG** (the foundation of Herwig) | © the Herwig collaboration | [herwig.hepforge.org](https://herwig.hepforge.org) | GPL v3 | see Herwig 7 above |
| **LHAPDF 6** (parton densities) | Andy Buckley, Mike Whalley et al. | [lhapdf.hepforge.org](https://lhapdf.hepforge.org) | GPL v3 | A. Buckley et al., "LHAPDF6: parton density access in the LHC precision era", *Eur. Phys. J. C* 75 (2015) 132, [arXiv:1412.7420](https://arxiv.org/abs/1412.7420) |
| **HepMC3** (event format) | the HepMC collaboration | [hepmc.web.cern.ch](http://hepmc.web.cern.ch/hepmc/) | GPL v3 | A. Buckley et al., "The HepMC3 event record library for Monte Carlo event generators", *Comput. Phys. Commun.* 260 (2021) 107310, [arXiv:1912.08005](https://arxiv.org/abs/1912.08005) |
| **FastJet** (jet algorithms) | Matteo Cacciari, Gavin P. Salam, Grégory Soyez | [fastjet.fr](https://fastjet.fr) | GPL v2 or later | M. Cacciari, G. P. Salam, G. Soyez, "FastJet user manual", *Eur. Phys. J. C* 72 (2012) 1896, [arXiv:1111.6097](https://arxiv.org/abs/1111.6097) |
| **GSL** (numerical computing) | the GNU Scientific Library and its contributors | [gnu.org/software/gsl](https://www.gnu.org/software/gsl/) | GPL v3 | M. Galassi et al., *GNU Scientific Library Reference Manual* |

### The formats

| format | to cite |
|---|---|
| **Les Houches** (parton-level events, between TreeLevel and the generators) | J. Alwall et al., "A standard format for Les Houches Event Files", *Comput. Phys. Commun.* 176 (2007) 300, [arXiv:hep-ph/0609017](https://arxiv.org/abs/hep-ph/0609017) |
| **HepMC3** (showered events, on the way back) | see HepMC3 above |

### The tools that build and run them

[Docker](https://www.docker.com) (the container image), [MacPorts](https://www.macports.org) and
[Homebrew](https://brew.sh) (the dependencies on the Mac), [GCC and gfortran](https://gcc.gnu.org) (Herwig, Sherpa,
WHIZARD, CalcHEP), [OCaml](https://ocaml.org) (O'Mega), [Emscripten](https://emscripten.org) (Pythia in
WebAssembly for the iPad), [CMake](https://cmake.org) and Microsoft Visual C++ (Pythia and the engine on Windows).

Versions shipped with TreeLevel Tools 0.5.0 and the 0.5.0 image: Pythia 8.318, Herwig 7.3.0 (ThePEG 2.3.0),
Sherpa 3.0.5, WHIZARD 3.1.6 (image only), CalcHEP 3.9.2, LHAPDF 6.5.3, HepMC3 3.2.5, FastJet 3.4.
The iPad module carries Pythia 8.318 alone.

## What it does

```
TreeLevel                       job folder                         TreeLevel Tools
  σ, |M|², events          →   job.json + events.lhe        →   Pythia 8 / Herwig 7
  histograms, detector     ←   events.hepmc + status.json   ←   shower, hadronisation, decays
```

The job folder is inside TreeLevel's container
(`~/Library/Containers/org.pasahome.Feyn/Data/Library/Application Support/MCJobs/<id>`): both programs reach it,
nobody else does.

## Where the executables live

A single rule: **everything that is launched lives in `~/Applications`** — `TreeLevel Tools.app` and, during
development, `TreeLevel (dev).app`. The `build/` and `.build/` folders of the repositories hold only disposable
build products; `scripts/install.sh` puts the usable version in `~/Applications` and removes the build copies from
the LaunchServices register, so that they are never launched by mistake. `/Applications` is kept for applications
installed by the App Store.

```bash
scripts/install.sh      # builds and installs into ~/Applications, with the Pythia module
scripts/release.sh      # builds, signs, notarises and makes the .dmg to distribute
```

## Installation

1. Download the [DMG](#treelevel-tools), drag `TreeLevel Tools.app` into `/Applications`, launch it once.
   It is signed and notarised by Apple.
2. That is all: Pythia 8, Herwig 7, Sherpa 3 and CalcHEP 3 travel inside the application, built for Apple
   Silicon and Intel and for macOS 13 and later. At the first launch it writes `capabilities.json` into its support
   folder, and TreeLevel then offers these generators in the Generation workspace.
3. WHIZARD 3 is not there — it compiles each process with gfortran, which macOS does not provide. For it, or to
   run everything in a single environment, there is the container below.

### The other way: the container

The image that carries the five generators for Windows runs just as well on a Mac, and the engine knows how to use
it. For anyone who already has Docker, it is one command instead of a series of builds:

```bash
docker pull ghcr.io/gpasa/treelevel-tools:latest
```

The image is built for `linux/amd64` and `linux/arm64`. The engine checks whether the image is **already** present
(`docker image inspect`) — it never pulls it by itself: a gigabyte is not downloaded behind someone's back. When it
is there, the generators that no module offers appear in `capabilities` followed by "(container)", and a job that
asks for them is run by the image's engine, with the job folder mounted as it is:

```
docker run --rm -v <job folder>:/job <image> run /job
```

Nothing is copied or converted: the mount *is* the protocol, and the container writes its own `status.json` into
the folder that TreeLevel reads back. Docker Desktop shares `/Users` by default, so the job folder — which lives
in TreeLevel's sandbox — is mounted without any particular setting.

**Installed modules keep priority**: they run natively, without a virtual machine, and do not require Docker to
be running. The container takes over only for a generator that is missing — or whose installation does not
answer.

Two measurements on this Mac, e⁻e⁺ → b b̄ at 200 GeV, 200 events showered and hadronised by Herwig:

| | |
|---|---|
| native modules | 3.0 s |
| container | 1.0 s |

The container is faster, which is surprising until one remembers that its binaries are those of a Linux
distribution built for itself, whereas ours come out of a cross-build under MacPorts. σ is the same to the ninth
decimal.

`TREELEVEL_MC_IMAGE` replaces the image, while trying a local build. Without it, the engine looks for `latest`,
then for the tag of its own version.

## On the command line

```bash
swift build -c release
.build/release/treelevel-tools capabilities          # what this installation can do
.build/release/treelevel-tools run /path/to/folder   # runs job.json
```

The folder holds `job.json` (written by TreeLevel, format described in `Protocol/MCEngineProtocol.swift`),
`events.lhe` as input, then `status.json`, `engine.log` and `events.hepmc` as output.

Each job receives a number (a counter kept in the support folder), its start and end times, and is added to the
`jobs.json` list that the window shows — it survives relaunches, a right click on a line opens the job folder or its
log, and "Clear the list" forgets it without deleting anything on disk.

Three generators: `pythia8`, `herwig7` and `passthrough` (no shower — the events are converted as they are, to
check the chain or to compare with the hard process).

## Building the modules

Since 0.4.0, rebuilt on 1 October 2026, everything the modules carry is built from source, for macOS 13, by
`scripts/build_stack.sh` — once on an Apple Silicon Mac, once on an Intel Mac, at the same path —, then
`scripts/merge_stack.sh` merges the two trees into a universal tree and `scripts/package_module.sh` turns it into
relocatable modules. `scripts/test_generators.sh` runs a real job per generator from the built application. The
sections that follow describe the earlier build, through MacPorts, kept for its notes on each generator.

## Building the Pythia driver

`Backends/pythia/main.cpp` is a program of about a hundred lines: it reads the command file written by the engine
and writes the HepMC3. It needs Pythia 8 compiled with HepMC3.

```bash
make -C Backends/pythia          # ./treelevel-pythia
make -C Backends/pythia install  # into Modules/pythia8/
```

## Building the Herwig 7 module

No macOS package manager provides Herwig: neither MacPorts, nor Homebrew outside an unmaintained tap (whose
binaries are linked to a GSL version that no longer exists). It is therefore built from source, with the official
bootstrap, and four precautions that the 2026 toolchain imposes:

```bash
# MacPorts gcc, never clang: ThePEG's global constructors call std::string before libc++'s initialiser has run,
# and Apple clang 21's typed allocation aborts at that very spot.
printf '#!/bin/sh\nexec /opt/local/bin/gfortran-mp-15 -fno-range-check "$@"\n' > ~/Library/TreeLevelMC/tools/gfortran-tl
chmod +x ~/Library/TreeLevelMC/tools/gfortran-tl

curl -LO https://herwig.hepforge.org/downloads/herwig-bootstrap
env PATH="$HOME/Library/TreeLevelMC/tools:/opt/local/bin:/usr/bin:/bin" \
    CC=/opt/local/bin/gcc-mp-15 CXX=/opt/local/bin/g++-mp-15 FC="$HOME/Library/TreeLevelMC/tools/gfortran-tl" \
    python3.13 herwig-bootstrap --lite -j 12 \
      --with-gsl=/opt/local --with-boost=/opt/local \
      --with-fastjet="$HOME/Library/TreeLevelMC/herwig7" \
      "$HOME/Library/TreeLevelMC/herwig7"

ln -s ~/Library/TreeLevelMC/herwig7 ~/Library/Application\ Support/TreeLevel\ MC\ Engine/Modules/herwig7
```

The four traps, for the record:

- **FastJet**: the `D0RunIICone` plugin, enabled by `--enable-allcxxplugins`, no longer compiles (`this->_Et`,
  two-phase name lookup). Herwig does not need it: build FastJet separately without the optional plugins, and pass
  it with `--with-fastjet`.
- **LHAPDF**: its Python wrapper does not find `libpython` in a MacPorts *framework*. Configure with
  `--disable-python` — and then fetch the PDF sets by hand, since the `lhapdf install` script imports that very
  module.
- **ThePEG**: see above, hence gcc rather than clang. The whole stack (FastJet, HepMC3, LHAPDF) must follow, or the
  C++ ABIs do not match.
- **LoopTools**: `parameter (nz2 = -2147483648)` overflows for gfortran 15, hence the `-fno-range-check` slipped
  into the wrapped compiler — `configure` overwrites `FCFLAGS`, so the flag cannot go through the environment.

The `lib/ThePEG` folder holds plugins linked to `@rpath/libHepMC3`, whose rpath is that of the build machine; the
engine sets `DYLD_FALLBACK_LIBRARY_PATH` to the module's `lib` folders, so there is nothing to touch up.

Measured on e⁻e⁺ → W⁺W⁻ at 200 GeV, 10,000 parton-level events written by TreeLevel: **12.2 s** of cascade and
hadronisation (Pythia 8: 6.4 s).

## Building the Sherpa, WHIZARD and CalcHEP modules

All with the same MacPorts gcc 15 as Herwig — the C++ ABIs must match — and reusing the HepMC3, LHAPDF and
FastJet installed in the `herwig7` prefix.

```bash
export PATH=/opt/local/bin:/usr/bin:/bin
export CC=/opt/local/bin/gcc-mp-15 CXX=/opt/local/bin/g++-mp-15 FC=/opt/local/bin/gfortran-mp-15
DEPS=~/Library/TreeLevelMC/herwig7

# Sherpa 3.0.5 — CMake. `_Static_assert` is a C keyword that clang also accepts in C++ and gcc refuses;
# mach/port.h uses it, and ATOOLS/Org/RUsage.C includes mach/mach.h.
cmake -S . -B build -DCMAKE_INSTALL_PREFIX=~/Library/TreeLevelMC/sherpa3 \
  -DCMAKE_CXX_FLAGS="-D_Static_assert=static_assert" \
  -DSHERPA_ENABLE_LHAPDF=ON -DLHAPDF_DIR=$DEPS \
  -DSHERPA_ENABLE_HEPMC3=ON -DHepMC3_DIR=$DEPS \
  -DSHERPA_ENABLE_FASTJET=ON -DFASTJET_DIR=$DEPS
cmake --build build -j 12 && cmake --install build

# WHIZARD 3.1.6 — autotools, MacPorts OCaml for O'Mega. mcfio/StdHEP mixes long and int32_t in its XDR calls,
# which gcc 15 turns into errors.
export CFLAGS="-O2 -std=gnu17 -Wno-incompatible-pointer-types -Wno-implicit-function-declaration -Wno-int-conversion"
./configure --prefix=~/Library/TreeLevelMC/whizard3 --with-hepmc=$DEPS --with-lhapdf=$DEPS \
            --with-fastjet=$DEPS --disable-latex && make -j 12 && make install

# CalcHEP 3.9.2 — a plain make, but it must be built where it will live: its libraries carry their absolute path.
make
```

Then a link from the modules folder, as for Herwig:

```bash
cd ~/Library/Application\ Support/TreeLevel\ MC\ Engine/Modules
ln -s ~/Library/TreeLevelMC/sherpa3 ~/Library/TreeLevelMC/whizard3 ~/Library/TreeLevelMC/calchep3 .
```

### What each one expects

Sherpa, WHIZARD and CalcHEP have no Les Houches reader: they are given the process (`MCProcess` in the protocol)
and compute everything themselves. Three details learnt the hard way:

- **Sherpa** writes its HepMC3 into the file whose base name it is given, and its cross section in the `C` line of
  the Asciiv3 format.
- **WHIZARD** refuses `?ps_isr_active` anywhere but on a hadronic collision, and writes no cross section into its
  HepMC3: it is read from the last line of its integration table, in femtobarns. The QED radiation of a lepton beam
  is `?isr_active`, left off — it would shift σ.
- **CalcHEP** stops at parton level: no shower and no hadronisation. A job runs in a copy of its tree made by
  `mkWORKdir`, and its gzipped Les Houches events are converted to HepMC3 by the same code as the passthrough.

### Measured: e⁻e⁺ → W⁺W⁻ at 200 GeV

| engine | σ | remark |
|---|---|---|
| TreeLevel | 19.22 pb | at tree level, M_W imposed by G_F |
| WHIZARD 3.1.6 | 19.441 ± 0.006 pb | O'Mega, its own scheme |
| CalcHEP 3.9.2 | 20.42 pb | another coupling scheme |
| Sherpa 3.0.5 | 18.2 ± 1.1 pb | QED initial-state radiation on by default |

The differences are choices of scheme, not errors: the coupling enters to the fourth power.

## Publishing a version

Everything happens on the developer's machine: the Developer ID key does not leave the keychain, and nothing is
entrusted to a continuous-integration service (the Docker image excepted, built by GitHub Actions).

```bash
scripts/release.sh                 # builds, signs, notarises, staples, makes the .dmg
scripts/release.sh 0.2.0           # the same, setting the version number (project.yml and sources)
scripts/release.sh --no-notarize   # stops after signing, to check offline
scripts/release.sh --upload        # also creates the GitHub release mac-<version> (gh authenticated)
```

Once only, beforehand:

- a **Developer ID Application** certificate in the keychain (Xcode › Settings › Accounts › Manage Certificates) —
  it comes with the developer programme membership, there is nothing more to pay;
- the notarisation credentials:
  `xcrun notarytool store-credentials "TreeLevelMC" --apple-id <id> --team-id 9LVGAJ594U --password <app password>`.

The script produces in `build/release/`: the signed and stapled application, the `.dmg` (with a link to
`/Applications`, the README and the licence), the `.zip`, `SHA256SUMS.txt` and a draft of release notes. The final
check, `spctl -a -t open --context context:primary-signature -v`, must answer `accepted`.

The iPad module is published by `Backends/pythia/wasm/release.sh <version> --upload`, under the stable release
`ipad-pythia`, with its notes in eleven languages (`Backends/pythia/wasm/notes/`).

## Licence

GNU General Public License v3 or later — see `LICENSE`. The file `Protocol/MCEngineProtocol.swift`, shared with
TreeLevel, is under the MIT licence (see its header) so that both programs can read it.

## Windows

The Windows port is in [`win/`](win/): a C# host, the common C++ engine (`Backends/engine`) compiled with MSVC, the
Pythia 8 module built the same way (`win/backends/pythia`); Herwig, Sherpa, WHIZARD and CalcHEP through the Docker
image. The protocol is the same: a job folder written on a Mac reads back on Windows and the other way round. See
[`win/README.md`](win/README.md).
