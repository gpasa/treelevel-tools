Les outils sous licence GPL que TreeLevel ne peut pas contenir, sur votre machine — rien ne sort d'ici.
TreeLevel est sandboxé et ne lance aucun programme ; ce paquet est ce qui a le droit de les exécuter.

- Glisser `TreeLevel Tools.app` dans `/Applications`, la lancer une fois.
- Quatre générateurs sont **déjà dedans**, rien d'autre à installer :
  - **Pythia 8** et **Herwig 7** habillent les événements de TreeLevel : gerbe, hadronisation, désintégrations.
  - **Sherpa 3** et **CalcHEP 3** n'ont pas de lecteur Les Houches : ils calculent eux-mêmes le processus décrit
    par le diagramme, d'après une description du processus (faisceaux, énergies, état final, ordres de couplage)
    que le protocole leur transmet à côté des événements.
- TreeLevel les propose alors dans l'espace Génération.

**WHIZARD 3** n'y est pas : il compile chaque processus avec gfortran, que ni macOS ni Xcode ne fournissent.
Deux façons de l'avoir, toutes deux à cocher dans la fenêtre de TreeLevel Tools :

- l'**image Docker** `ghcr.io/gpasa/treelevel-tools:0.3.0`, qui porte les cinq outils dans un environnement cohérent ;
- votre **propre installation** (MacPorts, Homebrew), si vous en avez une.

Aucune des deux ne sert d'office : par défaut, seuls les générateurs livrés ici sont proposés, pour qu'un
même document donne le même résultat sur deux machines.

### Mesuré : e⁻e⁺ → W⁺W⁻ à 200 GeV

| moteur | σ |
|---|---|
| TreeLevel | 19,22 pb |
| WHIZARD 3.1.6 | 19,441 ± 0,006 pb |
| CalcHEP 3.9.2 | 20,42 pb |
| Sherpa 3.0.5 | 18,2 ± 1,1 pb |

Les écarts sont des choix de schéma de couplages, pas des erreurs.

### Aussi

- Travaux numérotés, horodatés et conservés dans une liste.
- Chemins de bibliothèques d'un module corrigés à l'exécution : un module compilé ailleurs fonctionne sans retoucher ses binaires.
- Section efficace lue là où chaque générateur la met : ligne `C` d'Asciiv3, attribut `GenCrossSection`, ou table d'intégration.

Le README donne les recettes de compilation des modules sur macOS 26, avec les quatre ou cinq pièges que la
chaîne d'outils de 2026 réserve à des codes de 2023.

Signé et notarisé par Apple. Sommes de contrôle dans `SHA256SUMS.txt`.
