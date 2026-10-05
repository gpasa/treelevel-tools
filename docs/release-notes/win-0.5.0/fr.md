Le moteur qui fait tourner les générateurs Monte-Carlo pour TreeLevel 1.4 sur Windows (et toujours 1.3). Il s'installe en dépliant l'archive dans `%LOCALAPPDATA%\Programs` — pas de programme d'installation, rien dans le registre. **Pour mettre à jour** une version précédente : fermez TreeLevel, et dépliez l'archive au même endroit en remplaçant les fichiers.

Choisissez l'archive de votre machine : `arm64` pour un PC Copilot+ ou une tablette ARM, `x64` partout ailleurs. En cas de doute, la x64 fonctionne aussi sur ARM, en émulation.

**Ce que l'archive contient** : `treelevel-tools.exe`, que TreeLevel lance ; `treelevel-engine.exe`, le moteur qui écrit la carte de chaque générateur et le mène ; le module Pythia 8 compilé pour cette architecture ; `CREDITS.md`. Herwig, Sherpa, WHIZARD et CalcHEP passent par l'image de conteneur, qui demande Docker Desktop :

```
docker pull ghcr.io/gpasa/treelevel-tools:latest
```

Rien d'autre à faire : TreeLevel crée lui-même un conteneur éphémère pour chaque travail. Docker Desktop doit être lancé quand TreeLevel démarre ; les générateurs de l'image apparaissent alors, marqués « (Docker) ».

**Le moteur n'a pas de fenêtre.** C'est TreeLevel qui le lance, à chaque besoin. Si vous double-cliquez `treelevel-tools.exe`, Windows SmartScreen avertit d'une application non reconnue — le moteur n'est pas signé — et, passé l'avertissement, une console affiche son mode d'emploi et se referme. C'est normal, et sans effet.

### Ce qui change

- **La zone d'interaction, au femtomètre.** Pour TreeLevel 1.4, le pilote Pythia sait placer chaque interaction partonique dans le recouvrement des deux hadrons et chaque hadron là où sa corde s'est rompue (clé `spaceTime` du travail : `PartonVertex:setVertex`, `Fragmentation:setVertices`). Il écrit pour chaque parton son flux de couleur et son statut Pythia, et pour chaque particule née ailleurs que son vertex son propre lieu de naissance — ce que la coupe agrandie et la vue 3D de TreeLevel 1.4 dessinent. C'est le modèle du générateur, rien de mesuré.
- **Un seul décalage de zone lumineuse.** Avec ces positions, Pythia décalait les hadrons deux fois ; le pilote place désormais l'événement lui-même, d'un seul vecteur. Sans la clé, rien ne change.
- **Le moteur dit ce qu'il sait faire** : `treelevel-tools capabilities` annonce `spaceTimeGenerators` (Pythia natif quand son pilote répond « spacetime », et ce que l'image annonce). TreeLevel 1.4 ne montre la case « positions dans la zone d'interaction » que si elle y figure.
- **Compatible avec TreeLevel 1.3** : un travail sans la clé `spaceTime` tourne exactement comme avec la 0.4.0.
- **L'image Docker 0.5** suit : d'ici là, `:latest` est l'image 0.4.0, et Herwig, Sherpa, WHIZARD et CalcHEP y tournent comme avant ; la zone d'interaction passe par le Pythia natif de cette archive.
- **Le même moteur que `mac-0.5.0`** : même pilote Pythia (`Backends/pythia/main.cpp`), mêmes clés du travail, mêmes attributs écrits.
