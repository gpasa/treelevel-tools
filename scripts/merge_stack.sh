#!/bin/bash
# Fond deux arbres construits par scripts/build_stack.sh — Apple Silicon et Intel, chacun sur sa machine, au
# même chemin — en un seul arbre universel.
#
#   scripts/merge_stack.sh <arbre arm64> <arbre x86_64> <arbre universel>
#
# Chaque binaire Mach-O (exécutable, .dylib, .so, archive .a) devient un binaire à deux tranches par `lipo` ;
# tout le reste doit être identique des deux côtés, et l'est presque toujours : données, PDF, xmldoc,
# en-têtes. Ce qui diffère (un script *-config qui grave « -arch », un .la) est gardé dans sa version arm64 et
# listé, pour qu'on le regarde plutôt que de le découvrir publié. Un fichier présent d'un seul côté est
# signalé de même. Le script échoue si un binaire n'a pas son jumeau : un module qui ne tournerait que sur
# une architecture est exactement ce qu'on répare ici.
set -euo pipefail
A=${1:?arbre arm64}; B=${2:?arbre x86_64}; OUT=${3:?arbre universel}
A=$(cd "$A" && pwd); B=$(cd "$B" && pwd)
rm -rf "${OUT:?}"; mkdir -p "$OUT"; OUT=$(cd "$OUT" && pwd)

is_bin() { case "$(file -b "$1" 2>/dev/null)" in *Mach-O*|*"ar archive"*) return 0 ;; *) return 1 ;; esac; }
MERGED=0; SAME=0; DIFF=(); ONLY_A=(); ONLY_B=(); ORPHANS=()

while IFS= read -r -d '' path; do
  rel=${path#"$A"/}
  [ "$path" = "$A" ] && continue
  if [ -L "$path" ]; then
    ln -s "$(readlink "$path")" "$OUT/$rel"
    [ -L "$B/$rel" ] || ONLY_A+=("$rel")
  elif [ -d "$path" ]; then
    mkdir -p "$OUT/$rel"
  elif [ ! -e "$B/$rel" ]; then
    cp -p "$path" "$OUT/$rel"; ONLY_A+=("$rel")
    is_bin "$path" && ORPHANS+=("$rel")
  elif is_bin "$path" && is_bin "$B/$rel"; then
    if lipo "$path" -verify_arch x86_64 2>/dev/null; then
      cp -p "$path" "$OUT/$rel"                   # déjà universel (le runtime gfortran, par exemple)
    else
      lipo -create "$path" "$B/$rel" -output "$OUT/$rel"
      chmod "$(stat -f %Lp "$path")" "$OUT/$rel"
    fi
    MERGED=$((MERGED + 1))
  elif cmp -s "$path" "$B/$rel"; then
    cp -p "$path" "$OUT/$rel"; SAME=$((SAME + 1))
  else
    cp -p "$path" "$OUT/$rel"; DIFF+=("$rel")
  fi
done < <(find "$A" -print0)

while IFS= read -r -d '' path; do
  rel=${path#"$B"/}
  [ -e "$A/$rel" ] || [ -L "$A/$rel" ] || { ONLY_B+=("$rel"); is_bin "$path" && ORPHANS+=("$rel"); }
done < <(find "$B" \( -type f -o -type l \) -print0)

echo "  $MERGED binaires fusionnés, $SAME fichiers identiques"
report() { local title=$1; shift; [ $# -gt 0 ] || return 0
           echo "  $title ($#) :"; printf '     %s\n' "$@" | head -30; [ $# -le 30 ] || echo "     …"; }
report "différents, version arm64 gardée" ${DIFF[@]+"${DIFF[@]}"}
report "seulement côté arm64" ${ONLY_A[@]+"${ONLY_A[@]}"}
report "seulement côté x86_64" ${ONLY_B[@]+"${ONLY_B[@]}"}
if [ ${#ORPHANS[@]} -gt 0 ]; then
  echo "  ⚠ binaires sans jumeau — ils ne tourneraient que sur une architecture :" >&2
  printf '     %s\n' "${ORPHANS[@]}" >&2
  exit 1
fi
