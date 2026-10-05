Der Kern, der die Monte-Carlo-Generatoren für TreeLevel 1.4 unter Windows (und weiterhin 1.3) ausführt. Er wird installiert, indem man das Archiv nach `%LOCALAPPDATA%\Programs` entpackt — kein Installationsprogramm, nichts in der Registrierung. **Zum Aktualisieren** einer früheren Version: TreeLevel schließen und das Archiv an derselben Stelle entpacken, wobei die vorhandenen Dateien ersetzt werden.

Wählen Sie das Archiv für Ihren Rechner: `arm64` für einen Copilot+ PC oder ein ARM-Tablet, `x64` überall sonst. Im Zweifel läuft die x64-Fassung auch auf ARM, unter Emulation.

**Was das Archiv enthält**: `treelevel-tools.exe`, das TreeLevel startet; `treelevel-engine.exe`, der Kern, der die Karte jedes Generators schreibt und ihn steuert; das Pythia-8-Modul, für diese Architektur übersetzt; `CREDITS.md`. Herwig, Sherpa, WHIZARD und CalcHEP laufen über das Container-Image, das Docker Desktop voraussetzt:

```
docker pull ghcr.io/gpasa/treelevel-tools:latest
```

Sonst ist nichts zu tun: TreeLevel legt selbst für jeden Auftrag einen kurzlebigen Container an. Docker Desktop muss laufen, wenn TreeLevel startet; die Generatoren des Images erscheinen dann, mit „(Docker)“ gekennzeichnet.

**Der Kern hat kein Fenster.** TreeLevel startet ihn, wann immer er gebraucht wird. Wenn Sie `treelevel-tools.exe` doppelklicken, warnt Windows SmartScreen vor einer nicht erkannten App — der Kern ist nicht signiert —, und nach der Warnung zeigt eine Konsole seine Gebrauchsanweisung und schließt sich wieder. Das ist normal und ohne Wirkung.

### Was sich ändert

- **Der Host verlangt das Image 0.5.0.** Es ist veröffentlicht, und `:latest` zeigt darauf; der Windows-Kern sucht zuerst `ghcr.io/gpasa/treelevel-tools:0.5.0`, dann `:latest`, wie bisher. Mit dem Image 0.5.0 liefert das Kästchen „Tout faire tourner dans l'image Docker“ auch die Wechselwirkungszone (das Image meldet `spaceTimeGenerators`).
- **Um es mit Docker zu nutzen**: `docker pull ghcr.io/gpasa/treelevel-tools:latest` (oder `:0.5.0`) ersetzt das Image 0.4.0.
- **Sonst bewegt sich nichts**: derselbe Pythia-Treiber und dieselben Auftragsschlüssel wie `win-0.5.0`; kompatibel mit TreeLevel 1.3 und 1.4.
