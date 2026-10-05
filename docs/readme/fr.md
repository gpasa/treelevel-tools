Les générateurs d'événements de [TreeLevel](https://treelevel.pasahome.org), sur votre machine. TreeLevel écrit un
travail dans un dossier local ; ce programme le confie à **Pythia 8**, **Herwig 7**, **Sherpa 3**, **WHIZARD 3** ou
**CalcHEP 3** — gerbe et hadronisation de ses événements, ou collisions entières d'une machine — et réécrit le
résultat en HepMC3, que TreeLevel relit. Rien ne transite par le réseau, aucun compte, aucun service. Sur iPad,
Pythia 8 compilé en WebAssembly joue le même rôle, téléchargé depuis
[sa release](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia).

Il est distribué séparément parce que ces générateurs sont sous licence **GPL** : ce dépôt est GPL v3, et TreeLevel
ne contient aucun de leur code.

| système | télécharger | ce qu'il contient |
|---|---|---|
| **macOS** 13 ou plus récent, Apple Silicon et Intel | [TreeLevelTools-0.5.0.dmg](https://github.com/gpasa/treelevel-tools/releases/download/mac-0.5.0/TreeLevelTools-0.5.0.dmg) | Pythia 8, Herwig 7, Sherpa 3 et CalcHEP 3, prêts à tourner |
| **Windows** 10 et 11 | [x64](https://github.com/gpasa/treelevel-tools/releases/download/win-0.5.1/TreeLevelTools-0.5.1-x64.zip) · [ARM64](https://github.com/gpasa/treelevel-tools/releases/download/win-0.5.1/TreeLevelTools-0.5.1-arm64.zip) | Pythia 8 ; les autres par l'image Docker |
| **iPad** | depuis les réglages de TreeLevel ([la release](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia)) | Pythia 8 en WebAssembly |
| **Docker**, tous systèmes | `docker pull ghcr.io/gpasa/treelevel-tools:latest` | les cinq générateurs, WHIZARD 3 compris |

**Mac** : glisser `TreeLevel Tools.app` dans `/Applications` et la lancer une fois ; TreeLevel propose alors ses
générateurs dans l'espace Génération. **Windows** : déplier l'archive dans `%LOCALAPPDATA%\Programs`. **iPad** : la
carte *Module Pythia 8* des réglages le télécharge et vérifie chaque fichier. **Docker** : l'image présente,
TreeLevel Tools y fait tourner les générateurs qu'aucun module n'offre (au Mac, une case lui confie tous les
travaux).
