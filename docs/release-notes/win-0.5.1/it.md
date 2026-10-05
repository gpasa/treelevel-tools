Il motore che fa girare i generatori Monte Carlo per TreeLevel 1.4 su Windows (e sempre 1.3). Si installa scompattando l'archivio in `%LOCALAPPDATA%\Programs` — nessun programma d'installazione, nulla nel registro. **Per aggiornare** una versione precedente: chiudete TreeLevel, e scompattate l'archivio nello stesso posto sostituendo i file.

Scegliete l'archivio della vostra macchina: `arm64` per un PC Copilot+ o un tablet ARM, `x64` ovunque altrove. Nel dubbio, la x64 funziona anche su ARM, in emulazione.

**Che cosa contiene l'archivio**: `treelevel-tools.exe`, che TreeLevel lancia; `treelevel-engine.exe`, il motore che scrive la scheda di ogni generatore e lo conduce; il modulo Pythia 8 compilato per questa architettura; `CREDITS.md`. Herwig, Sherpa, WHIZARD e CalcHEP passano dall'immagine container, che richiede Docker Desktop:

```
docker pull ghcr.io/gpasa/treelevel-tools:latest
```

Nient'altro da fare: TreeLevel crea da sé un container effimero per ogni lavoro. Docker Desktop deve essere avviato quando TreeLevel parte; i generatori dell'immagine compaiono allora, contrassegnati «(Docker)».

**Il motore non ha finestra.** È TreeLevel a lanciarlo, a ogni necessità. Se fate doppio clic su `treelevel-tools.exe`, Windows SmartScreen avverte di un'applicazione non riconosciuta — il motore non è firmato — e, superato l'avviso, una console mostra le sue istruzioni d'uso e si richiude. È normale, e senza effetto.

### Che cosa cambia

- **L'host chiede l'immagine 0.5.0.** È pubblicata e `:latest` punta su di essa; il motore Windows cerca prima `ghcr.io/gpasa/treelevel-tools:0.5.0`, poi `:latest`, come prima. Con l'immagine 0.5.0, la casella «Tout faire tourner dans l'image Docker» dà anche la zona di interazione (l'immagine annuncia `spaceTimeGenerators`).
- **Per approfittarne con Docker**: `docker pull ghcr.io/gpasa/treelevel-tools:latest` (o `:0.5.0`) sostituisce l'immagine 0.4.0.
- **Nient'altro si muove**: stesso driver Pythia e stesse chiavi del lavoro di `win-0.5.0`; compatibile con TreeLevel 1.3 e 1.4.
