Pythia 8 compilé en WebAssembly, avec le pilote commun de TreeLevel Tools. TreeLevel sur iPad le télécharge
depuis cette page, fichier par fichier, et vérifie chacun contre une empreinte fixée dans l'app ; il le fait
tourner dans une vue web, sans rien envoyer nulle part. Les événements en sortent gerbés et hadronisés, et la
source Machine de TreeLevel devient disponible sur iPad.

| fichier | rôle |
|---|---|
| `treelevel-pythia-web.wasm`, `.js` | Pythia 8.318 et le pilote, en WebAssembly |
| `runner.js` | mène un travail de TreeLevel : plan, parties, réunion |
| `leptons.pack` | données de Pythia (xmldoc, tunes, setups) — faisceaux de leptons |
| `pdfdata.pack` | densités de partons — faisceaux de hadrons, facultatif |
| `pythia8318-sources.tgz` | les sources de Pythia 8.318, telles que publiées sur pythia.org |
| `COPYING.pythia8` | la licence de Pythia (GPL v2 ou ultérieure) |

### Pythia 8, ses auteurs

Pythia 8 est © Torbjörn Sjöstrand et la collaboration Pythia — [pythia.org](https://pythia.org) — et distribué
sous GPL v2 ou ultérieure. Toute la physique de ce module est la leur. Si vous publiez un résultat obtenu avec lui,
citez : C. Bierlich et al., « A comprehensive guide to the physics and usage of PYTHIA 8.3 »,
*SciPost Phys. Codebases* 8 (2022), [arXiv:2203.11601](https://arxiv.org/abs/2203.11601).

Les autres générateurs pilotés par TreeLevel Tools, et leurs auteurs :
[CREDITS.md](https://github.com/gpasa/treelevel-tools/blob/1.3-dev/CREDITS.md).
Il reste un programme séparé de TreeLevel : l'app lui passe un travail et relit le résultat. Les sources du
pilote et de `runner.js` sont dans ce dépôt, à l'étiquette de cette release (`Backends/pythia`).
Sommes de contrôle dans `SHA256SUMS.txt`.
