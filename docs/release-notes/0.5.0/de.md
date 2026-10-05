Die GPL-Werkzeuge, die TreeLevel nicht enthalten darf, auf Ihrem Rechner — nichts verlässt ihn. TreeLevel läuft in
einer Sandbox und startet kein Programm; dieses Paket ist das, was sie ausführen darf.

### Neu in 0.5.0

- **Pythia 8 platziert die Teilchen in der Wechselwirkungszone**, wenn TreeLevel 1.4 es verlangt (die Option
  „Positionen in der Wechselwirkungszone“): wo jedes Hadron entsteht, auf Femtometerskala, der Farbfluss und der
  Status der Partonen, und ein einziger Versatz der Kollisionszone für das ganze Ereignis. TreeLevel zeigt es
  auf Femtometerskala, in den Schnitten und in 3D.
- TreeLevel 1.3 verlangt nichts davon und erhält dieselben Ereignisse wie mit 0.4.0; dieselben Generatoren,
  dieselben Versionen.
- Erprobt auf einem Mac mit Apple Silicon und auf einem Intel-iMac: Jeder mitgelieferte Generator führt einen echten
  Auftrag aus.

### Installieren

- Für Macs mit **Apple Silicon und Intel**, macOS 13 oder neuer.
- `TreeLevel Tools.app` nach `/Applications` ziehen und einmal starten.
- Vier Generatoren sind **bereits enthalten**, sonst ist nichts zu installieren:
  - **Pythia 8** und **Herwig 7** kleiden die Ereignisse von TreeLevel zwischen zwei Leptonen ein: Schauer,
    Hadronisierung, Zerfälle. **Pythia 8** steuert auch die Quelle Maschine: zwei Strahlen, eine Energie und alles,
    was die Kollision erzeugt.
  - **Sherpa 3** und **CalcHEP 3** berechnen den vom Diagramm beschriebenen Prozess selbst.
- TreeLevel bietet sie dann im Arbeitsbereich Erzeugung an.

Die Karten aller Generatoren werden von derselben C++-Engine geschrieben wie im Docker-Image: Derselbe Auftrag ergibt
dieselbe Karte auf dem Mac und unter Linux.

**WHIZARD 3** ist nicht enthalten: Es kompiliert jeden Prozess mit gfortran, das weder macOS noch Xcode mitbringt.
Zwei Wege, es zu bekommen, im Fenster von TreeLevel Tools anzukreuzen:

- das **Docker-Image** `ghcr.io/gpasa/treelevel-tools:latest`, das die fünf Werkzeuge enthält; angekreuzt führt es
  **alle** Aufträge aus, und die hier mitgelieferten Generatoren schweigen;
- Ihre **eigene Installation** (MacPorts, Homebrew), falls Sie eine haben.

Keiner der beiden wird standardmäßig verwendet: Ab Werk werden nur die hier mitgelieferten Generatoren angeboten,
damit dasselbe Dokument auf zwei Rechnern dasselbe Ergebnis liefert.

Signiert und von Apple notarisiert. Prüfsummen in `SHA256SUMS.txt`.
