Version du module : **$MODULE** — Pythia **$PYTHIA_VERSION**, compilé en WebAssembly avec le pilote commun de
TreeLevel Tools $MODULE. Cette page garde toujours le même nom : TreeLevel sur iPad (1.4 et plus récent) y prend la
dernière version, lit son numéro dans `module.json` et l'affiche dans ses réglages, propose la mise à jour quand
une version plus récente paraît, et vérifie chaque fichier contre l'empreinte que `module.json` en donne. Il le
fait tourner dans une vue web, sans rien envoyer nulle part.

Ce que ce module sait faire : `$FEATURES`. « spacetime » : placer partons et hadrons dans la zone d'interaction,
que TreeLevel montre au femtomètre.

| fichier | rôle |
|---|---|
| `module.json` | version du module et de Pythia, ce qu'il sait faire, l'empreinte de chaque fichier |
| `treelevel-pythia-web.wasm`, `.js` | Pythia $PYTHIA_VERSION et le pilote, en WebAssembly |
| `runner.js` | mène un travail de TreeLevel : plan, parties, réunion |
| `leptons.pack` | données de Pythia (xmldoc, tunes, setups) — faisceaux de leptons |
| `pdfdata.pack` | densités de partons — faisceaux de hadrons, facultatif |
| `$SOURCES` | les sources de Pythia $PYTHIA_VERSION, telles que publiées sur pythia.org |
| `COPYING.pythia8` | la licence de Pythia (GPL v2 ou ultérieure) |

TreeLevel 1.3 sur iPad télécharge son module depuis
[ipad-pythia-8.318](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia-8.318), dont il fixe les
empreintes : cette page-là ne change pas.

**Pythia 8, ses auteurs.** Pythia 8 est © Torbjörn Sjöstrand et la collaboration Pythia —
[pythia.org](https://pythia.org) — et distribué sous GPL v2 ou ultérieure. Toute la physique de ce module est la
leur. Si vous publiez un résultat obtenu avec lui, citez : C. Bierlich et al., « A comprehensive guide to the
physics and usage of PYTHIA 8.3 », *SciPost Phys. Codebases* 8 (2022),
[arXiv:2203.11601](https://arxiv.org/abs/2203.11601). Les autres générateurs pilotés par TreeLevel Tools, et leurs
auteurs : [CREDITS.md](https://github.com/gpasa/treelevel-tools/blob/main/CREDITS.md).

Il reste un programme séparé de TreeLevel : l'app lui passe un travail et relit le résultat. Les sources du
pilote et de `runner.js` sont dans ce dépôt (`Backends/pythia`), à l'étiquette `ipad-pythia-module-$MODULE`.
Sommes de contrôle dans `SHA256SUMS.txt`.
