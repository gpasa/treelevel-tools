#!/bin/bash
# Construit, depuis les sources, tout ce que les modules de TreeLevel Tools emportent — pour l'architecture de
# la machine qui l'exécute, et pour macOS 13 et suivants.
#
#   scripts/build_stack.sh            tout, en reprenant là où une exécution précédente s'est arrêtée
#   scripts/build_stack.sh herwig     une seule étape (gsl boost hepmc3 lhapdf fastjet thepeg herwig sherpa
#                                     pythia driver calchep), refaite même si elle était faite
#
# Pourquoi tout depuis les sources : MacPorts et Homebrew construisent pour le macOS de la machine. Les modules
# de la première 0.4.0, liés à leurs bibliothèques, exigeaient macOS 26 ; et un iMac Intel ne pouvait rien en
# exécuter. Ici, gestionnaires de paquets ou non, seuls leurs *outils* servent (cmake, autotools) ; chaque
# bibliothèque est compilée par clang avec MACOSX_DEPLOYMENT_TARGET=13.0.
#
# Les deux architectures se construisent chacune sur sa machine — Apple Silicon ici, Intel sur l'iMac — au
# **même chemin** (~/Library/TreeLevelMC/stack) : les deux arbres se répondent alors fichier pour fichier, et
# scripts/merge_stack.sh les fond en un arbre universel avant scripts/package_module.sh.
#
# Fortran (Herwig et quatre bibliothèques de PDF de Sherpa) : le gfortran que publie le projet R
# (mac.r-project.org/tools), dont le runtime vise macOS 11, déballé sans installation dans
# ~/Library/TreeLevelMC/tools/gfortran, et son runtime rendu universel dans lib/universal.
set -euo pipefail
cd "$(dirname "$0")/.."
REPO=$(pwd)

ARCH=$(uname -m)                                   # arm64 ou x86_64 : on construit pour la machine
case "$ARCH" in arm64) GARCH=aarch64 ;; x86_64) GARCH=x86_64 ;; *) echo "architecture $ARCH ?" >&2; exit 1 ;; esac
BASE="$HOME/Library/TreeLevelMC"
SRC="$BASE/tarballs"
ROOT="$BASE/stack"
WORK="$BASE/stack-build"
GF="$BASE/tools/gfortran"
DEPS="$ROOT/deps"            # GSL et Boost : embarqués par les modules qui les tirent
HW="$ROOT/herwig7"           # HepMC3, LHAPDF, FastJet, ThePEG, Herwig — comme le faisait le bootstrap
SH="$ROOT/sherpa3"
PY="$ROOT/pythia8-8.318"     # Pythia lui-même ; le module pythia8 est le pilote et ses données
PYMOD="$ROOT/pythia8"
CH="$ROOT/calchep3"          # CalcHEP se construit en place : le dossier est le module
JOBS=$(sysctl -n hw.ncpu)

export MACOSX_DEPLOYMENT_TARGET=13.0
# CMake 4 refuse les projets qui déclarent un minimum < 3.5. La variable d'environnement atteint aussi les
# sous-constructions que Sherpa télécharge (libzip), que l'option de ligne de commande n'atteint pas.
export CMAKE_POLICY_VERSION_MINIMUM=3.5
export SDKROOT=$(xcrun --show-sdk-path)
# Les outils de construction, pas les bibliothèques : Homebrew sur l'iMac, MacPorts ici.
export PATH="$WORK/bin:/usr/local/bin:/opt/local/bin:/opt/homebrew/bin:/usr/bin:/bin:/usr/sbin:/sbin"
unset CPATH LIBRARY_PATH PKG_CONFIG_PATH DYLD_LIBRARY_PATH
FLAGS="-O2 -arch $ARCH -mmacosx-version-min=13.0"
export CC=clang CXX=clang++
export CFLAGS="$FLAGS" CXXFLAGS="$FLAGS" FCFLAGS="$FLAGS" FFLAGS="$FLAGS"
# headerpad : package_module.sh réécrit les chemins de chargement, qui doivent pouvoir s'allonger.
export LDFLAGS="-arch $ARCH -mmacosx-version-min=13.0 -Wl,-headerpad_max_install_names"
export PKG_CONFIG_LIBDIR="$HW/lib/pkgconfig:$DEPS/lib/pkgconfig"
# CMAKE_POLICY_VERSION_MINIMUM : CMake 4 (Homebrew) refuse les projets qui déclarent un minimum < 3.5 (HepMC3).
CMAKE_COMMON=(-DCMAKE_POLICY_VERSION_MINIMUM=3.5 -DCMAKE_BUILD_TYPE=Release -DCMAKE_OSX_ARCHITECTURES="$ARCH" -DCMAKE_OSX_DEPLOYMENT_TARGET=13.0
              -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++
              -DCMAKE_SHARED_LINKER_FLAGS=-Wl,-headerpad_max_install_names
              -DCMAKE_EXE_LINKER_FLAGS=-Wl,-headerpad_max_install_names)

say() { printf '\n\033[1m[%s] %s\033[0m\n' "$(date +%H:%M:%S)" "$*"; }
mkdir -p "$WORK/bin" "$WORK/logs" "$ROOT"

# --- gfortran ------------------------------------------------------------------------------------------------
# Le pilote du projet R a la bonne cible (Mach-O pour macOS 13) mais cherche ses outils sous /opt/gfortran ;
# on appelle directement le compilateur de l'architecture, avec -fno-range-check que LoopTools (dans Herwig)
# exige : D0func.F écrit une constante qui déborde pour un gfortran récent.
[ -x "$GF/bin/$GARCH-apple-darwin20.0-gfortran" ] || { echo "gfortran manquant dans $GF" >&2; exit 1; }
[ -f "$GF/lib/universal/libgfortran.5.dylib" ] || { echo "runtime universel manquant dans $GF/lib/universal" >&2; exit 1; }
cat > "$WORK/bin/gfortran" <<EOF
#!/bin/sh
exec "$GF/bin/$GARCH-apple-darwin20.0-gfortran" -fno-range-check -mmacosx-version-min=13.0 -B "$GF/bin/$GARCH-apple-darwin20.0-" "\$@"
EOF
chmod +x "$WORK/bin/gfortran"
export FC="$WORK/bin/gfortran" F77="$WORK/bin/gfortran"
# Ses fichiers libtool (.la) nomment /opt/gfortran, où le paquet s'installerait : libtool refuserait de lier
# Herwig (« libquadmath.la is not a valid libtool archive »). On les fait pointer là où il est vraiment.
{ grep -rl /opt/gfortran --include='*.la' "$GF" 2>/dev/null || true; } | while read -r la; do
  /usr/bin/sed -i '' "s|/opt/gfortran|$GF|g" "$la"
done

unpack() {   # unpack <archive> → dossier frais dans $WORK, renvoyé sur la sortie
  local archive=$1 dir
  dir=$(tar tf "$SRC/$archive" | head -1 | cut -d/ -f1)
  rm -rf "${WORK:?}/$dir"
  tar xf "$SRC/$archive" -C "$WORK"
  echo "$WORK/$dir"
}
log() { echo "$WORK/logs/$1.log"; }
# Le libtool que portent ThePEG et Herwig ne connaît pas de macOS au-delà de 10.x : avec
# MACOSX_DEPLOYMENT_TARGET=13.0 il n'ajoute pas « -undefined dynamic_lookup », et leurs greffons, qui trouvent
# leurs symboles dans ThePEG une fois chargés, ne se lient plus (« vtable for ThePEG::Cuts » introuvable).
# La branche « 10.* » de son test devient « tout le reste ».
patch_libtool() { find . -name configure -type f -exec perl -pi -e 's/^(\s*)10\.\*\)\s*$/$1*)\n/' {} +; }
# Et ce même libtool lit mal la sortie de l'éditeur de liens de Xcode 26 : il oublie la bibliothèque C++ du
# système en liant libThePEG. dynamic_lookup taisant l'oubli, le runtime C++ s'initialisait *après* ThePEG, qui
# s'arrêtait au chargement (« typed operator new being invoked before its static initializer »). On la nomme.
LIBCXX="LIBS=-lc++"
run() {      # run <étape> <commande…> : journal complet, fin du journal à l'écran si ça casse
  local step=$1; shift
  if ! "$@" >>"$(log "$step")" 2>&1; then
    echo "échec de l'étape $step — fin du journal :" >&2
    tail -40 "$(log "$step")" >&2
    exit 1
  fi
}

step_gsl() {
  local d; d=$(unpack gsl-2.8.tar.gz)
  cd "$d"
  # ThePEG vérifie la présence de libgsl.a avant d'accepter le dossier, même s'il lie la bibliothèque partagée.
  run gsl ./configure --prefix="$DEPS"
  run gsl make -j"$JOBS"
  run gsl make install
}

step_boost() {
  # ThePEG lie la bibliothèque compilée unit_test_framework ; le reste de Boost lui sert en en-têtes.
  local d; d=$(unpack boost_1_86_0.tar.bz2)
  cd "$d"
  run boost ./bootstrap.sh --with-toolset=clang --with-libraries=test --prefix="$DEPS"
  run boost ./b2 -j"$JOBS" toolset=clang architecture="$( [ "$ARCH" = arm64 ] && echo arm || echo x86 )" \
      address-model=64 link=shared threading=multi variant=release \
      cxxflags="$FLAGS" cflags="$FLAGS" linkflags="$LDFLAGS" install
  # b2 pose des noms d'installation nus (« libboost_….dylib ») : les rendre absolus, comme le reste.
  for l in "$DEPS"/lib/libboost_*.dylib; do
    [ -L "$l" ] && continue
    install_name_tool -id "$l" "$l"
    for dep in $(otool -L "$l" | tail -n +2 | awk '{print $1}' | grep '^libboost_' || true); do
      install_name_tool -change "$dep" "$DEPS/lib/$dep" "$l"
    done
  done
}

step_hepmc3() {
  local d; d=$(unpack HepMC3-3.2.5.tar.bz2)
  run hepmc3 cmake -S "$d" -B "$d/build" "${CMAKE_COMMON[@]}" -DCMAKE_INSTALL_PREFIX="$HW" \
      -DHEPMC3_ENABLE_ROOTIO=OFF -DHEPMC3_ENABLE_PYTHON=OFF -DHEPMC3_BUILD_EXAMPLES=OFF -DHEPMC3_ENABLE_TEST=OFF \
      -DHEPMC3_INSTALL_INTERFACES=OFF \
      -DCMAKE_INSTALL_NAME_DIR="$HW/lib"   # un nom absolu, comme les autres : sinon « @rpath/libHepMC3 », que les
                                           # greffons de ThePEG ne résolvent pas quand Herwig bâtit son dépôt
  run hepmc3 cmake --build "$d/build" -j "$JOBS"
  run hepmc3 cmake --install "$d/build"
}

step_lhapdf() {
  local d; d=$(unpack LHAPDF-6.5.3.tar.gz)
  cd "$d"
  run lhapdf ./configure --prefix="$HW" --disable-python
  run lhapdf make -j"$JOBS"
  run lhapdf make install
  # Les deux jeux que les défauts de Herwig chargent : des données, identiques sur les deux architectures.
  for set in CT14lo CT14nlo; do
    [ -d "$HW/share/LHAPDF/$set" ] || cp -R "$SRC/lhapdf-sets/$set" "$HW/share/LHAPDF/"
  done
}

step_fastjet() {
  local d; d=$(unpack fastjet-3.4.2.tar.gz)
  cd "$d"
  run fastjet ./configure --prefix="$HW" --disable-auto-ptr
  run fastjet make -j"$JOBS"
  run fastjet make install
}

step_thepeg() {
  local d; d=$(unpack ThePEG-2.3.0.tar.bz2)
  cd "$d"
  patch_libtool
  run thepeg ./configure "$LIBCXX" --prefix="$HW" --with-boost="$DEPS" --with-gsl="$DEPS" --with-hepmc="$HW" \
      --with-hepmcversion=3 --with-fastjet="$HW" --with-lhapdf="$HW"
  run thepeg make -j"$JOBS"
  run thepeg make install
}

step_herwig() {
  local d; d=$(unpack Herwig-7.3.0.tar.bz2)
  cd "$d"
  patch_libtool
  run herwig ./configure "$LIBCXX" --prefix="$HW" --with-thepeg="$HW" --with-boost="$DEPS" --with-gsl="$DEPS" \
      --with-fastjet="$HW"
  run herwig make -j"$JOBS"
  # make install construit aussi le dépôt HerwigDefaults.rpo : quelques minutes, et la preuve que tout se charge.
  run herwig make install
}

step_sherpa() {
  local d; d=$(unpack sherpa-v3.0.5.tar.gz)
  run sherpa cmake -S "$d" -B "$d/build" "${CMAKE_COMMON[@]}" -DCMAKE_INSTALL_PREFIX="$SH" \
      -DCMAKE_Fortran_COMPILER="$FC" \
      -DSHERPA_ENABLE_LHAPDF=ON -DLHAPDF_DIR="$HW" \
      -DSHERPA_ENABLE_HEPMC3=ON -DHepMC3_DIR="$HW/share/HepMC3/cmake" \
      -DSHERPA_ENABLE_FASTJET=ON -DFASTJET_DIR="$HW" \
      -DSHERPA_ENABLE_INSTALL_LIBZIP=ON -DSHERPA_ENABLE_INTERNAL_PDFS=ON -DSHERPA_ENABLE_ANALYSIS=ON \
      -DSHERPA_ENABLE_EXAMPLES=OFF
  run sherpa cmake --build "$d/build" -j "$JOBS"
  run sherpa cmake --install "$d/build"
}

step_pythia() {
  local d; d=$(unpack pythia8318.tgz)
  cd "$d"
  run pythia ./configure --prefix="$PY" --cxx-common="-O2 -std=c++17 -fPIC $FLAGS" \
      --cxx-shared="-dynamiclib $LDFLAGS"
  run pythia make -j"$JOBS"
  run pythia make install
}

step_driver() {
  # Le pilote du moteur, lié au Pythia ci-dessus ; `make install` y joint xmldoc, pdfdata, tunes et setups.
  rm -rf "${PYMOD:?}"
  cd "$REPO/Backends/pythia"
  rm -f treelevel-pythia
  PATH="$PY/bin:$PATH" run driver make CXX=clang++ CXXFLAGS="-O2 -std=c++17 $FLAGS -Wl,-headerpad_max_install_names" \
      MODULES="$PYMOD" install
  rm -f treelevel-pythia
}

step_calchep() {
  # CalcHEP se compile en place. Sans X11 il passe en mode « aveugle » — celui dont le moteur se sert, en lot —
  # et n'emporte plus libX11 et ses trois compagnes.
  rm -rf "${CH:?}"
  local d; d=$(unpack calchep_3.9.2.tgz)
  mv "$d" "$CH"
  cd "$CH"
  /usr/bin/sed -i '' -E 's/^([[:space:]]*)(testX11|findX11)[[:space:]]*$/\1false/' getFlags
  CC=cc CFLAGS="$FLAGS" run calchep ./getFlags
  run calchep make
}

ALL="gsl boost hepmc3 lhapdf fastjet thepeg herwig sherpa pythia driver calchep"
STEPS=${*:-$ALL}
for s in $STEPS; do
  if [ $# -eq 0 ] && [ -f "$WORK/.done-$s" ]; then continue; fi
  say "$s ($ARCH)"
  : > "$(log "$s")"
  ( "step_$s" )
  touch "$WORK/.done-$s"
done
say "terminé : $ROOT ($ARCH)"
