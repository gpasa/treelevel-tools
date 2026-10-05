Gli strumenti GPL che TreeLevel non può contenere, sulla vostra macchina — nulla ne esce. TreeLevel è in sandbox e
non lancia alcun programma; questo pacchetto è ciò che ha il diritto di eseguirli.

### Novità della 0.5.0

- **Pythia 8 colloca le particelle nella zona di interazione** quando TreeLevel 1.4 glielo chiede (l'opzione
  «posizioni nella zona di interazione»): dove nasce ogni adrone, alla scala del femtometro, il flusso di colore e lo
  stato dei partoni, e un unico spostamento della regione luminosa per tutto l'evento. TreeLevel lo mostra alla
  scala del femtometro, nelle sezioni e in 3D.
- TreeLevel 1.3 non chiede nulla di tutto ciò e riceve gli stessi eventi che con la 0.4.0; stessi generatori, stesse
  versioni.
- Provato su un Mac Apple Silicon e su un iMac Intel: ogni generatore incluso conduce un vero lavoro.

### Installare

- Per Mac **Apple Silicon e Intel**, macOS 13 o successivo.
- Trascinare `TreeLevel Tools.app` in `/Applications` e avviarla una volta.
- Quattro generatori sono **già dentro**, nient'altro da installare:
  - **Pythia 8** e **Herwig 7** vestono gli eventi di TreeLevel tra due leptoni: sciame, adronizzazione,
    decadimenti. **Pythia 8** pilota anche la sorgente Macchina: due fasci, un'energia, e tutto ciò che la
    collisione produce.
  - **Sherpa 3** e **CalcHEP 3** calcolano da sé il processo descritto dal diagramma.
- TreeLevel li propone allora nello spazio Generazione.

Le schede di tutti i generatori sono scritte dallo stesso motore C++ che all'interno dell'immagine Docker: uno stesso
lavoro dà la stessa scheda sul Mac e sotto Linux.

**WHIZARD 3** non è incluso: compila ogni processo con gfortran, che né macOS né Xcode forniscono. Due modi per
averlo, da spuntare nella finestra di TreeLevel Tools:

- l'**immagine Docker** `ghcr.io/gpasa/treelevel-tools:latest`, che porta i cinque strumenti; spuntata, conduce
  **tutti** i lavori, e i generatori forniti qui tacciono;
- la vostra **installazione personale** (MacPorts, Homebrew), se ne avete una.

Nessuna delle due è usata di default: in partenza sono proposti solo i generatori forniti qui, perché uno stesso
documento dia lo stesso risultato su due macchine.

Firmato e notarizzato da Apple. Somme di controllo in `SHA256SUMS.txt`.
