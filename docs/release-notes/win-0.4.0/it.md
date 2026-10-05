Il motore che fa girare i generatori Monte Carlo per TreeLevel 1.3 su Windows. Si installa scompattando l'archivio in `%LOCALAPPDATA%\Programs` — nessun programma d'installazione, nulla nel registro. **Per aggiornare** una versione precedente: chiudete TreeLevel, e scompattate l'archivio nello stesso posto sostituendo i file.

Scegliete l'archivio della vostra macchina: `arm64` per un PC Copilot+ o un tablet ARM, `x64` ovunque altrove. Nel dubbio, la x64 funziona anche su ARM, in emulazione.

**Che cosa contiene l'archivio**: `treelevel-tools.exe`, che TreeLevel lancia; `treelevel-engine.exe`, il motore che scrive la scheda di ogni generatore e lo conduce; il modulo Pythia 8 compilato per questa architettura; `CREDITS.md`. Herwig, Sherpa, WHIZARD e CalcHEP passano dall'immagine container, che richiede Docker Desktop:

```
docker pull ghcr.io/gpasa/treelevel-tools:0.4.0
```

Nient'altro da fare: TreeLevel crea da sé un container effimero per ogni lavoro. Docker Desktop deve essere avviato quando TreeLevel parte; i generatori dell'immagine compaiono allora, contrassegnati «(Docker)».

**Il motore non ha finestra.** È TreeLevel a lanciarlo, a ogni necessità. Se fate doppio clic su `treelevel-tools.exe`, Windows SmartScreen avverte di un'applicazione non riconosciuta — il motore non è firmato — e, superato l'avviso, una console mostra le sue istruzioni d'uso e si richiude. È normale, e senza effetto.

### Che cosa cambia

- **Un solo motore per Windows, il Mac e l'immagine.** Le schede dei generatori sono ormai scritte una volta sola, in C++ (`Backends/engine`), e lo stesso programma gira qui, sul Mac e nel container. La parte Windows non fa più che trovare Docker, l'immagine e il modulo Pythia.
- **«Tout faire tourner dans l'image Docker»**, una casella delle Impostazioni di TreeLevel 1.3. Spuntata, l'immagine conduce tutti i lavori, Pythia compreso, e nulla è proposto quando mancano Docker o l'immagine. Non spuntata, Pythia gira in nativo e il resto passa dall'immagine.
- **Ciò che l'esperimento registra**: la sorgente Macchina di TreeLevel 1.3 sceglie un fenomeno — tutto ciò che il rivelatore vede, la diffusione tramite un fotone, l'annichilazione in γ*/Z, il W scambiato o prodotto, le coppie di bosoni, i getti, la fotoproduzione, le collisioni molli —, e il motore lo apre con la soglia che gli conviene (Q² per le diffusioni, p_T per i getti).
- **Dove è nata ogni particella**: il driver Pythia scrive la posizione dei vertici, e il processo duro di ogni evento; TreeLevel li disegna e filtra in base a essi.
- **Pythia 8.318** ovunque, con i suoi tune (`Monash 2013`, `A14`…) tradotti in numeri di Pythia.
- **Percorsi con accenti**: una cartella di lavoro sotto un nome utente con accenti si apre come un'altra.
- Rimossa: la via WSL (Herwig o Sherpa installati a mano in una distribuzione) — Docker è la via prevista.

TreeLevel Tools è sotto GPL v3 o successiva (vedi `LICENSE.txt` nell'archivio); ogni generatore mantiene la propria licenza — vedi `CREDITS.md`, e qui sotto.
