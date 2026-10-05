# Links and credits

TreeLevel Tools only drives these programs: it hands them a job and reads back what they return. The physics —
showers, hadronisation, matrix elements, integration — is entirely theirs, the fruit of decades of work by their
authors. They are distributed here as they are, under their own licences, with their sources. When you publish a
result obtained with one of them, cite it: that is what its authors ask, and it is what lets them carry on.

## The generators

| program | authors | site | licence | to cite |
|---|---|---|---|---|
| **Pythia 8** | © Torbjörn Sjöstrand and the Pythia collaboration | [pythia.org](https://pythia.org) | GPL v2 or later | C. Bierlich et al., "A comprehensive guide to the physics and usage of PYTHIA 8.3", *SciPost Phys. Codebases* 8 (2022), [arXiv:2203.11601](https://arxiv.org/abs/2203.11601) |
| **Herwig 7** | © the Herwig collaboration | [herwig.hepforge.org](https://herwig.hepforge.org) | GPL v3 | J. Bellm et al., "Herwig 7.0 / Herwig++ 3.0 release note", *Eur. Phys. J. C* 76 (2016) 196, [arXiv:1512.01178](https://arxiv.org/abs/1512.01178) |
| **Sherpa 3** | © the Sherpa authors (SHERPA-MC Authors) | [sherpa-team.gitlab.io](https://sherpa-team.gitlab.io) | GPL v3 or later | E. Bothmann et al., "Event generation with Sherpa 3", [arXiv:2410.22148](https://arxiv.org/abs/2410.22148) |
| **WHIZARD 3** | © 1999–2025 Wolfgang Kilian, Thorsten Ohl, Jürgen Reuter and their contributors | [whizard.hepforge.org](https://whizard.hepforge.org) | GPL v2 or later | W. Kilian, T. Ohl, J. Reuter, "WHIZARD: Simulating Multi-Particle Processes at LHC and ILC", *Eur. Phys. J. C* 71 (2011) 1742, [arXiv:0708.4233](https://arxiv.org/abs/0708.4233) |
| **CalcHEP 3** | Alexander Pukhov, Alexander Belyaev, Neil Christensen, with code from the CompHEP group | [theory.sinp.msu.ru/~pukhov/calchep.html](https://theory.sinp.msu.ru/~pukhov/calchep.html) | GPL v3 | A. Belyaev, N. Christensen, A. Pukhov, "CalcHEP 3.4 for collider physics within and beyond the Standard Model", *Comput. Phys. Commun.* 184 (2013) 1729, [arXiv:1207.6082](https://arxiv.org/abs/1207.6082) |

## What they bundle

| component | in | authors | site | to cite |
|---|---|---|---|---|
| **O'Mega** (optimised amplitudes) | WHIZARD | Mauro Moretti, Thorsten Ohl, Jürgen Reuter | [whizard.hepforge.org](https://whizard.hepforge.org) | M. Moretti, T. Ohl, J. Reuter, "O'Mega: An Optimizing Matrix Element Generator", [arXiv:hep-ph/0102195](https://arxiv.org/abs/hep-ph/0102195) |
| **CompHEP** (from which CalcHEP descends) | CalcHEP | E. Boos, V. Bunichev, M. Dubinin, L. Dudko, V. Ilyin, A. Kryukov, V. Edneral, V. Savrin, A. Semenov, A. Sherstnev | [comphep.sinp.msu.ru](https://comphep.sinp.msu.ru) | E. Boos et al., "CompHEP 4.4", *Nucl. Instrum. Meth. A* 534 (2004) 250, [arXiv:hep-ph/0403113](https://arxiv.org/abs/hep-ph/0403113) |
| **StdHEP / mcfio** (event formats) | WHIZARD | Fermilab | [cd-docdb.fnal.gov](https://cd-docdb.fnal.gov) | — |

## The libraries

| library | authors | site | licence | to cite |
|---|---|---|---|---|
| **ThePEG** (the foundation of Herwig) | © the Herwig collaboration | [herwig.hepforge.org](https://herwig.hepforge.org) | GPL v3 | see Herwig 7 above |
| **LHAPDF 6** (parton densities) | Andy Buckley, Mike Whalley et al. | [lhapdf.hepforge.org](https://lhapdf.hepforge.org) | GPL v3 | A. Buckley et al., "LHAPDF6: parton density access in the LHC precision era", *Eur. Phys. J. C* 75 (2015) 132, [arXiv:1412.7420](https://arxiv.org/abs/1412.7420) |
| **HepMC3** (event format) | the HepMC collaboration | [hepmc.web.cern.ch](http://hepmc.web.cern.ch/hepmc/) | GPL v3 | A. Buckley et al., "The HepMC3 event record library for Monte Carlo event generators", *Comput. Phys. Commun.* 260 (2021) 107310, [arXiv:1912.08005](https://arxiv.org/abs/1912.08005) |
| **FastJet** (jet algorithms) | Matteo Cacciari, Gavin P. Salam, Grégory Soyez | [fastjet.fr](https://fastjet.fr) | GPL v2 or later | M. Cacciari, G. P. Salam, G. Soyez, "FastJet user manual", *Eur. Phys. J. C* 72 (2012) 1896, [arXiv:1111.6097](https://arxiv.org/abs/1111.6097) |
| **GSL** (numerical computing) | the GNU Scientific Library and its contributors | [gnu.org/software/gsl](https://www.gnu.org/software/gsl/) | GPL v3 | M. Galassi et al., *GNU Scientific Library Reference Manual* |

## The formats

| format | to cite |
|---|---|
| **Les Houches** (parton-level events, between TreeLevel and the generators) | J. Alwall et al., "A standard format for Les Houches Event Files", *Comput. Phys. Commun.* 176 (2007) 300, [arXiv:hep-ph/0609017](https://arxiv.org/abs/hep-ph/0609017) |
| **HepMC3** (showered events, on the way back) | see HepMC3 above |

## The tools that build and run them

[Docker](https://www.docker.com) (the container image), [MacPorts](https://www.macports.org) and
[Homebrew](https://brew.sh) (the dependencies on the Mac), [GCC and gfortran](https://gcc.gnu.org) (Herwig, Sherpa,
WHIZARD, CalcHEP), [OCaml](https://ocaml.org) (O'Mega), [Emscripten](https://emscripten.org) (Pythia in
WebAssembly for the iPad), [CMake](https://cmake.org) and Microsoft Visual C++ (Pythia and the engine on Windows).

Versions shipped with TreeLevel Tools 0.5.0 and the 0.5.0 image: Pythia 8.318, Herwig 7.3.0 (ThePEG 2.3.0),
Sherpa 3.0.5, WHIZARD 3.1.6 (image only), CalcHEP 3.9.2, LHAPDF 6.5.3, HepMC3 3.2.5, FastJet 3.4.
The iPad module carries Pythia 8.318 alone.
