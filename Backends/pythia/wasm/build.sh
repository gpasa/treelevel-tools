#!/bin/sh
# Pythia 8 et le pilote de TreeLevel compilés en WebAssembly (Emscripten).
#
#   Backends/pythia/wasm/build.sh [node|web]
#
# « node » (le défaut) : un prototype qui lit les vrais fichiers du Mac (NODERAWFS), pour comparer sections
# efficaces et temps au pilote natif. « web » : le module que l'iPad chargera dans une vue web, fichiers en mémoire.
#
# Le pilote est le même main.cpp que sur le Mac, sous Windows et dans l'image : la même carte partout.
# Prérequis, hors du dépôt : Emscripten (emsdk) dans ~/Library/TreeLevelMC/tools/emsdk, avec un Python ≥ 3.10
# (EMSDK_PYTHON), et les sources de Pythia dans ~/Library/TreeLevelMC/tarballs/pythia8318.
set -e
CIBLE=${1:-node}
ICI=$(cd "$(dirname "$0")" && pwd)
PYTHIA=${PYTHIA_SRC:-$HOME/Library/TreeLevelMC/tarballs/pythia8318}
EMSDK=${EMSDK_DIR:-$HOME/Library/TreeLevelMC/tools/emsdk}
export EMSDK_PYTHON=${EMSDK_PYTHON:-/opt/local/bin/python3.13}
. "$EMSDK/emsdk_env.sh" >/dev/null 2>&1
SORTIE="$ICI/build"
mkdir -p "$SORTIE/obj"

# XMLDIR : là où Pythia cherche ses données faute d'autre indication ; le module web les monte là.
# La bibliothèque, une fois : ~100 fichiers, compilés en parallèle, gardés tant que les sources ne bougent pas.
LIB="$SORTIE/libpythia8.a"
if [ ! -f "$LIB" ]; then
  echo "Pythia → WebAssembly ($(ls "$PYTHIA"/src/*.cc | wc -l | tr -d ' ') fichiers)"
  export PYTHIA SORTIE
  find "$PYTHIA/src" -name '*.cc' -print0 | xargs -0 -n 1 -P "$(sysctl -n hw.ncpu)" sh -c \
    'o="$SORTIE/obj/$(basename "$1" .cc).o"; [ -f "$o" ] || em++ -O3 -std=c++17 -fexceptions -I"$PYTHIA/include" \
       -DXMLDIR=\"/pythia/xmldoc\" -c "$1" -o "$o"' _
  emar rcs "$LIB" "$SORTIE"/obj/*.o
fi

COMMUN="-O3 -std=c++17 -fexceptions -I$PYTHIA/include -I$ICI/.. -sALLOW_MEMORY_GROWTH=1 -sSTACK_SIZE=8MB"
case "$CIBLE" in
  node)
    em++ $COMMUN "$ICI/../main.cpp" "$LIB" -o "$SORTIE/treelevel-pythia.js" \
      -sNODERAWFS=1 -sEXIT_RUNTIME=1 -sENVIRONMENT=node --pre-js "$ICI/node-env.js"
    echo "→ $SORTIE/treelevel-pythia.js (+ .wasm), à lancer par node" ;;
  web)
    # Le module de l'iPad : une instance par travail, les fichiers en mémoire, les données en deux paquets.
    WEB="$SORTIE/web"; mkdir -p "$WEB"
    em++ $COMMUN "$ICI/../main.cpp" "$LIB" -o "$WEB/treelevel-pythia-web.js" \
      -sMODULARIZE=1 -sEXPORT_NAME=TreeLevelPythia -sENVIRONMENT=web,worker -sINVOKE_RUN=0 -sEXIT_RUNTIME=1 \
      -sFORCE_FILESYSTEM=1 -sEXPORTED_RUNTIME_METHODS=FS,callMain,ENV
    DATA=$(dirname "$PYTHIA")/$(basename "$PYTHIA")/share/Pythia8
    python3 "$ICI/pack.py" "$WEB/leptons.pack" "$DATA/xmldoc@/pythia/xmldoc" "$DATA/tunes@/pythia/tunes" \
      "$DATA/setups@/pythia/setups"
    python3 "$ICI/pack.py" "$WEB/pdfdata.pack" "$DATA/pdfdata@/pythia/pdfdata"
    cp "$ICI/runner.js" "$ICI/test.html" "$WEB/"
    mkdir -p "$WEB/jobs"; cp -R "$ICI/../../../docker/test-job" "$ICI/../../../docker/test-job-machine" "$WEB/jobs/"
    ls -la "$WEB"/*.wasm "$WEB"/*.pack | awk '{print "  " $5 " octets  " $9}'
    echo "→ $WEB" ;;
esac
[ "$CIBLE" = node ] && ls -la "$SORTIE"/*.wasm | awk '{print "  " $5 " octets  " $9}'
true
