# TreeLevel Tools — Windows

La même chose que sur macOS : TreeLevel écrit un dossier de travail, ce programme y fait tourner un générateur
et réécrit les événements en HepMC3. Le protocole est identique au bit près — un dossier écrit sur un Mac se
relit ici et inversement.

```
treelevel-tools run <dossier> [--docker]            exécute job.json, produit events.hepmc, tient status.json à jour
treelevel-tools capabilities [--out f] [--docker]   les générateurs installés, en JSON
treelevel-tools serve <dossier> [--docker]          reste à l'écoute d'un dossier de travaux partagé
treelevel-tools version
```

`--docker` est la case des Réglages de TreeLevel « Tout faire tourner dans l'image Docker » : tout passe alors
par l'image, et rien n'est proposé quand Docker ou l'image manque — jamais de repli silencieux sur le natif, qui
ne porte pas les mêmes constructions.

## Ce qui tourne, et comment

Trois pièces, comme sur le Mac :

| Pièce | Rôle |
|---|---|
| `treelevel-tools.exe` (C#, `treelevel-tools/`) | l'hôte que TreeLevel lance : trouve Docker et l'image, le module Pythia, écrit `launch.json` |
| `treelevel-engine.exe` (C++, `engine/`) | le moteur : **le même source** que celui de l'image et du Mac (`Backends/engine/engine.cpp`) ; il écrit la carte de chaque générateur et le mène |
| `Modules\pythia8\` (`backends/pythia/`) | le pilote Pythia partagé (`Backends/pythia/main.cpp`), qui écrit lui-même sa carte |

| Générateur | Sur Windows |
|---|---|
| Sans gerbe (`passthrough`) | natif, dans le moteur C++ |
| Pythia 8 | natif, MSVC ; dans l'image avec `--docker` |
| Herwig 7, Sherpa 3, WHIZARD 3, CalcHEP 3 | dans l'image : aucun n'a de version Windows |

Pythia, Herwig, Sherpa, WHIZARD et CalcHEP sont sous **GPL** : ce dépôt est GPL v3, et aucun de leurs fichiers
n'y est recopié. Vous construisez Pythia avec le script ci-dessous ; les autres arrivent construits dans
l'image, dont la recette et les sources sont publiées avec elle. Leurs auteurs et licences : [`CREDITS.md`](../CREDITS.md).

## Construire

.NET 8 et Visual Studio (charge « Développement Desktop en C++ ») suffisent.

```powershell
cd win\treelevel-tools
dotnet publish -c Release -r win-arm64   # ou win-x64 : l'hôte, un seul exécutable
..\engine\build.ps1                      # le moteur C++, pour l'architecture de la machine
```

`package\release.ps1` fait les trois pièces et l'archive d'un coup. Le moteur C++ doit être **à côté** de
`treelevel-tools.exe`. TreeLevel cherche l'hôte à côté de lui, dans `%LOCALAPPDATA%\Programs\TreeLevel Tools`,
dans `%ProgramFiles%\TreeLevel Tools`, dans votre dossier personnel, puis dans le PATH.

Le moteur C++ ne diffère sous Windows que par sa plomberie, derrière `_WIN32` : `CreateProcess` au lieu de
`fork`/`exec`, et un remplacement de `status.json` qui marche quand la cible existe (`MoveFileEx`). Un manifeste
(`engine/utf8.manifest`, repris par le pilote Pythia) fait de l'UTF-8 la page de code de tous les appels : un
dossier de travail sous un nom d'utilisateur accentué s'ouvre comme un autre.

> TreeLevel est empaqueté en MSIX, et un paquet MSIX détourne les écritures dans `%LOCALAPPDATA%` vers son
> propre conteneur : un programme extérieur ne verrait pas ce qu'il y écrit. Les dossiers de travail sont donc
> créés **à côté du moteur** (`<dossier du moteur>\MCJobs\<id>`), et les capacités sont lues en lançant
> `treelevel-tools capabilities` plutôt qu'en ouvrant le fichier publié.

## Construire le module Pythia 8

Pythia n'a pas de système de construction pour Windows. `backends/pythia` compile ses sources directement avec
MSVC, sans en modifier une ligne : la seule chose qui manque à Windows, `<dlfcn.h>` — que `PythiaStdlib.h`
inclut sans condition et dont `Plugins.cc` se sert pour charger des greffons —, est fournie par
`backends/pythia/compat/dlfcn.h`, une trentaine de lignes au-dessus de `LoadLibrary`.

```powershell
# 1. les sources, depuis https://pythia.org (n'importe quelle version 8.3)
curl.exe -L -o pythia8318.tar.gz https://gitlab.com/Pythia8/releases/-/archive/pythia8318/releases-pythia8318.tar.gz
mkdir "$env:LOCALAPPDATA\TreeLevel Tools\src"
tar.exe xzf pythia8318.tar.gz -C "$env:LOCALAPPDATA\TreeLevel Tools\src"

# 2. le module
cd win\backends\pythia
.\build.ps1 -Pythia "$env:LOCALAPPDATA\TreeLevel Tools\src\pythia8318"
```

Le script trouve Visual Studio et son CMake tout seul, construit pour l'architecture de la machine (`-Arch x64`
ou `-Arch arm64` pour en changer) et installe le pilote **et son `xmldoc`** dans
`%LOCALAPPDATA%\TreeLevel Tools\Modules\pythia8`, où le moteur va les chercher. Le runtime C++ est lié
statiquement : le module tourne sur une machine sans redistribuable Visual C++.

Les 107 unités de compilation de Pythia prennent quelques minutes la première fois.

```powershell
treelevel-tools capabilities     # pythia8 doit apparaître, avec sa version
```

## Herwig, Sherpa, WHIZARD, CalcHEP : l'image

Aucun n'a de version Windows, et ce n'est pas une affaire de drapeaux de compilation : Sherpa charge ses modules
avec `dlopen` et s'appuie sur `sys/resource.h`, Herwig repose sur le dépôt de classes chargées à l'exécution de
ThePEG, sur autotools et sur du Fortran ; WHIZARD et CalcHEP compilent chaque processus. Ils tournent donc dans
un conteneur Linux, que l'utilisateur récupère d'une commande :

```powershell
docker pull ghcr.io/gpasa/treelevel-tools:latest
```

Le moteur qui tourne dans l'image est **le même source** que `treelevel-engine.exe`, compilé pour Linux : il
lit le même `job.json` et écrit le même `status.json`. Le dossier de travail est monté tel quel, donc rien
n'est copié ni converti — voir [`docker/README.md`](../docker/README.md) pour ce que l'image contient et d'où
viennent ses sources.

L'hôte vérifie que le démon Docker répond, que l'image est **déjà** présente (`docker image inspect`, l'étiquette
du protocole puis `latest` — rien n'est jamais téléchargé sans qu'on le demande), puis lance

```
docker run --rm -v "<dossier de travail>:/job" <image> run /job
```

et laisse le conteneur écrire lui-même sa progression. Si Docker n'est pas là, ces générateurs ne sont pas
proposés, et un travail qui les demande échoue tout de suite avec la raison. Les versions venues de l'image
portent « (Docker) », dans les capacités comme dans le statut d'un travail fini.

> **Machines virtuelles.** Docker Desktop fait tourner son moteur dans WSL2, c'est-à-dire dans une machine
> virtuelle Hyper-V. Sur un PC réel la virtualisation est active d'origine ; dans un invité Windows, il faut
> que l'hôte expose la **virtualisation imbriquée** — sur un Mac, une puce M3 ou M4 avec Parallels 19+.
> Sans elle, Docker s'installe mais son moteur ne démarre pas. Pythia, lui, tourne partout.

## Différences avec macOS

* Les chemins du support sont `%LOCALAPPDATA%\TreeLevel Tools\` au lieu de
  `~/Library/Application Support/TreeLevel Tools/`.
* L'hôte est écrit en C# plutôt qu'en Swift ; le protocole, lui, est le même fichier de part et d'autre
  (`MCEngineProtocol.cs` ↔ `Protocol/MCEngineProtocol.swift`), y compris la forme exacte du JSON que
  `Codable` produit : clés en camel, énumérations en minuscules, dates en secondes depuis le 1er janvier 2001.
* Seuls Pythia et le passage sans gerbe tournent en natif ; le reste passe par l'image, là où le Mac a aussi
  ses modules natifs.
* Le choix de l'image se fait dans les Réglages de TreeLevel (passé en `--docker`), et non dans une fenêtre du
  moteur, que Windows n'a pas.

## Mesuré

Pythia 8.318 construit avec MSVC 14.51 (Visual Studio 2026) sur Windows 11 ARM64, puis, sur 200 événements
e⁻e⁺ → b b̄ à 200 GeV écrits par TreeLevel :

```
treelevel-tools run <dossier>
  → 200 événements gerbés et hadronisés en 1,0 s, aucune erreur Pythia
  → σ = 3.11399 pb, celle du fichier d'entrée, reportée telle quelle dans status.json
  → feyn analyze : 31,9 photons, 24,2 pions, 3,6 kaons et 1,3 nucléon par événement en moyenne,
    2,06 jets (anti-k_T), thrust piqué à 0,95 — deux jets, avec la queue à trois jets du rayonnement de gluon
```

Trois choses seulement manquaient à Pythia pour compiler avec MSVC, et aucune ne demande de toucher à ses
sources : `<dlfcn.h>` et `clock_gettime`, fournis par `compat/`, et trois définitions passées au compilateur
(`_USE_MATH_DEFINES` pour `M_E`, `fjcore_EXPORTS` pour les membres statiques de FJcore, `XMLDIR` pour le
chemin de repli des données).
