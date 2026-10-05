Le moteur qui fait tourner les générateurs Monte-Carlo pour TreeLevel 1.4 sur Windows (et toujours 1.3). Il s'installe en dépliant l'archive dans `%LOCALAPPDATA%\Programs` — pas de programme d'installation, rien dans le registre. **Pour mettre à jour** une version précédente : fermez TreeLevel, et dépliez l'archive au même endroit en remplaçant les fichiers.

Choisissez l'archive de votre machine : `arm64` pour un PC Copilot+ ou une tablette ARM, `x64` partout ailleurs. En cas de doute, la x64 fonctionne aussi sur ARM, en émulation.

**Ce que l'archive contient** : `treelevel-tools.exe`, que TreeLevel lance ; `treelevel-engine.exe`, le moteur qui écrit la carte de chaque générateur et le mène ; le module Pythia 8 compilé pour cette architecture ; `CREDITS.md`. Herwig, Sherpa, WHIZARD et CalcHEP passent par l'image de conteneur, qui demande Docker Desktop :

```
docker pull ghcr.io/gpasa/treelevel-tools:latest
```

Rien d'autre à faire : TreeLevel crée lui-même un conteneur éphémère pour chaque travail. Docker Desktop doit être lancé quand TreeLevel démarre ; les générateurs de l'image apparaissent alors, marqués « (Docker) ».

**Le moteur n'a pas de fenêtre.** C'est TreeLevel qui le lance, à chaque besoin. Si vous double-cliquez `treelevel-tools.exe`, Windows SmartScreen avertit d'une application non reconnue — le moteur n'est pas signé — et, passé l'avertissement, une console affiche son mode d'emploi et se referme. C'est normal, et sans effet.

### Ce qui change

- **L'hôte demande l'image 0.5.0.** Elle est publiée et `:latest` pointe sur elle ; le moteur Windows cherche d'abord `ghcr.io/gpasa/treelevel-tools:0.5.0`, puis `:latest`, comme avant. Avec l'image 0.5.0, la case « Tout faire tourner dans l'image Docker » donne aussi la zone d'interaction (l'image annonce `spaceTimeGenerators`).
- **Pour en profiter avec Docker** : `docker pull ghcr.io/gpasa/treelevel-tools:latest` (ou `:0.5.0`) remplace l'image 0.4.0.
- **Rien d'autre ne bouge** : même pilote Pythia et mêmes clés du travail que `win-0.5.0` ; compatible avec TreeLevel 1.3 et 1.4.
