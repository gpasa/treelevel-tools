Die Ereignisgeneratoren von [TreeLevel](https://treelevel.pasahome.org), auf Ihrem Rechner. TreeLevel schreibt einen
Auftrag in einen lokalen Ordner; dieses Programm übergibt ihn an **Pythia 8**, **Herwig 7**, **Sherpa 3**,
**WHIZARD 3** oder **CalcHEP 3** — Schauer und Hadronisierung seiner Ereignisse oder ganze Kollisionen einer
Maschine — und schreibt das Ergebnis in HepMC3 zurück, das TreeLevel wieder einliest. Nichts geht über das Netz,
kein Konto, kein Dienst. Auf dem iPad übernimmt Pythia 8, nach WebAssembly kompiliert, dieselbe Rolle,
heruntergeladen von [seinem Release](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia).

Es wird getrennt verbreitet, weil diese Generatoren unter der **GPL** stehen: Dieses Repository ist GPL v3, und
TreeLevel enthält nichts von ihrem Code.

| System | Download | Inhalt |
|---|---|---|
| **macOS** 13 oder neuer, Apple Silicon und Intel | [TreeLevelTools-0.5.0.dmg](https://github.com/gpasa/treelevel-tools/releases/download/mac-0.5.0/TreeLevelTools-0.5.0.dmg) | Pythia 8, Herwig 7, Sherpa 3 und CalcHEP 3, sofort lauffähig |
| **Windows** 10 und 11 | [x64](https://github.com/gpasa/treelevel-tools/releases/download/win-0.5.1/TreeLevelTools-0.5.1-x64.zip) · [ARM64](https://github.com/gpasa/treelevel-tools/releases/download/win-0.5.1/TreeLevelTools-0.5.1-arm64.zip) | Pythia 8; die anderen über das Docker-Image |
| **iPad** | aus den Einstellungen von TreeLevel ([das Release](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia)) | Pythia 8 in WebAssembly |
| **Docker**, jedes System | `docker pull ghcr.io/gpasa/treelevel-tools:latest` | die fünf Generatoren, WHIZARD 3 inbegriffen |

**Mac**: `TreeLevel Tools.app` nach `/Applications` ziehen und einmal starten; TreeLevel bietet seine Generatoren
dann im Arbeitsbereich Erzeugung an. **Windows**: das Archiv nach `%LOCALAPPDATA%\Programs` entpacken. **iPad**: Die
Karte *Pythia-8-Modul* der Einstellungen lädt es herunter und prüft jede Datei. **Docker**: Ist das Image vorhanden,
führt TreeLevel Tools darin die Generatoren aus, die kein Modul bietet (auf dem Mac übergibt ihm ein Kästchen alle
Aufträge).
