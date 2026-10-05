Gli strumenti sotto licenza GPL che TreeLevel non può contenere, sulla vostra macchina — nulla ne esce.
TreeLevel è in sandbox e non lancia alcun programma; questo pacchetto è ciò che ha il diritto di eseguirli.

- Trascinare `TreeLevel Tools.app` in `/Applications` e avviarla una volta.
- Quattro generatori sono **già dentro**, nient'altro da installare:
  - **Pythia 8** e **Herwig 7** vestono gli eventi di TreeLevel: sciame, adronizzazione, decadimenti.
  - **Sherpa 3** e **CalcHEP 3** non hanno un lettore Les Houches: calcolano da sé il processo descritto
    dal diagramma, a partire da una descrizione del processo (fasci, energie, stato finale, ordini di accoppiamento)
    che il protocollo trasmette loro accanto agli eventi.
- TreeLevel li propone allora nello spazio Generazione.

**WHIZARD 3** non è incluso: compila ogni processo con gfortran, che né macOS né Xcode forniscono.
Due modi per averlo, entrambi da spuntare nella finestra di TreeLevel Tools:

- l'**immagine Docker** `ghcr.io/gpasa/treelevel-tools:0.3.0`, che porta i cinque strumenti in un ambiente coerente;
- la vostra **installazione personale** (MacPorts, Homebrew), se ne avete una.

Nessuna delle due è usata di default: in partenza sono proposti solo i generatori forniti qui, perché uno stesso
documento dia lo stesso risultato su due macchine.

### Misurato: e⁻e⁺ → W⁺W⁻ a 200 GeV

| motore | σ |
|---|---|
| TreeLevel | 19,22 pb |
| WHIZARD 3.1.6 | 19,441 ± 0,006 pb |
| CalcHEP 3.9.2 | 20,42 pb |
| Sherpa 3.0.5 | 18,2 ± 1,1 pb |

Gli scarti sono scelte di schema degli accoppiamenti, non errori.

### Inoltre

- Lavori numerati, datati e conservati in un elenco.
- Percorsi delle librerie di un modulo corretti all'esecuzione: un modulo compilato altrove funziona senza ritoccarne i binari.
- Sezione d'urto letta là dove ogni generatore la mette: riga `C` di Asciiv3, attributo `GenCrossSection`, o tabella d'integrazione.

Il README dà le ricette di compilazione dei moduli su macOS 26, con le quattro o cinque trappole che la
catena di strumenti del 2026 riserva a codici del 2023.

Firmato e notarizzato da Apple. Somme di controllo in `SHA256SUMS.txt`.
