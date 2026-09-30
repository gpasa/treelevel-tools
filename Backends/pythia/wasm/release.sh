#!/bin/sh
# Publie le module Pythia de l'iPad : une pré-release GitHub « ipad-pythia-<version> » de gpasa/treelevel-tools.
#
#   Backends/pythia/wasm/release.sh 8.318            prépare build/release-ipad et affiche les empreintes
#   Backends/pythia/wasm/release.sh 8.318 --upload   et crée la release (gh authentifié)
#
# Des fichiers séparés, pas une archive : iOS ne décompresse rien sans bibliothèque, et chaque fichier est vérifié
# par l'app contre une empreinte fixée dans son code (PythiaModuleInstaller). Les sources de Pythia accompagnent le
# binaire, comme la GPL le demande ; celles du pilote et de runner.js sont dans le dépôt, à l'étiquette de la release.
set -e
VERSION=${1:?version de Pythia, par exemple 8.318}
ICI=$(cd "$(dirname "$0")" && pwd)
PYTHIA=${PYTHIA_SRC:-$HOME/Library/TreeLevelMC/tarballs/pythia$(echo "$VERSION" | tr -d .)}
TARBALL="$PYTHIA.tgz"
[ -f "$TARBALL" ] || { echo "sources introuvables : $TARBALL" >&2; exit 1; }
"$ICI/build.sh" web >/dev/null
OUT="$ICI/build/release-ipad"
rm -rf "$OUT"; mkdir -p "$OUT"
for f in treelevel-pythia-web.js treelevel-pythia-web.wasm runner.js leptons.pack pdfdata.pack; do cp "$ICI/build/web/$f" "$OUT/"; done
cp "$TARBALL" "$OUT/pythia$(echo "$VERSION" | tr -d .)-sources.tgz"
cp "$PYTHIA/COPYING" "$OUT/COPYING.pythia8"
(cd "$OUT" && shasum -a 256 * > SHA256SUMS.txt)
cat > "$OUT/notes.md" <<NOTES
# Module Pythia $VERSION pour TreeLevel sur iPad

Pythia 8 compilé en WebAssembly, avec le pilote commun de TreeLevel Tools. TreeLevel sur iPad le télécharge
depuis cette page, fichier par fichier, et vérifie chacun contre une empreinte fixée dans l'app ; il le fait
tourner dans une vue web, sans rien envoyer nulle part. Les événements en sortent gerbés et hadronisés, et la
source Machine de TreeLevel devient disponible sur iPad.

| fichier | rôle |
|---|---|
| \`treelevel-pythia-web.wasm\`, \`.js\` | Pythia $VERSION et le pilote, en WebAssembly |
| \`runner.js\` | mène un travail de TreeLevel : plan, parties, réunion |
| \`leptons.pack\` | données de Pythia (xmldoc, tunes, setups) — faisceaux de leptons |
| \`pdfdata.pack\` | densités de partons — faisceaux de hadrons, facultatif |
| \`pythia$(echo "$VERSION" | tr -d .)-sources.tgz\` | les sources de Pythia $VERSION, telles que publiées sur pythia.org |
| \`COPYING.pythia8\` | la licence de Pythia (GPL v2 ou ultérieure) |

Pythia 8 est un logiciel libre de la collaboration Pythia (pythia.org), distribué sous GPL v2 ou ultérieure.
Il reste un programme séparé de TreeLevel : l'app lui passe un travail et relit le résultat. Les sources du
pilote et de \`runner.js\` sont dans ce dépôt, à l'étiquette de cette release (\`Backends/pythia\`).
Sommes de contrôle dans \`SHA256SUMS.txt\`.
NOTES
cat "$OUT/SHA256SUMS.txt"
if [ "${2:-}" = "--upload" ]; then
  TAG="ipad-pythia-$VERSION"
  gh release create "$TAG" --repo gpasa/treelevel-tools --target "$(git rev-parse HEAD)" --prerelease \
     --title "Module Pythia $VERSION pour TreeLevel sur iPad" --notes-file "$OUT/notes.md" \
     "$OUT"/treelevel-pythia-web.js "$OUT"/treelevel-pythia-web.wasm "$OUT"/runner.js "$OUT"/leptons.pack \
     "$OUT"/pdfdata.pack "$OUT"/pythia*-sources.tgz "$OUT"/COPYING.pythia8 "$OUT"/SHA256SUMS.txt
  echo "→ https://github.com/gpasa/treelevel-tools/releases/tag/$TAG"
fi
