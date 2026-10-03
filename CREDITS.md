# Liens et crédits

TreeLevel Tools ne fait que piloter ces programmes : il leur passe un travail et relit ce qu'ils rendent. La
physique — gerbes, hadronisation, éléments de matrice, intégration — est entièrement la leur, fruit de décennies
de travail de leurs auteurs. Ils sont distribués ici tels quels, sous leurs propres licences, avec leurs sources.
Quand vous publiez un résultat obtenu avec l'un d'eux, citez-le : c'est ce que ses auteurs demandent, et c'est ce
qui leur permet de continuer.

## Les générateurs

| programme | auteurs | site | licence | à citer |
|---|---|---|---|---|
| **Pythia 8** | © Torbjörn Sjöstrand et la collaboration Pythia | [pythia.org](https://pythia.org) | GPL v2 ou ultérieure | C. Bierlich et al., « A comprehensive guide to the physics and usage of PYTHIA 8.3 », *SciPost Phys. Codebases* 8 (2022), [arXiv:2203.11601](https://arxiv.org/abs/2203.11601) |
| **Herwig 7** | © la collaboration Herwig | [herwig.hepforge.org](https://herwig.hepforge.org) | GPL v3 | J. Bellm et al., « Herwig 7.0 / Herwig++ 3.0 release note », *Eur. Phys. J. C* 76 (2016) 196, [arXiv:1512.01178](https://arxiv.org/abs/1512.01178) |
| **Sherpa 3** | © les auteurs de Sherpa (SHERPA-MC Authors) | [sherpa-team.gitlab.io](https://sherpa-team.gitlab.io) | GPL v3 ou ultérieure | E. Bothmann et al., « Event generation with Sherpa 3 », [arXiv:2410.22148](https://arxiv.org/abs/2410.22148) |
| **WHIZARD 3** | © 1999–2025 Wolfgang Kilian, Thorsten Ohl, Jürgen Reuter et leurs contributeurs | [whizard.hepforge.org](https://whizard.hepforge.org) | GPL v2 ou ultérieure | W. Kilian, T. Ohl, J. Reuter, « WHIZARD: Simulating Multi-Particle Processes at LHC and ILC », *Eur. Phys. J. C* 71 (2011) 1742, [arXiv:0708.4233](https://arxiv.org/abs/0708.4233) |
| **CalcHEP 3** | Alexander Pukhov, Alexander Belyaev, Neil Christensen, avec du code du groupe CompHEP | [theory.sinp.msu.ru/~pukhov/calchep.html](https://theory.sinp.msu.ru/~pukhov/calchep.html) | GPL v3 | A. Belyaev, N. Christensen, A. Pukhov, « CalcHEP 3.4 for collider physics within and beyond the Standard Model », *Comput. Phys. Commun.* 184 (2013) 1729, [arXiv:1207.6082](https://arxiv.org/abs/1207.6082) |

## Ce qu'ils embarquent

| composant | dans | auteurs | site | à citer |
|---|---|---|---|---|
| **O'Mega** (amplitudes optimisées) | WHIZARD | Mauro Moretti, Thorsten Ohl, Jürgen Reuter | [whizard.hepforge.org](https://whizard.hepforge.org) | M. Moretti, T. Ohl, J. Reuter, « O'Mega: An Optimizing Matrix Element Generator », [arXiv:hep-ph/0102195](https://arxiv.org/abs/hep-ph/0102195) |
| **CompHEP** (dont CalcHEP est issu) | CalcHEP | E. Boos, V. Bunichev, M. Dubinin, L. Dudko, V. Ilyin, A. Kryukov, V. Edneral, V. Savrin, A. Semenov, A. Sherstnev | [comphep.sinp.msu.ru](https://comphep.sinp.msu.ru) | E. Boos et al., « CompHEP 4.4 », *Nucl. Instrum. Meth. A* 534 (2004) 250, [arXiv:hep-ph/0403113](https://arxiv.org/abs/hep-ph/0403113) |
| **StdHEP / mcfio** (formats d'événements) | WHIZARD | Fermilab | [cd-docdb.fnal.gov](https://cd-docdb.fnal.gov) | — |

## Les bibliothèques

| bibliothèque | auteurs | site | licence | à citer |
|---|---|---|---|---|
| **ThePEG** (le socle de Herwig) | © la collaboration Herwig | [herwig.hepforge.org](https://herwig.hepforge.org) | GPL v3 | voir Herwig 7 ci-dessus |
| **LHAPDF 6** (densités de partons) | Andy Buckley, Mike Whalley et al. | [lhapdf.hepforge.org](https://lhapdf.hepforge.org) | GPL v3 | A. Buckley et al., « LHAPDF6: parton density access in the LHC precision era », *Eur. Phys. J. C* 75 (2015) 132, [arXiv:1412.7420](https://arxiv.org/abs/1412.7420) |
| **HepMC3** (format des événements) | la collaboration HepMC | [hepmc.web.cern.ch](http://hepmc.web.cern.ch/hepmc/) | GPL v3 | A. Buckley et al., « The HepMC3 event record library for Monte Carlo event generators », *Comput. Phys. Commun.* 260 (2021) 107310, [arXiv:1912.08005](https://arxiv.org/abs/1912.08005) |
| **FastJet** (algorithmes de jets) | Matteo Cacciari, Gavin P. Salam, Grégory Soyez | [fastjet.fr](https://fastjet.fr) | GPL v2 ou ultérieure | M. Cacciari, G. P. Salam, G. Soyez, « FastJet user manual », *Eur. Phys. J. C* 72 (2012) 1896, [arXiv:1111.6097](https://arxiv.org/abs/1111.6097) |
| **GSL** (calcul numérique) | la GNU Scientific Library et ses contributeurs | [gnu.org/software/gsl](https://www.gnu.org/software/gsl/) | GPL v3 | M. Galassi et al., *GNU Scientific Library Reference Manual* |

## Les formats

| format | à citer |
|---|---|
| **Les Houches** (événements au niveau partonique, entre TreeLevel et les générateurs) | J. Alwall et al., « A standard format for Les Houches Event Files », *Comput. Phys. Commun.* 176 (2007) 300, [arXiv:hep-ph/0609017](https://arxiv.org/abs/hep-ph/0609017) |
| **HepMC3** (événements gerbés, en retour) | voir HepMC3 ci-dessus |

## Les outils qui les construisent et les font tourner

[Docker](https://www.docker.com) (l'image de conteneur), [MacPorts](https://www.macports.org) et
[Homebrew](https://brew.sh) (les dépendances au Mac), [GCC et gfortran](https://gcc.gnu.org) (Herwig, Sherpa,
WHIZARD, CalcHEP), [OCaml](https://ocaml.org) (O'Mega), [Emscripten](https://emscripten.org) (Pythia en
WebAssembly pour l'iPad), [CMake](https://cmake.org) et Microsoft Visual C++ (Pythia et le moteur sous Windows).

Versions livrées avec TreeLevel Tools 0.5 et l'image 0.5.0 : Pythia 8.318, Herwig 7.3.0 (ThePEG 2.3.0),
Sherpa 3.0.5, WHIZARD 3.1.6 (image seulement), CalcHEP 3.9.2, LHAPDF 6.5.3, HepMC3 3.2.5, FastJet 3.4.
Le module de l'iPad porte Pythia 8.318 seul.
