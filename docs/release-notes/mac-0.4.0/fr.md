Les outils sous licence GPL que TreeLevel ne peut pas contenir, sur votre machine — rien ne sort d'ici.
TreeLevel est sandboxé et ne lance aucun programme ; ce paquet est ce qui a le droit de les exécuter.

- Pour Mac **Apple Silicon et Intel**, macOS 13 ou plus récent.
- Glisser `TreeLevel Tools.app` dans `/Applications`, la lancer une fois.
- Quatre générateurs sont **déjà dedans**, rien d'autre à installer :
  - **Pythia 8** et **Herwig 7** habillent les événements de TreeLevel entre deux leptons : gerbe,
    hadronisation, désintégrations. **Pythia 8** mène aussi la source Machine : deux faisceaux, une énergie,
    et tout ce que la collision produit.
  - **Sherpa 3** et **CalcHEP 3** calculent eux-mêmes le processus décrit par le diagramme.
- TreeLevel les propose alors dans l'espace Génération.

Les cartes de tous les générateurs sont écrites par le même moteur C++ qu'au sein de l'image Docker : un
même travail donne la même carte au Mac et sous Linux.

**WHIZARD 3** n'y est pas : il compile chaque processus avec gfortran, que ni macOS ni Xcode ne fournissent.
Deux façons de l'avoir, à cocher dans la fenêtre de TreeLevel Tools :

- l'**image Docker** `ghcr.io/gpasa/treelevel-tools:latest`, qui porte les cinq outils ; cochée, elle mène
  **tous** les travaux, et les générateurs livrés ici se taisent ;
- votre **propre installation** (MacPorts, Homebrew), si vous en avez une.

Aucune des deux ne sert d'office : par défaut, seuls les générateurs livrés ici sont proposés, pour qu'un
même document donne le même résultat sur deux machines.

Signé et notarisé par Apple. Sommes de contrôle dans `SHA256SUMS.txt`.
