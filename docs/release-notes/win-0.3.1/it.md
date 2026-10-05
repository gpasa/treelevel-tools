Il motore che fa girare i generatori Monte Carlo per TreeLevel su Windows. Si installa scompattando l'archivio in `%LOCALAPPDATA%\Programs` — nessun programma d'installazione, nulla nel registro. **Per aggiornare** una versione precedente: chiudete TreeLevel, e scompattate l'archivio nello stesso posto sostituendo i file.

Scegliete l'archivio della vostra macchina: `arm64` per un PC Copilot+ o un tablet ARM, `x64` ovunque altrove. Nel dubbio, la x64 funziona anche su ARM, in emulazione.

**Che cosa contiene l'archivio**: il motore e il modulo Pythia 8 compilato per questa architettura. Herwig, Sherpa, WHIZARD e CalcHEP passano dall'immagine container, che richiede Docker Desktop:

```
docker pull ghcr.io/gpasa/treelevel-tools
```

Nient'altro da fare: TreeLevel crea da sé un container effimero per ogni lavoro. Docker Desktop deve essere avviato quando TreeLevel parte; i generatori dell'immagine compaiono allora, contrassegnati «(Docker)».

**Il motore non ha finestra.** È TreeLevel a lanciarlo, a ogni necessità. Se fate doppio clic su `treelevel-tools.exe`, Windows SmartScreen avverte di un'applicazione non riconosciuta — il motore non è firmato — e, superato l'avviso, una console mostra le sue istruzioni d'uso e si richiude. È normale, e senza effetto: non dovete mai lanciarlo voi stessi.

### Correzioni di questa versione

- **L'immagine scaricata senza numero è riconosciuta.** La 0.3.0 riconosceva solo il tag `:0.3.0`; ma il comando che propone la pagina del pacchetto, e quello che tutti digitano, scarica `:latest`. L'immagine era sulla macchina, rispondeva quando la si lanciava a mano, eppure TreeLevel offriva solo Pythia. I due tag designano la stessa immagine, ed entrambi sono ora riconosciuti.
- **Sherpa su fasci di leptoni**, quando gira fuori dall'immagine: la sua sezione d'urto non è più gonfiata dalla radiazione iniziale di QED (una quindicina di picobarn invece di 3,2 per e⁻e⁺ → b b̄ a 200 GeV). La via che ne dipendeva — Sherpa installato da sé in WSL — sarà rimossa in una prossima versione: Docker è la via prevista.

### Cinque generatori, due famiglie

**Pythia 8** e **Herwig 7** vestono gli eventi partonici che TreeLevel dà loro: sciame, adronizzazione, decadimenti.

**Sherpa 3**, **WHIZARD 3** e **CalcHEP 3** non hanno un lettore Les Houches — calcolano da sé il processo descritto dal diagramma. Il protocollo trasmette loro quindi una descrizione del processo (fasci, energie, stato finale, ordini di accoppiamento) accanto agli eventi.

### Misurato: e⁻e⁺ → W⁺W⁻ a 200 GeV

| motore | σ |
|---|---|
| TreeLevel | 19,22 pb |
| WHIZARD 3.1.6 | 19,441 ± 0,006 pb |
| CalcHEP 3.9.2 | 20,42 pb |
| Sherpa 3.0.5 | 18,2 ± 1,1 pb |

Gli scarti sono scelte di schema degli accoppiamenti, non errori.

### Promemoria: che cosa portava la 0.3.0

- **La modalità collisore.** Il generatore riceve solo i fasci e l'energia, mai uno stato finale: produce l'intera miscela, come una vera macchina, e TreeLevel conta poi gli eventi che portano la firma del processo disegnato — il che misura una sezione d'urto invece di calcolarla. Sei famiglie di canali, tra cui la QCD dura, la fotoproduzione e la sezione d'urto totale. Per ora Pythia 8.
- **Due configurazioni di macchina assemblate.** Un fascio di leptoni entra come leptone o come il flusso di fotoni che irraggia, mai entrambi in una stessa estrazione: il motore estrae entrambi e tiene di ciascuno la parte che la sua sezione d'urto gli vale.
- **La sezione d'urto riportata è quella dopo l'ultimo evento.** Pythia normalizza dopo il suo ciclo; il driver scriveva la stima corrente, sbagliata del 12 % su qualche centinaio di eventi.
- **Il programma si chiama TreeLevel Tools**, e l'eseguibile `treelevel-tools.exe`.
- Lavori numerati, datati e conservati in un elenco, che TreeLevel riapre; sezione d'urto letta là dove ogni generatore la mette.

TreeLevel Tools è sotto GPL v3 o successiva (vedi `LICENSE.txt` nell'archivio); ogni generatore mantiene la propria licenza, qui sotto.
