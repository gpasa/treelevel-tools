#!/bin/bash
# Builds, signs, notarises and packages TreeLevel Tools for distribution outside the App Store.
# Everything happens on this machine: the Developer ID key never leaves the keychain.
#
#   scripts/release.sh                 build, sign, notarise, staple, make the disk image
#   scripts/release.sh 0.2.0           the same, with that version number
#   scripts/release.sh --no-notarize   stop after signing (offline check of the build)
#   scripts/release.sh --upload        also create the GitHub release mac-<version> (gh authenticated)
#
# Prerequisites, done once:
#   • a "Developer ID Application" certificate of the G2 authority in the keychain — from the developer site,
#     choosing "G2 Sub-CA" (Xcode › Manage Certificates › + issues one from the previous authority, which
#     stops on 1 February 2027); scripts/devid_identity.sh finds it
#   • notarisation credentials:  xcrun notarytool store-credentials "TreeLevelMC" \
#         --apple-id <apple id> --team-id 9LVGAJ594U --password <app-specific password>
set -euo pipefail
cd "$(dirname "$0")/.."

# L'identité de l'autorité G2, désignée par son empreinte : plusieurs certificats portent le même nom (ceux de
# l'ancienne autorité cessent le 1ᵉʳ février 2027), et codesign refuse un nom ambigu. IDENTITY=… la remplace.
IDENTITY=${IDENTITY:-$(scripts/devid_identity.sh)}
PROFILE=${NOTARY_PROFILE:-TreeLevelMC}
NOTARIZE=1
UPLOAD=0
VERSION=""
for arg in "$@"; do
  case "$arg" in
    --no-notarize) NOTARIZE=0 ;;
    --upload) UPLOAD=1 ;;
    -*) echo "unknown option $arg" >&2; exit 2 ;;
    *) VERSION=$arg ;;
  esac
done

say() { printf '\n\033[1m%s\033[0m\n' "$*"; }

# --- Checks -----------------------------------------------------------------
security find-identity -v -p codesigning | grep -q "$IDENTITY" || {
  echo "no '$IDENTITY' certificate in the keychain — create one in Xcode › Settings › Accounts › Manage Certificates" >&2
  exit 1
}
if [ "$NOTARIZE" = 1 ]; then
  xcrun notarytool history --keychain-profile "$PROFILE" >/dev/null 2>&1 || {
    echo "no notarisation credentials named '$PROFILE' — run: xcrun notarytool store-credentials \"$PROFILE\" …" >&2
    exit 1
  }
fi
command -v xcodegen >/dev/null || { echo "xcodegen is needed to generate the project" >&2; exit 1; }

# --- Version ----------------------------------------------------------------
if [ -n "$VERSION" ]; then
  /usr/bin/sed -i '' "s/MARKETING_VERSION: \".*\"/MARKETING_VERSION: \"$VERSION\"/" App/project.yml
  /usr/bin/sed -i '' "s/let engineVersion = \".*\"/let engineVersion = \"$VERSION\"/" Sources/treelevel-tools/main.swift
  /usr/bin/sed -i '' "s/let version = \".*\"/let version = \"$VERSION\"/" App/Sources/EngineApp.swift
else
  VERSION=$(grep -m1 'MARKETING_VERSION' App/project.yml | sed 's/.*"\(.*\)".*/\1/')
fi
BUILD=$(git rev-list --count HEAD 2>/dev/null || echo 1)
say "TreeLevel Tools $VERSION (build $BUILD)"

OUT="build/release"
rm -rf "$OUT"
mkdir -p "$OUT"

# --- Build ------------------------------------------------------------------
say "Command line tool"
# Universels, comme l'application : un iMac Intel les exécute aussi (la 0.4.0 publiée d'abord ne les
# avait qu'en arm64 — rien ne tournait sur Intel).
/usr/bin/swift build -c release --arch arm64 --arch x86_64
BIN=.build/apple/Products/Release
# Le moteur C++ : les cartes de tous les générateurs, les mêmes que dans l'image Linux.
/usr/bin/clang++ -O2 -std=c++17 -arch arm64 -arch x86_64 -mmacosx-version-min=13.0 -I Backends/pythia \
  Backends/engine/engine.cpp -o "$BIN/treelevel-engine"
say "Application"
(cd App && xcodegen generate >/dev/null)
xcodebuild -project App/TreeLevelMCEngine.xcodeproj -scheme TreeLevelMCEngine -configuration Release \
  -derivedDataPath App/build CURRENT_PROJECT_VERSION="$BUILD" CODE_SIGNING_ALLOWED=NO | grep -E "error:|warning: unable|BUILD" || true
APP_SRC="App/build/Build/Products/Release/TreeLevel Tools.app"
[ -d "$APP_SRC" ] || { echo "the application was not built" >&2; exit 1; }
APP="$OUT/TreeLevel Tools.app"
cp -R "$APP_SRC" "$APP"
cp "$BIN/treelevel-tools" "$APP/Contents/MacOS/treelevel-tools"
cp "$BIN/treelevel-engine" "$APP/Contents/MacOS/treelevel-engine"
for f in "$APP/Contents/MacOS/"*; do
  lipo "$f" -verify_arch arm64 x86_64 || { echo "$f n'est pas universel" >&2; exit 1; }
done

# --- Modules -----------------------------------------------------------------
# L'utilisateur n'installe qu'une application : les générateurs voyagent dedans. Ils ont été rendus
# relogeables et signés par scripts/package_module.sh, qui a aussi vérifié qu'aucun chemin de cette
# machine ne les accompagne.
MODULES_SRC="build/modules/stage"
if [ -d "$MODULES_SRC" ]; then
  say "Modules embarqués"
  mkdir -p "$APP/Contents/Resources/Modules"
  for module in "$MODULES_SRC"/*/; do
    name=$(basename "$module")
    # WHIZARD ne tourne pas en natif sur macOS — il compile chaque processus avec gfortran, que le système
    # ne fournit pas — et l'application ne le propose donc que par le conteneur, qui l'emporte déjà.
    # L'embarquer coûterait 190 Mo au téléchargement pour un générateur qui ne démarrerait jamais.
    if [ "$name" = "whizard3" ]; then echo "  $name — écarté (conteneur seulement)"; continue; fi
    rsync -a "$module" "$APP/Contents/Resources/Modules/$name/"
    echo "  $name ($(du -sh "$module" | cut -f1))"
  done
else
  echo "  (aucun module : scripts/package_module.sh n'a pas tourné)"
fi

# Chaque binaire embarqué doit tourner sur les deux architectures et dès macOS 13, comme l'application. La
# première 0.4.0 est partie avec des générateurs arm64 seulement, et liés à des bibliothèques qui exigeaient
# macOS 26 : rien ne le disait, et un iMac Intel n'avait que CalcHEP, qui échouait au premier travail.
say "Architectures et version minimale"
BAD_BIN=""
while IFS= read -r -d '' f; do
  # Les objets .o de CalcHEP sont séparés exprès par architecture (la notarisation refuse un .o universel) ;
  # ld_n choisit celui de la machine.
  case "$(file -b "$f")" in *"Mach-O"*object*) continue ;; *Mach-O*) ;; *) continue ;; esac
  lipo "$f" -verify_arch arm64 x86_64 2>/dev/null || BAD_BIN="$BAD_BIN
  pas universel   ${f#$APP/}"
  for v in $(vtool -show-build "$f" 2>/dev/null | awk '$1=="minos"{print $2}'); do
    [ "$(printf '%s\n13.0\n' "$v" | sort -V | tail -1)" = "13.0" ] || BAD_BIN="$BAD_BIN
  macOS $v requis   ${f#$APP/}"
  done
done < <(find "$APP/Contents" -type f -print0)
if [ -n "$BAD_BIN" ]; then
  echo "  ⚠ binaires qui ne tourneraient pas partout :" >&2
  printf '%s\n' "$BAD_BIN" | grep -v '^$' | sort -u | head -30 >&2
  exit 1
fi
echo "  tout est universel et vise macOS 13"

# --- Sign -------------------------------------------------------------------
# Nested binaries first, then the bundle; hardened runtime and a secure timestamp, both required for notarisation.
say "Signature"
find "$APP/Contents/MacOS" -type f -perm +111 -print0 | while IFS= read -r -d '' binary; do
  [ "$binary" = "$APP/Contents/MacOS/TreeLevel Tools" ] && continue
  codesign --force --timestamp --options runtime --sign "$IDENTITY" "$binary"
done
# Les modules sont déjà signés — CalcHEP avec sa dérogation de validation de bibliothèques, que
# --force écraserait : ne toucher qu'à ce qui ne l'est pas encore.
codesign --force --timestamp --options runtime --sign "$IDENTITY" "$APP"
codesign --verify --strict --verbose=1 "$APP"

# --- Notarise the application ------------------------------------------------
ZIP="$OUT/TreeLevelTools-$VERSION.zip"
/usr/bin/ditto -c -k --keepParent "$APP" "$ZIP"
if [ "$NOTARIZE" = 1 ]; then
  say "Notarisation de l'application"
  xcrun notarytool submit "$ZIP" --keychain-profile "$PROFILE" --wait
  xcrun stapler staple "$APP"
  rm -f "$ZIP"
  /usr/bin/ditto -c -k --keepParent "$APP" "$ZIP"
fi

# --- Disk image --------------------------------------------------------------
say "Image disque"
DMG="$OUT/TreeLevelTools-$VERSION.dmg"
STAGE=$(mktemp -d)
cp -R "$APP" "$STAGE/"
cp README.md "$STAGE/Lisez-moi.md"
cp LICENSE "$STAGE/LICENSE"
ln -s /Applications "$STAGE/Applications"
hdiutil create -volname "TreeLevel Tools $VERSION" -srcfolder "$STAGE" -ov -format UDZO "$DMG" >/dev/null
rm -rf "$STAGE"
codesign --force --timestamp --sign "$IDENTITY" "$DMG"
if [ "$NOTARIZE" = 1 ]; then
  say "Notarisation de l'image"
  xcrun notarytool submit "$DMG" --keychain-profile "$PROFILE" --wait
  xcrun stapler staple "$DMG"
  spctl -a -t open --context context:primary-signature -v "$DMG" || true
fi

# --- Checksums and notes ------------------------------------------------------
(cd "$OUT" && shasum -a 256 *.dmg *.zip > SHA256SUMS.txt)
# Les notes en onze langues (scripts/gh_pages.py) : docs/release-notes/<version>/<langue>.md, l'anglais d'abord et
# chaque autre langue dans un bloc dépliable, puis les crédits. GitHub ne choisit pas la langue : un lien mène au
# site, qui le fait.
if [ -d "docs/release-notes/$VERSION" ]; then
  python3 scripts/gh_pages.py tools "$VERSION" "$OUT/release-notes.md"
else
  echo "⚠ docs/release-notes/$VERSION absent : notes réduites aux crédits, à écrire avant --upload" >&2
  { printf '# TreeLevel Tools %s\n\n' "$VERSION"; cat CREDITS.md; } > "$OUT/release-notes.md"
fi
say "Prêt"
ls -lh "$OUT" | sed 's/^/  /'

# --- Optional: publish on GitHub ---------------------------------------------
# Le dépôt public est https://github.com/gpasa/treelevel-tools ; `gh` doit être authentifié.
if [ "$UPLOAD" = 1 ]; then
  say "Publication"
  command -v gh >/dev/null || { echo "gh n'est pas installé" >&2; exit 1; }
  # Les releases du dépôt portent leur plateforme : mac-<version> ici, win-<version> pour Windows. Le tag naît
  # sur le commit d'où le paquet a été construit, qui doit être poussé.
  git push -q origin HEAD
  gh release create "mac-$VERSION" --target "$(git rev-parse HEAD)" --latest \
     --title "TreeLevel Tools $VERSION — macOS" \
     --notes-file "$OUT/release-notes.md" "$OUT"/*.dmg "$OUT"/*.zip "$OUT/SHA256SUMS.txt" \
     && echo "  release mac-$VERSION créée"
fi
