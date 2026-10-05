Der Kern, der die Monte-Carlo-Generatoren für TreeLevel 1.4 unter Windows (und weiterhin 1.3) ausführt. Er wird installiert, indem man das Archiv nach `%LOCALAPPDATA%\Programs` entpackt — kein Installationsprogramm, nichts in der Registrierung. **Zum Aktualisieren** einer früheren Version: TreeLevel schließen und das Archiv an derselben Stelle entpacken, wobei die vorhandenen Dateien ersetzt werden.

Wählen Sie das Archiv für Ihren Rechner: `arm64` für einen Copilot+ PC oder ein ARM-Tablet, `x64` überall sonst. Im Zweifel läuft die x64-Fassung auch auf ARM, unter Emulation.

**Was das Archiv enthält**: `treelevel-tools.exe`, das TreeLevel startet; `treelevel-engine.exe`, der Kern, der die Karte jedes Generators schreibt und ihn steuert; das Pythia-8-Modul, für diese Architektur übersetzt; `CREDITS.md`. Herwig, Sherpa, WHIZARD und CalcHEP laufen über das Container-Image, das Docker Desktop voraussetzt:

```
docker pull ghcr.io/gpasa/treelevel-tools:latest
```

Sonst ist nichts zu tun: TreeLevel legt selbst für jeden Auftrag einen kurzlebigen Container an. Docker Desktop muss laufen, wenn TreeLevel startet; die Generatoren des Images erscheinen dann, mit „(Docker)“ gekennzeichnet.

**Der Kern hat kein Fenster.** TreeLevel startet ihn, wann immer er gebraucht wird. Wenn Sie `treelevel-tools.exe` doppelklicken, warnt Windows SmartScreen vor einer nicht erkannten App — der Kern ist nicht signiert —, und nach der Warnung zeigt eine Konsole seine Gebrauchsanweisung und schließt sich wieder. Das ist normal und ohne Wirkung.

### Was sich ändert

- **Die Wechselwirkungszone, auf Femtometerskala.** Für TreeLevel 1.4 kann der Pythia-Treiber jede partonische Wechselwirkung in die Überlappung der beiden Hadronen setzen und jedes Hadron dorthin, wo sein String gerissen ist (Auftragsschlüssel `spaceTime`: `PartonVertex:setVertex`, `Fragmentation:setVertices`). Er schreibt für jedes Parton seinen Farbfluss und seinen Pythia-Status und für jedes Teilchen, das nicht an seinem Vertex entstanden ist, seinen eigenen Entstehungsort — das, was der vergrößerte Schnitt und die 3D-Ansicht von TreeLevel 1.4 zeichnen. Das ist das Modell des Generators, nichts Gemessenes.
- **Ein einziger Versatz der Kollisionszone.** Mit diesen Positionen verschob Pythia die Hadronen zweimal; der Treiber platziert das Ereignis nun selbst, mit einem einzigen Vektor. Ohne den Schlüssel ändert sich nichts.
- **Der Kern sagt, was er kann**: `treelevel-tools capabilities` meldet `spaceTimeGenerators` (natives Pythia, wenn sein Treiber „spacetime“ antwortet, und was das Image meldet). TreeLevel 1.4 zeigt das Kästchen „Positionen in der Wechselwirkungszone“ nur, wenn es dort aufgeführt ist.
- **Kompatibel mit TreeLevel 1.3**: Ein Auftrag ohne den Schlüssel `spaceTime` läuft genau wie mit 0.4.0.
- **Das Docker-Image 0.5** folgt: Bis dahin ist `:latest` das Image 0.4.0, und Herwig, Sherpa, WHIZARD und CalcHEP laufen darin wie bisher; die Wechselwirkungszone läuft über das native Pythia dieses Archivs.
- **Derselbe Kern wie `mac-0.5.0`**: derselbe Pythia-Treiber (`Backends/pythia/main.cpp`), dieselben Auftragsschlüssel, dieselben geschriebenen Attribute.
