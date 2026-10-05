Der Kern, der die Monte-Carlo-Generatoren für TreeLevel 1.3 unter Windows ausführt. Er wird installiert, indem man das Archiv nach `%LOCALAPPDATA%\Programs` entpackt — kein Installationsprogramm, nichts in der Registrierung. **Zum Aktualisieren** einer früheren Version: TreeLevel schließen und das Archiv an derselben Stelle entpacken, wobei die vorhandenen Dateien ersetzt werden.

Wählen Sie das Archiv für Ihren Rechner: `arm64` für einen Copilot+ PC oder ein ARM-Tablet, `x64` überall sonst. Im Zweifel läuft die x64-Fassung auch auf ARM, unter Emulation.

**Was das Archiv enthält**: `treelevel-tools.exe`, das TreeLevel startet; `treelevel-engine.exe`, der Kern, der die Karte jedes Generators schreibt und ihn steuert; das Pythia-8-Modul, für diese Architektur übersetzt; `CREDITS.md`. Herwig, Sherpa, WHIZARD und CalcHEP laufen über das Container-Image, das Docker Desktop voraussetzt:

```
docker pull ghcr.io/gpasa/treelevel-tools:0.4.0
```

Sonst ist nichts zu tun: TreeLevel legt selbst für jeden Auftrag einen kurzlebigen Container an. Docker Desktop muss laufen, wenn TreeLevel startet; die Generatoren des Images erscheinen dann, mit „(Docker)“ gekennzeichnet.

**Der Kern hat kein Fenster.** TreeLevel startet ihn, wann immer er gebraucht wird. Wenn Sie `treelevel-tools.exe` doppelklicken, warnt Windows SmartScreen vor einer nicht erkannten App — der Kern ist nicht signiert —, und nach der Warnung zeigt eine Konsole seine Gebrauchsanweisung und schließt sich wieder. Das ist normal und ohne Wirkung.

### Was sich ändert

- **Ein einziger Kern für Windows, den Mac und das Image.** Die Karten der Generatoren werden nur noch einmal geschrieben, in C++ (`Backends/engine`), und dasselbe Programm läuft hier, auf dem Mac und im Container. Der Windows-Teil sucht nur noch Docker, das Image und das Pythia-Modul.
- **„Tout faire tourner dans l'image Docker“**, ein Kästchen in den Einstellungen von TreeLevel 1.3. Angekreuzt führt das Image alle Aufträge aus, Pythia eingeschlossen, und nichts wird angeboten, wenn Docker oder das Image fehlen. Nicht angekreuzt läuft Pythia nativ, und der Rest läuft über das Image.
- **Was das Experiment aufzeichnet**: Die Quelle Maschine von TreeLevel 1.3 wählt ein Phänomen — alles, was der Detektor sieht, die Streuung durch ein Photon, die Annihilation in γ*/Z, das W, ausgetauscht oder erzeugt, die Bosonenpaare, die Jets, die Photoproduktion, die weichen Kollisionen —, und der Kern öffnet es mit der passenden Schwelle (Q² für die Streuungen, p_T für die Jets).
- **Wo jedes Teilchen entstanden ist**: Der Pythia-Treiber schreibt die Position der Vertizes und den harten Prozess jedes Ereignisses; TreeLevel zeichnet sie und filtert danach.
- **Pythia 8.318** überall, mit seinen Tunes (`Monash 2013`, `A14`…), in Pythias Nummern übersetzt.
- **Pfade mit Akzenten**: Ein Auftragsordner unter einem Benutzernamen mit Akzenten öffnet sich wie jeder andere.
- Entfernt: der WSL-Weg (Herwig oder Sherpa von Hand in einer Distribution installiert) — Docker ist der vorgesehene Weg.

TreeLevel Tools steht unter GPL v3 oder neuer (siehe `LICENSE.txt` im Archiv); jeder Generator behält seine eigene Lizenz — siehe `CREDITS.md` und unten.
