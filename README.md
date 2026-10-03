# TreeLevel Tools

**[Téléchargements](#téléchargements)** · [Installation](#installation) · [Le conteneur](#lautre-voie--le-conteneur) · [Liens et crédits](#liens-et-crédits) · [Sommaire](#sommaire)

Les générateurs d'événements de [TreeLevel](https://treelevel.pasahome.org), sur votre machine. TreeLevel écrit un
travail dans un dossier local ; ce programme le confie à **Pythia 8**, **Herwig 7**, **Sherpa 3**, **WHIZARD 3** ou
**CalcHEP 3** — gerbe et hadronisation de ses événements, ou collisions entières d'une machine — et réécrit le
résultat en HepMC3, que TreeLevel relit. Rien ne transite par le réseau, aucun compte, aucun service. Sur iPad,
Pythia 8 compilé en WebAssembly joue le même rôle, téléchargé depuis
[sa release](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia-8.318).

Il est distribué séparément parce que ces générateurs sont sous licence **GPL** : ce dépôt est GPL v3, et TreeLevel
ne contient aucun de leur code.

## Téléchargements

| système | télécharger | ce qu'il contient |
|---|---|---|
| **macOS** 13 ou plus récent, Apple Silicon et Intel | [TreeLevelTools-0.5.0.dmg](https://github.com/gpasa/treelevel-tools/releases/download/mac-0.5.0/TreeLevelTools-0.5.0.dmg) | Pythia 8, Herwig 7, Sherpa 3 et CalcHEP 3, prêts à tourner |
| **Windows** 10 et 11 | [x64](https://github.com/gpasa/treelevel-tools/releases/download/win-0.5.0/TreeLevelTools-0.5.0-x64.zip) · [ARM64](https://github.com/gpasa/treelevel-tools/releases/download/win-0.5.0/TreeLevelTools-0.5.0-arm64.zip) | Pythia 8 ; les autres par l'image Docker |
| **iPad** | depuis les réglages de TreeLevel ([la release](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia-8.318)) | Pythia 8 en WebAssembly |
| **Docker**, tous systèmes | `docker pull ghcr.io/gpasa/treelevel-tools:latest` | les cinq générateurs, WHIZARD 3 compris |

Toutes les versions et leurs notes : [releases](https://github.com/gpasa/treelevel-tools/releases). L'installation pas à pas est [plus bas](#installation).

## Sommaire

- [Téléchargements](#téléchargements)
- [Liens et crédits](#liens-et-crédits) — [les générateurs](#les-générateurs), [ce qu'ils embarquent](#ce-quils-embarquent),
  [les bibliothèques](#les-bibliothèques), [les formats](#les-formats), [les outils](#les-outils-qui-les-construisent-et-les-font-tourner)
- [Ce que ça fait](#ce-que-ça-fait)
- [Où vivent les exécutables](#où-vivent-les-exécutables)
- [Installation](#installation) — [l'autre voie : le conteneur](#lautre-voie--le-conteneur)
- [En ligne de commande](#en-ligne-de-commande)
- [Construire les modules](#construire-les-modules) — [le pilote Pythia](#construire-le-pilote-pythia)
- [Construire le module Herwig 7](#construire-le-module-herwig-7)
- [Construire les modules Sherpa, WHIZARD et CalcHEP](#construire-les-modules-sherpa-whizard-et-calchep) —
  [ce que chacun attend](#ce-que-chacun-attend)
- [Publier une version](#publier-une-version)
- [Licence](#licence)
- [Windows](#windows)

## Liens et crédits

TreeLevel Tools ne fait que piloter ces programmes : il leur passe un travail et relit ce qu'ils rendent. La
physique — gerbes, hadronisation, éléments de matrice, intégration — est entièrement la leur, fruit de décennies
de travail de leurs auteurs. Ils sont distribués ici tels quels, sous leurs propres licences, avec leurs sources.
Quand vous publiez un résultat obtenu avec l'un d'eux, citez-le : c'est ce que ses auteurs demandent, et c'est ce
qui leur permet de continuer.

### Les générateurs

| programme | auteurs | site | licence | à citer |
|---|---|---|---|---|
| **Pythia 8** | © Torbjörn Sjöstrand et la collaboration Pythia | [pythia.org](https://pythia.org) | GPL v2 ou ultérieure | C. Bierlich et al., « A comprehensive guide to the physics and usage of PYTHIA 8.3 », *SciPost Phys. Codebases* 8 (2022), [arXiv:2203.11601](https://arxiv.org/abs/2203.11601) |
| **Herwig 7** | © la collaboration Herwig | [herwig.hepforge.org](https://herwig.hepforge.org) | GPL v3 | J. Bellm et al., « Herwig 7.0 / Herwig++ 3.0 release note », *Eur. Phys. J. C* 76 (2016) 196, [arXiv:1512.01178](https://arxiv.org/abs/1512.01178) |
| **Sherpa 3** | © les auteurs de Sherpa (SHERPA-MC Authors) | [sherpa-team.gitlab.io](https://sherpa-team.gitlab.io) | GPL v3 ou ultérieure | E. Bothmann et al., « Event generation with Sherpa 3 », [arXiv:2410.22148](https://arxiv.org/abs/2410.22148) |
| **WHIZARD 3** | © 1999–2025 Wolfgang Kilian, Thorsten Ohl, Jürgen Reuter et leurs contributeurs | [whizard.hepforge.org](https://whizard.hepforge.org) | GPL v2 ou ultérieure | W. Kilian, T. Ohl, J. Reuter, « WHIZARD: Simulating Multi-Particle Processes at LHC and ILC », *Eur. Phys. J. C* 71 (2011) 1742, [arXiv:0708.4233](https://arxiv.org/abs/0708.4233) |
| **CalcHEP 3** | Alexander Pukhov, Alexander Belyaev, Neil Christensen, avec du code du groupe CompHEP | [theory.sinp.msu.ru/~pukhov/calchep.html](https://theory.sinp.msu.ru/~pukhov/calchep.html) | GPL v3 | A. Belyaev, N. Christensen, A. Pukhov, « CalcHEP 3.4 for collider physics within and beyond the Standard Model », *Comput. Phys. Commun.* 184 (2013) 1729, [arXiv:1207.6082](https://arxiv.org/abs/1207.6082) |

### Ce qu'ils embarquent

| composant | dans | auteurs | site | à citer |
|---|---|---|---|---|
| **O'Mega** (amplitudes optimisées) | WHIZARD | Mauro Moretti, Thorsten Ohl, Jürgen Reuter | [whizard.hepforge.org](https://whizard.hepforge.org) | M. Moretti, T. Ohl, J. Reuter, « O'Mega: An Optimizing Matrix Element Generator », [arXiv:hep-ph/0102195](https://arxiv.org/abs/hep-ph/0102195) |
| **CompHEP** (dont CalcHEP est issu) | CalcHEP | E. Boos, V. Bunichev, M. Dubinin, L. Dudko, V. Ilyin, A. Kryukov, V. Edneral, V. Savrin, A. Semenov, A. Sherstnev | [comphep.sinp.msu.ru](https://comphep.sinp.msu.ru) | E. Boos et al., « CompHEP 4.4 », *Nucl. Instrum. Meth. A* 534 (2004) 250, [arXiv:hep-ph/0403113](https://arxiv.org/abs/hep-ph/0403113) |
| **StdHEP / mcfio** (formats d'événements) | WHIZARD | Fermilab | [cd-docdb.fnal.gov](https://cd-docdb.fnal.gov) | — |

### Les bibliothèques

| bibliothèque | auteurs | site | licence | à citer |
|---|---|---|---|---|
| **ThePEG** (le socle de Herwig) | © la collaboration Herwig | [herwig.hepforge.org](https://herwig.hepforge.org) | GPL v3 | voir Herwig 7 ci-dessus |
| **LHAPDF 6** (densités de partons) | Andy Buckley, Mike Whalley et al. | [lhapdf.hepforge.org](https://lhapdf.hepforge.org) | GPL v3 | A. Buckley et al., « LHAPDF6: parton density access in the LHC precision era », *Eur. Phys. J. C* 75 (2015) 132, [arXiv:1412.7420](https://arxiv.org/abs/1412.7420) |
| **HepMC3** (format des événements) | la collaboration HepMC | [hepmc.web.cern.ch](http://hepmc.web.cern.ch/hepmc/) | GPL v3 | A. Buckley et al., « The HepMC3 event record library for Monte Carlo event generators », *Comput. Phys. Commun.* 260 (2021) 107310, [arXiv:1912.08005](https://arxiv.org/abs/1912.08005) |
| **FastJet** (algorithmes de jets) | Matteo Cacciari, Gavin P. Salam, Grégory Soyez | [fastjet.fr](https://fastjet.fr) | GPL v2 ou ultérieure | M. Cacciari, G. P. Salam, G. Soyez, « FastJet user manual », *Eur. Phys. J. C* 72 (2012) 1896, [arXiv:1111.6097](https://arxiv.org/abs/1111.6097) |
| **GSL** (calcul numérique) | la GNU Scientific Library et ses contributeurs | [gnu.org/software/gsl](https://www.gnu.org/software/gsl/) | GPL v3 | M. Galassi et al., *GNU Scientific Library Reference Manual* |

### Les formats

| format | à citer |
|---|---|
| **Les Houches** (événements au niveau partonique, entre TreeLevel et les générateurs) | J. Alwall et al., « A standard format for Les Houches Event Files », *Comput. Phys. Commun.* 176 (2007) 300, [arXiv:hep-ph/0609017](https://arxiv.org/abs/hep-ph/0609017) |
| **HepMC3** (événements gerbés, en retour) | voir HepMC3 ci-dessus |

### Les outils qui les construisent et les font tourner

[Docker](https://www.docker.com) (l'image de conteneur), [MacPorts](https://www.macports.org) et
[Homebrew](https://brew.sh) (les dépendances au Mac), [GCC et gfortran](https://gcc.gnu.org) (Herwig, Sherpa,
WHIZARD, CalcHEP), [OCaml](https://ocaml.org) (O'Mega), [Emscripten](https://emscripten.org) (Pythia en
WebAssembly pour l'iPad), [CMake](https://cmake.org) et Microsoft Visual C++ (Pythia et le moteur sous Windows).

Versions livrées avec TreeLevel Tools 0.4.0 et l'image 0.4.0 : Pythia 8.318, Herwig 7.3.0 (ThePEG 2.3.0),
Sherpa 3.0.5, WHIZARD 3.1.6 (image seulement), CalcHEP 3.9.2, LHAPDF 6.5.3, HepMC3 3.2.5, FastJet 3.4.
Le module de l'iPad porte Pythia 8.318 seul.

## Ce que ça fait

```
TreeLevel                    dossier de travail                 TreeLevel Tools
  σ, |M|², événements  →   job.json + events.lhe       →   Pythia 8 / Herwig 7
  histogrammes, détecteur  ←   events.hepmc + status.json  ←   gerbe, hadronisation, désintégrations
```

Le dossier de travail est dans le conteneur de TreeLevel
(`~/Library/Containers/org.pasahome.Feyn/Data/Library/Application Support/MCJobs/<id>`) : les deux programmes y
accèdent, personne d'autre.

## Où vivent les exécutables

Une seule règle : **tout ce qui se lance est dans `~/Applications`** — `TreeLevel Tools.app` et, pendant le
développement, `TreeLevel (dev).app`. Les dossiers `build/` et `.build/` des dépôts ne contiennent que des
résultats de compilation jetables ; `scripts/install.sh` dépose la version bonne à l'emploi dans
`~/Applications` et retire les copies de compilation du registre de LaunchServices, pour qu'elles ne soient
jamais lancées par erreur. `/Applications` reste réservé aux applications installées par l'App Store.

```bash
scripts/install.sh      # construit et installe dans ~/Applications, avec le module Pythia
scripts/release.sh      # construit, signe, notarise et fabrique le .dmg à distribuer
```

## Installation

1. Télécharger le [DMG](#téléchargements), glisser `TreeLevel Tools.app` dans `/Applications`, la lancer une fois.
   Elle est signée et notarisée par Apple.
2. C'est tout : Pythia 8, Herwig 7, Sherpa 3 et CalcHEP 3 voyagent dans l'application, construits pour Apple
   Silicon et Intel et pour macOS 13 et suivants. Au premier lancement, elle écrit `capabilities.json` dans son
   dossier de support, et TreeLevel propose alors ces générateurs dans l'espace Génération.
3. WHIZARD 3 n'y est pas — il compile chaque processus avec gfortran, que macOS ne fournit pas. Pour lui, ou
   pour tout faire tourner dans un même environnement, il y a le conteneur ci-dessous.

### L'autre voie : le conteneur

L'image qui porte les cinq générateurs pour Windows tourne aussi bien sur un Mac, et le moteur sait s'en
servir. Pour qui a déjà Docker, c'est une commande au lieu d'une série de compilations :

```bash
docker pull ghcr.io/gpasa/treelevel-tools:latest
```

Le moteur regarde si l'image est **déjà** présente (`docker image inspect`) — il ne la tire jamais de
lui-même : un gigaoctet ne se télécharge pas dans le dos de quelqu'un. Quand elle est là, les générateurs
qu'aucun module n'offre apparaissent dans `capabilities` suivis de « (conteneur) », et un travail qui les
demande est mené par le moteur de l'image, avec le dossier de travail monté tel quel :

```
docker run --rm -v <dossier de travail>:/job <image> run /job
```

Rien n'est copié ni converti : le montage *est* le protocole, et le conteneur écrit lui-même son
`status.json` dans le dossier que TreeLevel relit. Docker Desktop partage `/Users` par défaut, donc le
dossier de travail — qui vit dans le bac à sable de TreeLevel — est monté sans réglage particulier.

**Les modules installés restent prioritaires** : ils tournent nativement, sans machine virtuelle, et
n'imposent pas que Docker soit démarré. Le conteneur ne prend la main que pour un générateur qui manque —
ou dont l'installation ne répond pas.

Deux mesures sur ce Mac, e⁻e⁺ → b b̄ à 200 GeV, 200 événements gerbés et hadronisés par Herwig :

| | |
|---|---|
| modules natifs | 3,0 s |
| conteneur | 1,0 s |

Le conteneur est plus rapide, ce qui surprend jusqu'à ce qu'on se rappelle que ses binaires sont ceux d'une
distribution Linux construite pour elle-même, là où les nôtres sortent d'une compilation croisée sous
MacPorts. La σ est la même à la neuvième décimale.

`TREELEVEL_MC_IMAGE` remplace l'image, le temps d'essayer une construction locale. Sans ce réglage, le
moteur cherche l'étiquette de sa propre version, puis `latest`.

## En ligne de commande

```bash
swift build -c release
.build/release/treelevel-tools capabilities          # ce que cette installation sait faire
.build/release/treelevel-tools run /chemin/du/dossier  # exécute job.json
```

Le dossier contient `job.json` (généré par TreeLevel, format décrit dans `Protocol/MCEngineProtocol.swift`),
`events.lhe` en entrée, puis `status.json`, `engine.log` et `events.hepmc` en sortie.

Chaque travail reçoit un numéro (compteur gardé dans le dossier de support), l'heure de début et de fin, et
s'ajoute à la liste `jobs.json` que la fenêtre affiche — elle survit aux relancements, un clic droit sur une
ligne ouvre le dossier du travail ou son journal, et « Vider la liste » l'oublie sans rien effacer sur le disque.

Trois générateurs : `pythia8`, `herwig7` et `passthrough` (aucune gerbe — les événements sont convertis tels
quels, pour vérifier la chaîne ou comparer avec le processus dur).

## Construire les modules

Depuis la 0.4.0 refaite le 1ᵉʳ octobre 2026, tout ce que les modules emportent se construit depuis les sources,
pour macOS 13, par `scripts/build_stack.sh` — une fois sur un Mac Apple Silicon, une fois sur un Mac Intel, au
même chemin —, puis `scripts/merge_stack.sh` fond les deux arbres en un arbre universel et
`scripts/package_module.sh` en fait des modules relogeables. `scripts/test_generators.sh` fait tourner un vrai
travail par générateur depuis l'application construite. Les sections qui suivent décrivent la construction
d'avant, par MacPorts, gardée pour ses remarques sur chaque générateur.

## Construire le pilote Pythia

`Backends/pythia/main.cpp` est un programme d'une centaine de lignes : il lit le fichier de commandes écrit par
le moteur et écrit le HepMC3. Il faut Pythia 8 compilé avec HepMC3.

```bash
make -C Backends/pythia          # ./treelevel-pythia
make -C Backends/pythia install  # dans Modules/pythia8/
```

## Construire le module Herwig 7

Aucun gestionnaire de paquets macOS ne fournit Herwig : ni MacPorts, ni Homebrew hors d'un tap non maintenu
(dont les binaires sont liés à une version de GSL qui n'existe plus). Il se construit donc depuis les sources,
avec le bootstrap officiel, et quatre précautions que la chaîne d'outils de 2026 impose :

```bash
# gcc de MacPorts, jamais clang : les constructeurs globaux de ThePEG appellent std::string avant que
# l'initialiseur de libc++ ait tourné, et l'allocation typée d'Apple clang 21 avorte à cet endroit précis.
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

Les quatre pièges, pour mémoire :

- **FastJet** : le greffon `D0RunIICone`, activé par `--enable-allcxxplugins`, ne compile plus (`this->_Et`,
  recherche de nom en deux phases). Herwig n'en a pas besoin : construire FastJet à part sans les greffons
  optionnels, et le passer par `--with-fastjet`.
- **LHAPDF** : son enrobage Python ne trouve pas `libpython` dans un *framework* MacPorts. Configurer avec
  `--disable-python` — et récupérer alors les jeux de PDF à la main, le script `lhapdf install` important ce
  même module.
- **ThePEG** : voir ci-dessus, d'où gcc plutôt que clang. Toute la pile (FastJet, HepMC3, LHAPDF) doit suivre,
  sans quoi les ABI C++ ne s'accordent pas.
- **LoopTools** : `parameter (nz2 = -2147483648)` déborde pour gfortran 15, d'où le `-fno-range-check` glissé
  dans le compilateur enrobé — `configure` écrase `FCFLAGS`, le drapeau ne peut pas passer par l'environnement.

Le dossier `lib/ThePEG` contient des greffons liés à `@rpath/libHepMC3`, dont le rpath est celui de la machine
de construction ; le moteur pose `DYLD_FALLBACK_LIBRARY_PATH` sur les `lib` du module, donc il n'y a rien à
retoucher.

Mesuré sur un e⁻e⁺ → W⁺W⁻ à 200 GeV, 10 000 événements partoniques écrits par TreeLevel : **12,2 s** de
cascade et d'hadronisation (Pythia 8 : 6,4 s).

## Construire les modules Sherpa, WHIZARD et CalcHEP

Tous avec le même gcc 15 de MacPorts que Herwig — les ABI C++ doivent s'accorder — et en réutilisant les
HepMC3, LHAPDF et FastJet installés dans le préfixe `herwig7`.

```bash
export PATH=/opt/local/bin:/usr/bin:/bin
export CC=/opt/local/bin/gcc-mp-15 CXX=/opt/local/bin/g++-mp-15 FC=/opt/local/bin/gfortran-mp-15
DEPS=~/Library/TreeLevelMC/herwig7

# Sherpa 3.0.5 — CMake. `_Static_assert` est un mot-clé du C que clang accepte aussi en C++ et
# que gcc refuse ; mach/port.h s'en sert, et ATOOLS/Org/RUsage.C inclut mach/mach.h.
cmake -S . -B build -DCMAKE_INSTALL_PREFIX=~/Library/TreeLevelMC/sherpa3 \
  -DCMAKE_CXX_FLAGS="-D_Static_assert=static_assert" \
  -DSHERPA_ENABLE_LHAPDF=ON -DLHAPDF_DIR=$DEPS \
  -DSHERPA_ENABLE_HEPMC3=ON -DHepMC3_DIR=$DEPS \
  -DSHERPA_ENABLE_FASTJET=ON -DFASTJET_DIR=$DEPS
cmake --build build -j 12 && cmake --install build

# WHIZARD 3.1.6 — autotools, OCaml de MacPorts pour O'Mega. mcfio/StdHEP mélange long et int32_t
# dans ses appels XDR, ce dont gcc 15 fait des erreurs.
export CFLAGS="-O2 -std=gnu17 -Wno-incompatible-pointer-types -Wno-implicit-function-declaration -Wno-int-conversion"
./configure --prefix=~/Library/TreeLevelMC/whizard3 --with-hepmc=$DEPS --with-lhapdf=$DEPS \
            --with-fastjet=$DEPS --disable-latex && make -j 12 && make install

# CalcHEP 3.9.2 — un simple make, mais il faut le construire là où il vivra : ses bibliothèques
# portent leur chemin absolu.
make
```

Puis un lien depuis le dossier de modules, comme pour Herwig :

```bash
cd ~/Library/Application\ Support/TreeLevel\ MC\ Engine/Modules
ln -s ~/Library/TreeLevelMC/sherpa3 ~/Library/TreeLevelMC/whizard3 ~/Library/TreeLevelMC/calchep3 .
```

### Ce que chacun attend

Sherpa, WHIZARD et CalcHEP n'ont pas de lecteur Les Houches : on leur décrit le processus (`MCProcess`
du protocole) et ils calculent tout eux-mêmes. Trois détails appris à leurs dépens :

- **Sherpa** écrit son HepMC3 dans le fichier dont on lui donne le nom de base, et sa section efficace dans
  la ligne `C` du format Asciiv3.
- **WHIZARD** refuse `?ps_isr_active` ailleurs que sur une collision hadronique, et n'écrit aucune section
  efficace dans son HepMC3 : elle se lit dans la dernière ligne de sa table d'intégration, en femtobarns.
  Le rayonnement QED d'un faisceau leptonique est `?isr_active`, laissé éteint — il déplacerait σ.
- **CalcHEP** s'arrête au niveau partonique : ni gerbe ni hadronisation. Un travail tourne dans une copie
  de son arbre faite par `mkWORKdir`, et ses événements Les Houches gzippés sont convertis en HepMC3 par
  le même code que le passe-plat.

### Mesuré : e⁻e⁺ → W⁺W⁻ à 200 GeV

| moteur | σ | remarque |
|---|---|---|
| TreeLevel | 19,22 pb | à l'arbre, M_W imposée par G_F |
| WHIZARD 3.1.6 | 19,441 ± 0,006 pb | O'Mega, schéma propre |
| CalcHEP 3.9.2 | 20,42 pb | autre schéma de couplages |
| Sherpa 3.0.5 | 18,2 ± 1,1 pb | rayonnement initial QED activé par défaut |

Les écarts sont des choix de schéma, pas des erreurs : le couplage entre à la puissance quatre.

## Publier une version

Tout se passe sur la machine du développeur : la clé Developer ID ne quitte pas le trousseau, rien n'est confié
à un service d'intégration continue.

```bash
scripts/release.sh                 # construit, signe, notarise, agrafe, fabrique le .dmg
scripts/release.sh 0.2.0           # idem en fixant le numéro de version (project.yml et sources)
scripts/release.sh --no-notarize   # s'arrête après la signature, pour vérifier hors ligne
scripts/release.sh --upload        # crée en plus la release GitLab (GITLAB_PROJECT et GITLAB_TOKEN)
```

Préalables, une seule fois :

- un certificat **Developer ID Application** dans le trousseau (Xcode › Réglages › Comptes › Gérer les
  certificats) — il est inclus dans l'adhésion au programme développeur, il n'y a rien de plus à payer ;
- les identifiants de notarisation :
  `xcrun notarytool store-credentials "TreeLevelMC" --apple-id <identifiant> --team-id 9LVGAJ594U --password <mot de passe pour app>`.

Le script produit dans `build/release/` : l'application signée et agrafée, le `.dmg` (avec un lien vers
`/Applications`, le README et la licence), le `.zip`, `SHA256SUMS.txt` et un brouillon de notes de version.
La vérification finale, `spctl -a -t open --context context:primary-signature -v`, doit répondre `accepted`.

## Licence

GNU General Public License v3 ou ultérieure — voir `LICENSE`. Le fichier `Protocol/MCEngineProtocol.swift`,
partagé avec TreeLevel, est sous licence MIT (voir son en-tête) pour que les deux programmes puissent le lire.

## Windows

Le port Windows est dans [`win/`](win/) : un hôte en C#, le moteur C++ commun (`Backends/engine`) compilé avec
MSVC, le module Pythia 8 construit de même (`win/backends/pythia`) ; Herwig, Sherpa, WHIZARD et CalcHEP par l'image
Docker. Le protocole est le même : un dossier de travail écrit sur un Mac se relit sur
Windows et inversement. Voir [`win/README.md`](win/README.md).
