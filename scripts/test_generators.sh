#!/bin/bash
# Fait tourner un vrai travail par générateur embarqué, avec l'outil en ligne de commande d'une application
# installée — la vérification qui manquait à la première 0.4.0 : sur un Mac Intel, rien n'aurait passé.
#
#   scripts/test_generators.sh "/Applications/TreeLevel Tools.app"
#
# Les travaux sont ceux de docker/test-job* (e⁺e⁻ → b b̄ à 200 GeV), copiés dans un dossier temporaire ;
# chacun doit finir « finished » avec des événements. Le conteneur n'intervient pas : ce sont les modules.
set -uo pipefail
cd "$(dirname "$0")/.."
APP=${1:?chemin de TreeLevel Tools.app}
CLI="$APP/Contents/MacOS/treelevel-tools"
[ -x "$CLI" ] || { echo "pas d'outil en ligne de commande dans $APP" >&2; exit 1; }
echo "$(uname -m), macOS $(sw_vers -productVersion), $("$CLI" version)"
"$CLI" capabilities | python3 -c 'import json,sys; c=json.load(sys.stdin); print("  proposés :", ", ".join(c["generators"]))'

TMP=$(mktemp -d)
FAILED=0
run() {   # run <générateur> <dossier modèle> [étiquette]
  local gen=$1 label=${3:-$1} dir="$TMP/${3:-$1}" start
  cp -R "$2" "$dir"
  python3 - "$dir/job.json" "$gen" <<'PY'
import json, sys
path, gen = sys.argv[1], sys.argv[2]
job = json.load(open(path))
job["generator"] = gen
job["id"] = "essai-" + gen
job["events"] = 50
json.dump(job, open(path, "w"), indent=2)
PY
  start=$(date +%s)
  "$CLI" run "$dir" >"$dir/cli.log" 2>&1
  python3 - "$dir" "$label" "$(( $(date +%s) - start ))" <<'PY'
import json, os, sys
d, gen, secs = sys.argv[1], sys.argv[2], sys.argv[3]
try:
    s = json.load(open(os.path.join(d, "status.json")))
except Exception as e:
    print(f"  ✗ {gen:9} pas de status.json ({e})"); sys.exit(1)
ok = s.get("state") == "finished" and (s.get("eventsWritten") or 0) > 0
mark = "✓" if ok else "✗"
print(f"  {mark} {gen:10} {s.get('state')}, {s.get('eventsWritten')} événements, {secs} s"
      + ("" if ok else f" — {s.get('message', '')[:160]}"))
sys.exit(0 if ok else 1)
PY
  if [ $? -ne 0 ]; then FAILED=$((FAILED + 1)); tail -15 "$dir/engine.log" 2>/dev/null | sed 's/^/      /'; fi
}
run pythia8  docker/test-job
run herwig7  docker/test-job
run sherpa3  docker/test-job-sherpa
run calchep3 docker/test-job-sherpa
run pythia8  docker/test-job-machine machine
rm -rf "${TMP:?}"
[ "$FAILED" -eq 0 ] && echo "tous les générateurs tournent" || { echo "$FAILED échec(s)"; exit 1; }
