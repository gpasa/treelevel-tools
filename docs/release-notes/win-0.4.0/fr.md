Le moteur qui fait tourner les générateurs Monte-Carlo pour TreeLevel 1.3 sur Windows. Il s'installe en dépliant l'archive dans `%LOCALAPPDATA%\Programs` — pas de programme d'installation, rien dans le registre. **Pour mettre à jour** une version précédente : fermez TreeLevel, et dépliez l'archive au même endroit en remplaçant les fichiers.

Choisissez l'archive de votre machine : `arm64` pour un PC Copilot+ ou une tablette ARM, `x64` partout ailleurs. En cas de doute, la x64 fonctionne aussi sur ARM, en émulation.

**Ce que l'archive contient** : `treelevel-tools.exe`, que TreeLevel lance ; `treelevel-engine.exe`, le moteur qui écrit la carte de chaque générateur et le mène ; le module Pythia 8 compilé pour cette architecture ; `CREDITS.md`. Herwig, Sherpa, WHIZARD et CalcHEP passent par l'image de conteneur, qui demande Docker Desktop :

```
docker pull ghcr.io/gpasa/treelevel-tools:0.4.0
```

Rien d'autre à faire : TreeLevel crée lui-même un conteneur éphémère pour chaque travail. Docker Desktop doit être lancé quand TreeLevel démarre ; les générateurs de l'image apparaissent alors, marqués « (Docker) ».

**Le moteur n'a pas de fenêtre.** C'est TreeLevel qui le lance, à chaque besoin. Si vous double-cliquez `treelevel-tools.exe`, Windows SmartScreen avertit d'une application non reconnue — le moteur n'est pas signé — et, passé l'avertissement, une console affiche son mode d'emploi et se referme. C'est normal, et sans effet.

### Ce qui change

- **Un seul moteur pour Windows, le Mac et l'image.** Les cartes des générateurs ne sont plus écrites qu'une fois, en C++ (`Backends/engine`), et le même programme tourne ici, au Mac et dans le conteneur. La partie Windows ne fait plus que trouver Docker, l'image et le module Pythia.
- **« Tout faire tourner dans l'image Docker »**, une case des Réglages de TreeLevel 1.3. Cochée, l'image mène tous les travaux, Pythia compris, et rien n'est proposé quand Docker ou l'image manquent. Décochée, Pythia tourne en natif et le reste passe par l'image.
- **Ce que l'expérience enregistre** : la source Machine de TreeLevel 1.3 choisit un phénomène — tout ce que le détecteur voit, la diffusion par un photon, l'annihilation en γ*/Z, le W échangé ou produit, les paires de bosons, les jets, la photoproduction, les collisions molles —, et le moteur l'ouvre avec le seuil qui lui convient (Q² pour les diffusions, p_T pour les jets).
- **Où chaque particule est née** : le pilote Pythia écrit la position des vertex, et le processus dur de chaque événement ; TreeLevel les dessine et filtre dessus.
- **Pythia 8.318** partout, avec ses tunes (`Monash 2013`, `A14`…) traduits en numéros de Pythia.
- **Chemins accentués** : un dossier de travail sous un nom d'utilisateur à accents s'ouvre comme un autre.
- Retirés : la voie WSL (Herwig ou Sherpa installés à la main dans une distribution) — Docker est la voie prévue.

TreeLevel Tools est sous GPL v3 ou ultérieure (voir `LICENSE.txt` dans l'archive) ; chaque générateur garde sa propre licence — voir `CREDITS.md`, et ci-dessous.
