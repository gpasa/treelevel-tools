#!/bin/bash
# Une image ne casse jamais TreeLevel 1.3 : avant qu'une nouvelle image devienne « latest », elle doit mener les
# travaux que TreeLevel Tools 0.4.0 lui passe, exactement comme il les lui passe.
#
#   scripts/test_image_compat.sh ghcr.io/gpasa/treelevel-tools:0.9.0
#
# Les travaux de docker/compat-0.4.0 sont figés : protocole 2, tels que la 0.4.0 les écrit. On ne les met pas à
# jour quand le protocole évolue — c'est tout leur intérêt. L'appel est celui de Runner.swift (0.4.0) :
#   docker run --rm -v <dossier>:/job <image> run /job
# et le moteur doit laisser status.json (« finished », des événements), events.hepmc et engine.log. La liste des
# capacités doit aussi se lire avec les clés que la 0.4.0 attend.
set -uo pipefail
cd "$(dirname "$0")/.."
IMAGE=${1:?image à éprouver}
DOCKER=$(command -v docker) || { echo "docker introuvable" >&2; exit 1; }
"$DOCKER" image inspect "$IMAGE" >/dev/null 2>&1 || { echo "image absente : $IMAGE" >&2; exit 1; }

FAILED=0
echo "$IMAGE — compatibilité avec TreeLevel Tools 0.4.0 (protocole 2)"
"$DOCKER" run --rm "$IMAGE" capabilities | python3 -c '
import json, sys
c = json.load(sys.stdin)
manque = [k for k in ("engineVersion", "generators", "versions") if k not in c]
if manque: print("  ✗ capacités : clés absentes", manque); sys.exit(1)
attendus = {"pythia8", "herwig7", "sherpa3", "whizard3", "calchep3"}
absents = attendus - set(c["generators"])
print("  " + ("✓" if not absents else "✗") + " capacités :", ", ".join(c["generators"]),
      ("— manquent " + ", ".join(sorted(absents))) if absents else "")
sys.exit(1 if absents else 0)' || FAILED=$((FAILED + 1))

TMP=$(mktemp -d)
for job in docker/compat-0.4.0/*/; do
  name=$(basename "$job")
  cp -R "$job" "$TMP/$name"
  start=$(date +%s)
  "$DOCKER" run --rm --user "$(id -u):$(id -g)" -v "$TMP/$name:/job" "$IMAGE" run /job >"$TMP/$name.out" 2>&1
  python3 - "$TMP/$name" "$name" "$(( $(date +%s) - start ))" <<'PY' || FAILED=$((FAILED + 1))
import json, os, sys
d, name, secs = sys.argv[1:4]
try:
    s = json.load(open(os.path.join(d, "status.json")))
except Exception as e:
    print(f"  ✗ {name:9} pas de status.json ({e})"); sys.exit(1)
fichiers = [f for f in ("events.hepmc", "engine.log") if not os.path.exists(os.path.join(d, f))]
ok = s.get("state") == "finished" and (s.get("eventsWritten") or 0) > 0 and not fichiers
print(f"  {'✓' if ok else '✗'} {name:9} {s.get('state')}, {s.get('eventsWritten')} événements, {secs} s"
      + ("" if ok else f" — {s.get('message', '')} {('manquent ' + ', '.join(fichiers)) if fichiers else ''}"))
sys.exit(0 if ok else 1)
PY
done
rm -rf "${TMP:?}"
if [ "$FAILED" -eq 0 ]; then echo "compatible : cette image peut devenir « latest »"; else echo "$FAILED échec(s) : pas de « latest »"; exit 1; fi
