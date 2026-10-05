Le moteur qui fait tourner les générateurs Monte-Carlo pour TreeLevel sur Windows. Il s'installe en dépliant l'archive dans `%LOCALAPPDATA%\Programs` — pas de programme d'installation, rien dans le registre. **Pour mettre à jour** une version précédente : fermez TreeLevel, et dépliez l'archive au même endroit en remplaçant les fichiers.

Choisissez l'archive de votre machine : `arm64` pour un PC Copilot+ ou une tablette ARM, `x64` partout ailleurs. En cas de doute, la x64 fonctionne aussi sur ARM, en émulation.

**Ce que l'archive contient** : le moteur et le module Pythia 8 compilé pour cette architecture. Herwig, Sherpa, WHIZARD et CalcHEP passent par l'image de conteneur, qui demande Docker Desktop :

```
docker pull ghcr.io/gpasa/treelevel-tools
```

Rien d'autre à faire : TreeLevel crée lui-même un conteneur éphémère pour chaque travail. Docker Desktop doit être lancé quand TreeLevel démarre ; les générateurs de l'image apparaissent alors, marqués « (Docker) ».

**Le moteur n'a pas de fenêtre.** C'est TreeLevel qui le lance, à chaque besoin. Si vous double-cliquez `treelevel-tools.exe`, Windows SmartScreen avertit d'une application non reconnue — le moteur n'est pas signé — et, passé l'avertissement, une console affiche son mode d'emploi et se referme. C'est normal, et sans effet : vous n'avez jamais à le lancer vous-même.

### Corrections de cette version

- **L'image tirée sans numéro est reconnue.** La 0.3.0 ne reconnaissait que l'étiquette `:0.3.0` ; or la commande que propose la page du paquet, et celle que tout le monde tape, tire `:latest`. L'image était sur la machine, répondait quand on la lançait à la main, et TreeLevel n'offrait pourtant que Pythia. Les deux étiquettes désignent la même image, et les deux sont désormais reconnues.
- **Sherpa sur des faisceaux de leptons**, quand il tourne hors de l'image : sa section efficace n'est plus gonflée par le rayonnement initial de QED (une quinzaine de picobarns au lieu de 3,2 pour e⁻e⁺ → b b̄ à 200 GeV). La voie qui en dépendait — Sherpa installé soi-même dans WSL — sera retirée dans une prochaine version : Docker est la voie prévue.

### Cinq générateurs, deux familles

**Pythia 8** et **Herwig 7** habillent les événements partoniques que TreeLevel leur donne : gerbe, hadronisation, désintégrations.

**Sherpa 3**, **WHIZARD 3** et **CalcHEP 3** n'ont pas de lecteur Les Houches — ils calculent eux-mêmes le processus décrit par le diagramme. Le protocole leur transmet donc une description du processus (faisceaux, énergies, état final, ordres de couplage) à côté des événements.

### Mesuré : e⁻e⁺ → W⁺W⁻ à 200 GeV

| moteur | σ |
|---|---|
| TreeLevel | 19,22 pb |
| WHIZARD 3.1.6 | 19,441 ± 0,006 pb |
| CalcHEP 3.9.2 | 20,42 pb |
| Sherpa 3.0.5 | 18,2 ± 1,1 pb |

Les écarts sont des choix de schéma de couplages, pas des erreurs.

### Rappel : ce qu'apportait la 0.3.0

- **Le mode collisionneur.** Le générateur ne reçoit que les faisceaux et l'énergie, jamais un état final : il produit le mélange entier, comme une vraie machine, et TreeLevel compte ensuite les événements qui portent la signature du processus dessiné — ce qui mesure une section efficace au lieu de la calculer. Six familles de voies, dont la QCD dure, la photoproduction et la section efficace totale. Pythia 8 pour l'instant.
- **Deux configurations de machine assemblées.** Un faisceau de leptons entre comme lepton ou comme le flux de photons qu'il rayonne, jamais les deux dans un même tirage : le moteur tire les deux et garde de chacun la part que sa section efficace lui vaut.
- **La section efficace rapportée est celle d'après le dernier événement.** Pythia normalise après sa boucle ; le pilote écrivait l'estimation courante, fausse de 12 % sur quelques centaines d'événements.
- **Le programme s'appelle TreeLevel Tools**, et l'exécutable `treelevel-tools.exe`.
- Travaux numérotés, horodatés et conservés dans une liste, que TreeLevel rouvre ; section efficace lue là où chaque générateur la met.

TreeLevel Tools est sous GPL v3 ou ultérieure (voir `LICENSE.txt` dans l'archive) ; chaque générateur garde sa propre licence, ci-dessous.
