> **Ersetzt durch [0.3.1](https://github.com/gpasa/treelevel-tools/releases/tag/win-0.3.1).** Diese Version erkennt das Image nur unter dem Tag `:0.3.0`; 0.3.1 akzeptiert auch `:latest`, das Tag, das `docker pull` ohne Nummer zieht.

Der Kern, der die Monte-Carlo-Generatoren für TreeLevel unter Windows ausführt. Er wird installiert, indem man das Archiv nach `%LOCALAPPDATA%\Programs` entpackt — kein Installationsprogramm, nichts in der Registrierung.

Wählen Sie das Archiv für Ihren Rechner: `arm64` für einen Copilot+ PC oder ein ARM-Tablet, `x64` überall sonst. Im Zweifel läuft die x64-Fassung auch auf ARM, unter Emulation.

**Was das Archiv enthält**: der Kern und das Pythia-8-Modul, für diese Architektur übersetzt. Herwig, Sherpa, WHIZARD und CalcHEP laufen über das Container-Image `ghcr.io/gpasa/treelevel-tools`, das Docker voraussetzt. Ziehen Sie es **mit seiner Nummer**:

```
docker pull ghcr.io/gpasa/treelevel-tools:0.3.0
```

Diese Version des Kerns erkennt nur dieses Tag: Ein ohne Nummer gezogenes Image (also `:latest`) ist zwar auf dem Rechner, aber TreeLevel bietet seine Generatoren nicht an. Beide Tags bezeichnen dasselbe Image; wenn Sie `latest` schon haben, fügt der obige Befehl nur das Tag hinzu. Docker Desktop muss laufen, wenn TreeLevel startet.

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

### Neu in dieser Version

- **Der Collider-Modus.** Der Generator erhält nur die Strahlen und die Energie, nie einen Endzustand: Er erzeugt die ganze Mischung, wie eine echte Maschine, und TreeLevel zählt danach die Ereignisse, die die Signatur des gezeichneten Prozesses tragen — was einen Wirkungsquerschnitt misst, statt ihn zu berechnen. Sechs Familien von Kanälen, darunter harte QCD, Photoproduktion und der totale Wirkungsquerschnitt. Vorerst Pythia 8.
- **Zwei Maschinenkonfigurationen zusammengefügt.** Ein Leptonenstrahl tritt als Lepton oder als der von ihm abgestrahlte Photonenfluss ein, nie beides in derselben Ziehung: Der Kern zieht beide und behält von jeder den Anteil, der ihr nach ihrem Wirkungsquerschnitt zusteht.
- **Der gemeldete Wirkungsquerschnitt ist der nach dem letzten Ereignis.** Pythia normiert nach seiner Schleife; der Treiber schrieb die laufende Schätzung, die bei einigen hundert Ereignissen um 12 % danebenlag.
- **Das Programm heißt TreeLevel Tools**, und die ausführbare Datei `treelevel-tools.exe`. Es enthält nicht mehr nur Monte-Carlo-Engines.

### Außerdem

- Aufträge nummeriert, mit Zeitstempel versehen und in einer Liste aufbewahrt, die TreeLevel wieder öffnet.
- Wirkungsquerschnitt dort gelesen, wo jeder Generator ihn ablegt: Zeile `C` von Asciiv3, Attribut `GenCrossSection` oder Integrationstabelle.

### Bekanntes Problem

Läuft Sherpa in einer eigenen WSL-Installation statt im Image, fällt sein Wirkungsquerschnitt auf Leptonenstrahlen zu hoch aus: Die QED-Anfangszustandsstrahlung bleibt dort eingeschaltet, und e⁻e⁺ → b b̄ bei 200 GeV ergibt rund fünfzehn Pikobarn statt 3,2. Über das Image `ghcr.io/gpasa/treelevel-tools` ist das behoben.

TreeLevel Tools steht unter GPL v3 oder neuer (siehe `LICENSE.txt` im Archiv); jeder Generator behält seine eigene Lizenz, siehe unten.
