# Pythia 8 en WebAssembly — pour l'iPad

Pythia et le pilote commun (`../main.cpp`, `--job`) compilés par Emscripten. L'iPad ne peut ni lancer un
programme ni charger du code natif téléchargé, et un programme GPL ne peut pas voyager dans le binaire App
Store : le module est téléchargé par l'utilisateur depuis une release GitHub, vérifié par empreinte, et exécuté
par WebKit dans une vue web invisible. Il reste un programme séparé, qui parle par fichiers.

## Construire

    Backends/pythia/wasm/build.sh node    # prototype : lit les vrais fichiers du Mac, pour comparer
    Backends/pythia/wasm/build.sh web     # le module de l'iPad

Prérequis hors dépôt : Emscripten dans `~/Library/TreeLevelMC/tools/emsdk` (emsdk, Python ≥ 3.10 par
`EMSDK_PYTHON`), sources de Pythia 8.318 dans `~/Library/TreeLevelMC/tarballs/pythia8318`.

## Ce qui est établi (30/09)

- Pythia 8.318 → 8,6 Mo de WebAssembly (107 fichiers, Emscripten 6.0.10, -O3) ; seule retouche : `XMLDIR`.
- **Mêmes événements que le natif 8.318**, à l'arrondi près : même structure, mêmes particules, sur 10 200
  événements ; seuls les derniers chiffres diffèrent (≤ 3·10⁻⁶ relatif, bibliothèque mathématique).
- σ identiques : e⁺e⁻ → b b̄ habillé 3,114 pb ; machine e⁻e⁺ 200 GeV 1078 pb (10 000 év.).
- Temps (Node, Mac M) : environ trois fois le natif — 10 000 événements de la machine en 0,8 s.
- Données : xmldoc 3,7 Mo, tunes 0,2 Mo, setups 1,6 Mo pour les leptons ; pdfdata 53 Mo en plus pour les
  hadrons. Depuis 8.31x, Monash des leptons se lit dans `tunes/` : ne pas l'oublier dans le paquet.

## À faire

1. Cible « web » : monter les données dans le système de fichiers d'Emscripten sous `/pythia`, passer
   `job.json`, récupérer `events.hepmc` et `status`.
2. TreeLevel iPad : une vue web invisible (WKWebView) qui charge le module depuis Application Support, un
   gestionnaire de schéma d'URL pour lui servir les fichiers, la même interface que le moteur du Mac.
3. Réglages de l'iPad : « Module Pythia », téléchargement depuis la release, empreinte fixée dans l'app.
4. Release GitHub du module (WebAssembly, données, sources, licence).
5. Mesurer sur un iPad réel (simulateur puis appareil), et expliquer le module dans les notes de revue.
