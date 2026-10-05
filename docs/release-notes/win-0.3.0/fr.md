> **Remplacée par la [0.3.1](https://github.com/gpasa/treelevel-tools/releases/tag/win-0.3.1).** Celle-ci ne reconnaît l'image que sous l'étiquette `:0.3.0` ; la 0.3.1 accepte aussi `:latest`, celle que tire `docker pull` sans numéro.

Le moteur qui fait tourner les générateurs Monte-Carlo pour TreeLevel sur Windows. Il s'installe en dépliant l'archive dans `%LOCALAPPDATA%\Programs` — pas de programme d'installation, rien dans le registre.

Choisissez l'archive de votre machine : `arm64` pour un PC Copilot+ ou une tablette ARM, `x64` partout ailleurs. En cas de doute, la x64 fonctionne aussi sur ARM, en émulation.

**Ce que l'archive contient** : le moteur et le module Pythia 8 compilé pour cette architecture. Herwig, Sherpa, WHIZARD et CalcHEP passent par l'image de conteneur `ghcr.io/gpasa/treelevel-tools`, qui demande Docker. Tirez-la **avec son numéro** :

```
docker pull ghcr.io/gpasa/treelevel-tools:0.3.0
```

Cette version du moteur ne reconnaît que cette étiquette : une image tirée sans numéro (donc `:latest`) est bien sur la machine, mais TreeLevel n'en propose pas les générateurs. Les deux étiquettes désignent la même image ; si vous avez déjà `latest`, la commande ci-dessus n'ajoute que l'étiquette. Docker Desktop doit être lancé quand TreeLevel démarre.

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

### Nouveautés de cette version

- **Le mode collisionneur.** Le générateur ne reçoit que les faisceaux et l'énergie, jamais un état final : il produit le mélange entier, comme une vraie machine, et TreeLevel compte ensuite les événements qui portent la signature du processus dessiné — ce qui mesure une section efficace au lieu de la calculer. Six familles de voies, dont la QCD dure, la photoproduction et la section efficace totale. Pythia 8 pour l'instant.
- **Deux configurations de machine assemblées.** Un faisceau de leptons entre comme lepton ou comme le flux de photons qu'il rayonne, jamais les deux dans un même tirage : le moteur tire les deux et garde de chacun la part que sa section efficace lui vaut.
- **La section efficace rapportée est celle d'après le dernier événement.** Pythia normalise après sa boucle ; le pilote écrivait l'estimation courante, fausse de 12 % sur quelques centaines d'événements.
- **Le programme s'appelle TreeLevel Tools**, et l'exécutable `treelevel-tools.exe`. Il ne porte plus seulement des moteurs Monte-Carlo.

### Aussi

- Travaux numérotés, horodatés et conservés dans une liste, que TreeLevel rouvre.
- Section efficace lue là où chaque générateur la met : ligne `C` d'Asciiv3, attribut `GenCrossSection`, ou table d'intégration.

### Problème connu

Si Sherpa tourne dans une installation WSL personnelle plutôt que dans l'image, sa section efficace sur des faisceaux de leptons sort trop haute : le rayonnement initial de QED y reste allumé, et e⁻e⁺ → b b̄ à 200 GeV donne une quinzaine de picobarns au lieu de 3,2. Par l'image `ghcr.io/gpasa/treelevel-tools`, c'est corrigé.

TreeLevel Tools est sous GPL v3 ou ultérieure (voir `LICENSE.txt` dans l'archive) ; chaque générateur garde sa propre licence, ci-dessous.
