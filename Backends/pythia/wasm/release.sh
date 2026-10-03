#!/bin/sh
# Publie le module Pythia de l'iPad sous un nom stable : la release GitHub « ipad-pythia » de gpasa/treelevel-tools,
# dont les fichiers gardent toujours le même nom. Chaque app télécharge la dernière version publiée, lit son numéro
# dans module.json et l'affiche : le numéro ne fait pas partie du nom.
#
#   Backends/pythia/wasm/release.sh 0.5.0            prépare build/release-ipad et affiche module.json
#   Backends/pythia/wasm/release.sh 0.5.0 --upload   et publie (gh authentifié) : crée la release, ou remplace ses
#                                                    fichiers, module.json en dernier
#
# module.json dit la version du module (celle de TreeLevel Tools dont vient le pilote), celle de Pythia, ce que le
# pilote sait faire (`--features`, ex. « spacetime ») et l'empreinte de chaque fichier, que l'app vérifie avant
# d'installer. Des fichiers séparés, pas une archive : iOS ne décompresse rien sans bibliothèque.
#
# Compatibilité : un module plus récent mène les travaux d'une app plus ancienne (une clé inconnue de lui est
# ignorée, une clé absente prend son défaut) ; une app plus récente devant un module plus ancien n'offre que ce
# qu'il annonce. L'ancienne release « ipad-pythia-8.318 », dont TreeLevel 1.3 fixe les empreintes dans son code,
# n'est jamais touchée.
set -e
MODULE=${1:?version du module, par exemple 0.5.0}
PYTHIA_VERSION=${PYTHIA_VERSION:-8.318}
ICI=$(cd "$(dirname "$0")" && pwd)
PYTHIA=${PYTHIA_SRC:-$HOME/Library/TreeLevelMC/tarballs/pythia$(echo "$PYTHIA_VERSION" | tr -d .)}
TARBALL="$PYTHIA.tgz"
[ -f "$TARBALL" ] || { echo "sources introuvables : $TARBALL" >&2; exit 1; }
"$ICI/build.sh" web >/dev/null
OUT="$ICI/build/release-ipad"
rm -rf "$OUT"; mkdir -p "$OUT"
for f in treelevel-pythia-web.js treelevel-pythia-web.wasm runner.js leptons.pack pdfdata.pack; do cp "$ICI/build/web/$f" "$OUT/"; done
SOURCES="pythia$(echo "$PYTHIA_VERSION" | tr -d .)-sources.tgz"
cp "$TARBALL" "$OUT/$SOURCES"
cp "$PYTHIA/COPYING" "$OUT/COPYING.pythia8"
# Ce que le pilote sait faire : la réponse de `--features`, lue dans sa source (le module web ne se lance pas ici).
FEATURES=$(sed -n 's/.*a == "--features".*std::cout << "\([^"]*\)".*/\1/p' "$ICI/../main.cpp")
[ -n "$FEATURES" ] || { echo "« --features » introuvable dans main.cpp" >&2; exit 1; }
python3 - "$OUT" "$MODULE" "$PYTHIA_VERSION" "$FEATURES" <<'PY'
import hashlib, json, os, sys
out, module, pythia, features = sys.argv[1:5]
files = []
for name, hadrons in [("treelevel-pythia-web.wasm", False), ("treelevel-pythia-web.js", False), ("runner.js", False),
                      ("leptons.pack", False), ("pdfdata.pack", True)]:
    data = open(os.path.join(out, name), "rb").read()
    files.append({"name": name, "sha256": hashlib.sha256(data).hexdigest(), "size": len(data), "hadrons": hadrons})
manifest = {"module": module, "pythia": pythia, "features": features.split(), "files": files}
json.dump(manifest, open(os.path.join(out, "module.json"), "w"), indent=2)
PY
(cd "$OUT" && shasum -a 256 * > SHA256SUMS.txt)
cat > "$OUT/notes.md" <<NOTES
# Module Pythia pour TreeLevel sur iPad

Version du module : **$MODULE** — Pythia **$PYTHIA_VERSION**, compilé en WebAssembly avec le pilote commun de
TreeLevel Tools $MODULE. Cette page garde toujours le même nom : TreeLevel sur iPad (1.4 et plus récent) y prend la
dernière version, lit son numéro dans \`module.json\` et l'affiche dans ses réglages, propose la mise à jour quand
une version plus récente paraît, et vérifie chaque fichier contre l'empreinte que \`module.json\` en donne. Il le
fait tourner dans une vue web, sans rien envoyer nulle part.

Ce que ce module sait faire : \`$FEATURES\`. « spacetime » : placer partons et hadrons dans la zone d'interaction,
que TreeLevel montre au femtomètre.

| fichier | rôle |
|---|---|
| \`module.json\` | version du module et de Pythia, ce qu'il sait faire, l'empreinte de chaque fichier |
| \`treelevel-pythia-web.wasm\`, \`.js\` | Pythia $PYTHIA_VERSION et le pilote, en WebAssembly |
| \`runner.js\` | mène un travail de TreeLevel : plan, parties, réunion |
| \`leptons.pack\` | données de Pythia (xmldoc, tunes, setups) — faisceaux de leptons |
| \`pdfdata.pack\` | densités de partons — faisceaux de hadrons, facultatif |
| \`$SOURCES\` | les sources de Pythia $PYTHIA_VERSION, telles que publiées sur pythia.org |
| \`COPYING.pythia8\` | la licence de Pythia (GPL v2 ou ultérieure) |

TreeLevel 1.3 sur iPad télécharge son module depuis
[ipad-pythia-8.318](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia-8.318), dont il fixe les
empreintes : cette page-là ne change pas.

## Pythia 8, ses auteurs

Pythia 8 est © Torbjörn Sjöstrand et la collaboration Pythia — [pythia.org](https://pythia.org) — et distribué
sous GPL v2 ou ultérieure. Toute la physique de ce module est la leur. Si vous publiez un résultat obtenu avec lui,
citez : C. Bierlich et al., « A comprehensive guide to the physics and usage of PYTHIA 8.3 »,
*SciPost Phys. Codebases* 8 (2022), [arXiv:2203.11601](https://arxiv.org/abs/2203.11601).

Les autres générateurs pilotés par TreeLevel Tools, et leurs auteurs :
[CREDITS.md](https://github.com/gpasa/treelevel-tools/blob/main/CREDITS.md).

Il reste un programme séparé de TreeLevel : l'app lui passe un travail et relit le résultat. Les sources du
pilote et de \`runner.js\` sont dans ce dépôt (\`Backends/pythia\`), à l'étiquette \`ipad-pythia-module-$MODULE\`.
Sommes de contrôle dans \`SHA256SUMS.txt\`.
NOTES
cat "$OUT/module.json"
if [ "${2:-}" = "--upload" ]; then
  TAG="ipad-pythia"
  REPO=gpasa/treelevel-tools
  # L'état exact des sources de cette version, à une étiquette qui ne bouge pas, elle.
  git tag -f "ipad-pythia-module-$MODULE" HEAD >/dev/null && git push -f origin "ipad-pythia-module-$MODULE" >/dev/null 2>&1
  DATA="$OUT/treelevel-pythia-web.js $OUT/treelevel-pythia-web.wasm $OUT/runner.js $OUT/leptons.pack $OUT/pdfdata.pack $OUT/$SOURCES $OUT/COPYING.pythia8 $OUT/SHA256SUMS.txt"
  if gh release view "$TAG" --repo "$REPO" >/dev/null 2>&1; then
    # Les fichiers d'abord, module.json en dernier : une app qui passe entre les deux voit des empreintes qui ne
    # correspondent pas, et n'installe rien.
    # shellcheck disable=SC2086
    gh release upload "$TAG" --repo "$REPO" --clobber $DATA
    gh release upload "$TAG" --repo "$REPO" --clobber "$OUT/module.json"
    gh release edit "$TAG" --repo "$REPO" --title "Module Pythia pour TreeLevel sur iPad — module $MODULE, Pythia $PYTHIA_VERSION" --notes-file "$OUT/notes.md" --latest=false
  else
    # shellcheck disable=SC2086
    gh release create "$TAG" --repo "$REPO" --target "$(git rev-parse HEAD)" --latest=false \
       --title "Module Pythia pour TreeLevel sur iPad — module $MODULE, Pythia $PYTHIA_VERSION" --notes-file "$OUT/notes.md" $DATA "$OUT/module.json"
  fi
  echo "→ https://github.com/$REPO/releases/tag/$TAG"
fi
