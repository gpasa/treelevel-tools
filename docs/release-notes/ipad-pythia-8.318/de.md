Pythia 8, nach WebAssembly übersetzt, mit dem gemeinsamen Treiber von TreeLevel Tools. TreeLevel auf dem iPad lädt es
von dieser Seite herunter, Datei für Datei, und prüft jede gegen einen in der App festgelegten Fingerabdruck; es lässt es
in einer Web-Ansicht laufen, ohne irgendetwas irgendwohin zu senden. Die Ereignisse kommen mit Schauer und Hadronisierung
heraus, und die Quelle Maschine von TreeLevel wird auf dem iPad verfügbar.

| Datei | Rolle |
|---|---|
| `treelevel-pythia-web.wasm`, `.js` | Pythia 8.318 und der Treiber, in WebAssembly |
| `runner.js` | führt einen Auftrag von TreeLevel aus: Plan, Teile, Zusammenführung |
| `leptons.pack` | Daten von Pythia (xmldoc, tunes, setups) — Leptonenstrahlen |
| `pdfdata.pack` | Partondichten — Hadronenstrahlen, optional |
| `pythia8318-sources.tgz` | die Quellen von Pythia 8.318, wie auf pythia.org veröffentlicht |
| `COPYING.pythia8` | die Lizenz von Pythia (GPL v2 oder neuer) |

### Pythia 8, seine Autoren

Pythia 8 ist © Torbjörn Sjöstrand und die Pythia-Kollaboration — [pythia.org](https://pythia.org) — und wird
unter GPL v2 oder neuer verbreitet. Die gesamte Physik dieses Moduls stammt von ihnen. Wenn Sie ein damit erzieltes
Ergebnis veröffentlichen, zitieren Sie: C. Bierlich et al., „A comprehensive guide to the physics and usage of PYTHIA 8.3“,
*SciPost Phys. Codebases* 8 (2022), [arXiv:2203.11601](https://arxiv.org/abs/2203.11601).

Die anderen von TreeLevel Tools gesteuerten Generatoren und ihre Autoren:
[CREDITS.md](https://github.com/gpasa/treelevel-tools/blob/1.3-dev/CREDITS.md).
Es bleibt ein von TreeLevel getrenntes Programm: Die App übergibt ihm einen Auftrag und liest das Ergebnis zurück. Die
Quellen des Treibers und von `runner.js` liegen in diesem Repository, beim Tag dieses Release (`Backends/pythia`).
Prüfsummen in `SHA256SUMS.txt`.
