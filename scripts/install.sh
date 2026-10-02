#!/bin/sh
# Builds the engine and installs it where everything the user opens lives: ~/Applications.
# The Pythia driver goes to its module folder. Nothing is left in /Applications or in a build directory.
set -e
cd "$(dirname "$0")/.."
APPS="$HOME/Applications"
DEST="$APPS/TreeLevel Tools.app"

/usr/bin/swift build -c release
# Le moteur C++ : les cartes de tous les générateurs, les mêmes que dans l'image Linux.
/usr/bin/clang++ -O2 -std=c++17 -I Backends/pythia Backends/engine/engine.cpp -o .build/release/treelevel-engine
(cd App && xcodegen generate >/dev/null)
xcodebuild -project App/TreeLevelMCEngine.xcodeproj -scheme TreeLevelMCEngine -configuration Release \
  -derivedDataPath App/build CODE_SIGNING_ALLOWED=NO | grep -E "error:|BUILD"

osascript -e 'tell application id "org.pasahome.TreeLevelTools" to quit' 2>/dev/null || true
mkdir -p "$APPS"
rm -rf "$DEST"
/usr/bin/ditto "App/build/Build/Products/Release/TreeLevel Tools.app" "$DEST"
cp .build/release/treelevel-tools "$DEST/Contents/MacOS/treelevel-tools"
cp .build/release/treelevel-engine "$DEST/Contents/MacOS/treelevel-engine"
if ID=$(scripts/devid_identity.sh 2>/dev/null); then
  codesign --force --timestamp --options runtime --sign "$ID" "$DEST/Contents/MacOS/treelevel-tools"
  codesign --force --timestamp --options runtime --sign "$ID" "$DEST/Contents/MacOS/treelevel-engine"
  codesign --force --timestamp --options runtime --sign "$ID" "$DEST"
  codesign --verify --strict "$DEST"
fi
touch "$DEST"
# Build copies would otherwise compete with this one in LaunchServices.
LSREGISTER=/System/Library/Frameworks/CoreServices.framework/Frameworks/LaunchServices.framework/Support/lsregister
"$LSREGISTER" -u "$PWD/App/build/Build/Products/Release/TreeLevel Tools.app" 2>/dev/null || true
"$LSREGISTER" -u "$PWD/build/release/TreeLevel Tools.app" 2>/dev/null || true
"$LSREGISTER" -f "$DEST" 2>/dev/null || true

if command -v pythia8-config >/dev/null || [ -f /opt/local/include/pythia/Pythia8/Pythia.h ]; then
  make -C Backends/pythia install >/dev/null && echo "→ module Pythia dans ~/Library/Application Support/TreeLevel Tools/Modules/pythia8"
fi
echo "→ $DEST  ($(stat -f "%Sm" -t "%d %b %H:%M" "$DEST/Contents/MacOS/TreeLevel Tools"))"
