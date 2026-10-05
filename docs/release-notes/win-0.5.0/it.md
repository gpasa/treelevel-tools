Il motore che fa girare i generatori Monte Carlo per TreeLevel 1.4 su Windows (e sempre 1.3). Si installa scompattando l'archivio in `%LOCALAPPDATA%\Programs` — nessun programma d'installazione, nulla nel registro. **Per aggiornare** una versione precedente: chiudete TreeLevel, e scompattate l'archivio nello stesso posto sostituendo i file.

Scegliete l'archivio della vostra macchina: `arm64` per un PC Copilot+ o un tablet ARM, `x64` ovunque altrove. Nel dubbio, la x64 funziona anche su ARM, in emulazione.

**Che cosa contiene l'archivio**: `treelevel-tools.exe`, che TreeLevel lancia; `treelevel-engine.exe`, il motore che scrive la scheda di ogni generatore e lo conduce; il modulo Pythia 8 compilato per questa architettura; `CREDITS.md`. Herwig, Sherpa, WHIZARD e CalcHEP passano dall'immagine container, che richiede Docker Desktop:

```
docker pull ghcr.io/gpasa/treelevel-tools:latest
```

Nient'altro da fare: TreeLevel crea da sé un container effimero per ogni lavoro. Docker Desktop deve essere avviato quando TreeLevel parte; i generatori dell'immagine compaiono allora, contrassegnati «(Docker)».

**Il motore non ha finestra.** È TreeLevel a lanciarlo, a ogni necessità. Se fate doppio clic su `treelevel-tools.exe`, Windows SmartScreen avverte di un'applicazione non riconosciuta — il motore non è firmato — e, superato l'avviso, una console mostra le sue istruzioni d'uso e si richiude. È normale, e senza effetto.

### Che cosa cambia

- **La zona di interazione, al femtometro.** Per TreeLevel 1.4, il driver Pythia sa collocare ogni interazione partonica nella sovrapposizione dei due adroni e ogni adrone là dove la sua stringa si è rotta (chiave `spaceTime` del lavoro: `PartonVertex:setVertex`, `Fragmentation:setVertices`). Scrive per ogni partone il suo flusso di colore e il suo stato Pythia, e per ogni particella nata altrove che nel suo vertice il proprio luogo di nascita — ciò che la sezione ingrandita e la vista 3D di TreeLevel 1.4 disegnano. È il modello del generatore, nulla di misurato.
- **Un unico spostamento della regione luminosa.** Con queste posizioni, Pythia spostava gli adroni due volte; il driver colloca ora l'evento da sé, con un solo vettore. Senza la chiave, nulla cambia.
- **Il motore dice che cosa sa fare**: `treelevel-tools capabilities` annuncia `spaceTimeGenerators` (Pythia nativo quando il suo driver risponde «spacetime», e ciò che annuncia l'immagine). TreeLevel 1.4 mostra la casella «posizioni nella zona di interazione» solo se vi figura.
- **Compatibile con TreeLevel 1.3**: un lavoro senza la chiave `spaceTime` gira esattamente come con la 0.4.0.
- **L'immagine Docker 0.5** segue: fino ad allora, `:latest` è l'immagine 0.4.0, e Herwig, Sherpa, WHIZARD e CalcHEP vi girano come prima; la zona di interazione passa dal Pythia nativo di questo archivio.
- **Lo stesso motore di `mac-0.5.0`**: stesso driver Pythia (`Backends/pythia/main.cpp`), stesse chiavi del lavoro, stessi attributi scritti.
