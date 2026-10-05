Der Kern, der die Monte-Carlo-Generatoren für TreeLevel unter Windows ausführt. Er wird installiert, indem man das Archiv nach `%LOCALAPPDATA%\Programs` entpackt — kein Installationsprogramm, nichts in der Registrierung. **Zum Aktualisieren** einer früheren Version: TreeLevel schließen und das Archiv an derselben Stelle entpacken, wobei die vorhandenen Dateien ersetzt werden.

Wählen Sie das Archiv für Ihren Rechner: `arm64` für einen Copilot+ PC oder ein ARM-Tablet, `x64` überall sonst. Im Zweifel läuft die x64-Fassung auch auf ARM, unter Emulation.

**Was das Archiv enthält**: der Kern und das Pythia-8-Modul, für diese Architektur übersetzt. Herwig, Sherpa, WHIZARD und CalcHEP laufen über das Container-Image, das Docker Desktop voraussetzt:

```
docker pull ghcr.io/gpasa/treelevel-tools
```

Sonst ist nichts zu tun: TreeLevel legt selbst für jeden Auftrag einen kurzlebigen Container an. Docker Desktop muss laufen, wenn TreeLevel startet; die Generatoren des Images erscheinen dann, mit „(Docker)“ gekennzeichnet.

**Der Kern hat kein Fenster.** TreeLevel startet ihn, wann immer er gebraucht wird. Wenn Sie `treelevel-tools.exe` doppelklicken, warnt Windows SmartScreen vor einer nicht erkannten App — der Kern ist nicht signiert —, und nach der Warnung zeigt eine Konsole seine Gebrauchsanweisung und schließt sich wieder. Das ist normal und ohne Wirkung: Sie müssen ihn nie selbst starten.

### Korrekturen in dieser Version

- **Das ohne Nummer gezogene Image wird erkannt.** 0.3.0 erkannte nur das Tag `:0.3.0`; der Befehl, den die Paketseite vorschlägt, und der, den alle eintippen, zieht aber `:latest`. Das Image war auf dem Rechner, antwortete, wenn man es von Hand startete, und dennoch bot TreeLevel nur Pythia an. Beide Tags bezeichnen dasselbe Image, und beide werden nun erkannt.
- **Sherpa auf Leptonenstrahlen**, wenn es außerhalb des Images läuft: Sein Wirkungsquerschnitt wird nicht mehr durch die QED-Anfangszustandsstrahlung aufgebläht (rund fünfzehn Pikobarn statt 3,2 für e⁻e⁺ → b b̄ bei 200 GeV). Der Weg, der davon abhing — Sherpa selbst in WSL installiert —, wird in einer kommenden Version entfernt: Docker ist der vorgesehene Weg.

### Fünf Generatoren, zwei Familien

**Pythia 8** und **Herwig 7** kleiden die partonischen Ereignisse ein, die TreeLevel ihnen gibt: Schauer, Hadronisierung, Zerfälle.

**Sherpa 3**, **WHIZARD 3** und **CalcHEP 3** haben keinen Leser für Les Houches — sie berechnen den vom Diagramm beschriebenen Prozess selbst. Das Protokoll übermittelt ihnen daher neben den Ereignissen eine Beschreibung des Prozesses (Strahlen, Energien, Endzustand, Kopplungsordnungen).

### Gemessen: e⁻e⁺ → W⁺W⁻ bei 200 GeV

| Programm | σ |
|---|---|
| TreeLevel | 19,22 pb |
| WHIZARD 3.1.6 | 19,441 ± 0,006 pb |
| CalcHEP 3.9.2 | 20,42 pb |
| Sherpa 3.0.5 | 18,2 ± 1,1 pb |

Die Abweichungen gehen auf die Wahl des Kopplungsschemas zurück, nicht auf Fehler.

### Zur Erinnerung: was 0.3.0 brachte

- **Der Collider-Modus.** Der Generator erhält nur die Strahlen und die Energie, nie einen Endzustand: Er erzeugt die ganze Mischung, wie eine echte Maschine, und TreeLevel zählt danach die Ereignisse, die die Signatur des gezeichneten Prozesses tragen — was einen Wirkungsquerschnitt misst, statt ihn zu berechnen. Sechs Familien von Kanälen, darunter harte QCD, Photoproduktion und der totale Wirkungsquerschnitt. Vorerst Pythia 8.
- **Zwei Maschinenkonfigurationen zusammengefügt.** Ein Leptonenstrahl tritt als Lepton oder als der von ihm abgestrahlte Photonenfluss ein, nie beides in derselben Ziehung: Der Kern zieht beide und behält von jeder den Anteil, der ihr nach ihrem Wirkungsquerschnitt zusteht.
- **Der gemeldete Wirkungsquerschnitt ist der nach dem letzten Ereignis.** Pythia normiert nach seiner Schleife; der Treiber schrieb die laufende Schätzung, die bei einigen hundert Ereignissen um 12 % danebenlag.
- **Das Programm heißt TreeLevel Tools**, und die ausführbare Datei `treelevel-tools.exe`.
- Aufträge nummeriert, mit Zeitstempel versehen und in einer Liste aufbewahrt, die TreeLevel wieder öffnet; Wirkungsquerschnitt dort gelesen, wo jeder Generator ihn ablegt.

TreeLevel Tools steht unter GPL v3 oder neuer (siehe `LICENSE.txt` im Archiv); jeder Generator behält seine eigene Lizenz, siehe unten.
