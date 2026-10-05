Die GPL-Werkzeuge, die TreeLevel nicht enthalten darf, auf Ihrem Rechner — nichts verlässt ihn.
TreeLevel läuft in einer Sandbox und startet kein Programm; dieses Paket ist das, was sie ausführen darf.

- `TreeLevel Tools.app` nach `/Applications` ziehen und einmal starten.
- Vier Generatoren sind **bereits enthalten**, sonst ist nichts zu installieren:
  - **Pythia 8** und **Herwig 7** kleiden die Ereignisse von TreeLevel ein: Schauer, Hadronisierung, Zerfälle.
  - **Sherpa 3** und **CalcHEP 3** haben keinen Leser für Les Houches: Sie berechnen den vom Diagramm
    beschriebenen Prozess selbst, anhand einer Beschreibung des Prozesses (Strahlen, Energien, Endzustand,
    Kopplungsordnungen), die das Protokoll ihnen neben den Ereignissen übermittelt.
- TreeLevel bietet sie dann im Arbeitsbereich Erzeugung an.

**WHIZARD 3** ist nicht enthalten: Es kompiliert jeden Prozess mit gfortran, das weder macOS noch Xcode mitbringt.
Zwei Wege, es zu bekommen, beide im Fenster von TreeLevel Tools anzukreuzen:

- das **Docker-Image** `ghcr.io/gpasa/treelevel-tools:0.3.0`, das die fünf Werkzeuge in einer stimmigen Umgebung enthält;
- Ihre **eigene Installation** (MacPorts, Homebrew), falls Sie eine haben.

Keiner der beiden wird standardmäßig verwendet: Ab Werk werden nur die hier mitgelieferten Generatoren angeboten,
damit dasselbe Dokument auf zwei Rechnern dasselbe Ergebnis liefert.

### Gemessen: e⁻e⁺ → W⁺W⁻ bei 200 GeV

| Programm | σ |
|---|---|
| TreeLevel | 19,22 pb |
| WHIZARD 3.1.6 | 19,441 ± 0,006 pb |
| CalcHEP 3.9.2 | 20,42 pb |
| Sherpa 3.0.5 | 18,2 ± 1,1 pb |

Die Abweichungen gehen auf die Wahl des Kopplungsschemas zurück, nicht auf Fehler.

### Außerdem

- Aufträge nummeriert, mit Zeitstempel versehen und in einer Liste aufbewahrt.
- Bibliothekspfade eines Moduls zur Laufzeit korrigiert: Ein anderswo kompiliertes Modul funktioniert, ohne dass man seine Binärdateien anfasst.
- Wirkungsquerschnitt dort gelesen, wo jeder Generator ihn ablegt: Zeile `C` von Asciiv3, Attribut `GenCrossSection` oder Integrationstabelle.

Das README gibt die Rezepte zum Kompilieren der Module unter macOS 26, mit den vier oder fünf Fallen, die die
Werkzeugkette von 2026 für Code von 2023 bereithält.

Signiert und von Apple notarisiert. Prüfsummen in `SHA256SUMS.txt`.
