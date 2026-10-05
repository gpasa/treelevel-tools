Modulversion: **$MODULE** — Pythia **$PYTHIA_VERSION**, nach WebAssembly kompiliert mit dem gemeinsamen Treiber von
TreeLevel Tools $MODULE. Diese Seite behält immer denselben Namen: TreeLevel auf dem iPad (1.4 und neuer) holt hier
die neueste Version, liest ihre Nummer in `module.json` und zeigt sie in seinen Einstellungen an, bietet die
Aktualisierung an, sobald eine neuere Version erscheint, und prüft jede Datei gegen den Fingerabdruck, den
`module.json` für sie angibt. Es führt das Modul in einer Web-Ansicht aus, ohne irgendetwas irgendwohin zu senden.

Was dieses Modul kann: `$FEATURES`. „spacetime“: Partonen und Hadronen in der Wechselwirkungszone platzieren, die
TreeLevel auf Femtometerskala zeigt.

| Datei | Rolle |
|---|---|
| `module.json` | Version des Moduls und von Pythia, was es kann, der Fingerabdruck jeder Datei |
| `treelevel-pythia-web.wasm`, `.js` | Pythia $PYTHIA_VERSION und der Treiber, in WebAssembly |
| `runner.js` | führt einen Auftrag von TreeLevel aus: Plan, Teile, Zusammenführung |
| `leptons.pack` | Daten von Pythia (xmldoc, tunes, setups) — Leptonenstrahlen |
| `pdfdata.pack` | Partondichten — Hadronenstrahlen, optional |
| `$SOURCES` | die Quellen von Pythia $PYTHIA_VERSION, wie auf pythia.org veröffentlicht |
| `COPYING.pythia8` | die Lizenz von Pythia (GPL v2 oder neuer) |

TreeLevel 1.3 auf dem iPad lädt sein Modul von
[ipad-pythia-8.318](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia-8.318) herunter, dessen
Fingerabdrücke es festschreibt: Jene Seite ändert sich nicht.

**Pythia 8 und seine Autoren.** Pythia 8 ist © Torbjörn Sjöstrand und die Pythia-Kollaboration —
[pythia.org](https://pythia.org) — und wird unter der GPL v2 oder neuer verbreitet. Die gesamte Physik dieses Moduls
stammt von ihnen. Wenn Sie ein damit erzieltes Ergebnis veröffentlichen, zitieren Sie: C. Bierlich et al., „A
comprehensive guide to the physics and usage of PYTHIA 8.3“, *SciPost Phys. Codebases* 8 (2022),
[arXiv:2203.11601](https://arxiv.org/abs/2203.11601). Die anderen von TreeLevel Tools gesteuerten Generatoren und
ihre Autoren: [CREDITS.md](https://github.com/gpasa/treelevel-tools/blob/main/CREDITS.md).

Es bleibt ein von TreeLevel getrenntes Programm: Die App übergibt ihm einen Auftrag und liest das Ergebnis zurück.
Die Quellen des Treibers und von `runner.js` liegen in diesem Repository (`Backends/pythia`), beim Tag
`ipad-pythia-module-$MODULE`. Prüfsummen in `SHA256SUMS.txt`.
