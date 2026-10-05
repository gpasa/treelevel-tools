> **Sostituita dalla [0.3.1](https://github.com/gpasa/treelevel-tools/releases/tag/win-0.3.1).** Questa riconosce l'immagine solo con il tag `:0.3.0`; la 0.3.1 accetta anche `:latest`, quello che scarica `docker pull` senza numero.

Il motore che fa girare i generatori Monte Carlo per TreeLevel su Windows. Si installa scompattando l'archivio in `%LOCALAPPDATA%\Programs` — nessun programma d'installazione, nulla nel registro.

Scegliete l'archivio della vostra macchina: `arm64` per un PC Copilot+ o un tablet ARM, `x64` ovunque altrove. Nel dubbio, la x64 funziona anche su ARM, in emulazione.

**Che cosa contiene l'archivio**: il motore e il modulo Pythia 8 compilato per questa architettura. Herwig, Sherpa, WHIZARD e CalcHEP passano dall'immagine container `ghcr.io/gpasa/treelevel-tools`, che richiede Docker. Scaricatela **con il suo numero**:

```
docker pull ghcr.io/gpasa/treelevel-tools:0.3.0
```

Questa versione del motore riconosce solo questo tag: un'immagine scaricata senza numero (quindi `:latest`) è sì sulla macchina, ma TreeLevel non ne propone i generatori. I due tag designano la stessa immagine; se avete già `latest`, il comando qui sopra aggiunge solo il tag. Docker Desktop deve essere avviato quando TreeLevel parte.

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

### Novità di questa versione

- **La modalità collisore.** Il generatore riceve solo i fasci e l'energia, mai uno stato finale: produce l'intera miscela, come una vera macchina, e TreeLevel conta poi gli eventi che portano la firma del processo disegnato — il che misura una sezione d'urto invece di calcolarla. Sei famiglie di canali, tra cui la QCD dura, la fotoproduzione e la sezione d'urto totale. Per ora Pythia 8.
- **Due configurazioni di macchina assemblate.** Un fascio di leptoni entra come leptone o come il flusso di fotoni che irraggia, mai entrambi in una stessa estrazione: il motore estrae entrambi e tiene di ciascuno la parte che la sua sezione d'urto gli vale.
- **La sezione d'urto riportata è quella dopo l'ultimo evento.** Pythia normalizza dopo il suo ciclo; il driver scriveva la stima corrente, sbagliata del 12 % su qualche centinaio di eventi.
- **Il programma si chiama TreeLevel Tools**, e l'eseguibile `treelevel-tools.exe`. Non porta più soltanto motori Monte Carlo.

### Inoltre

- Lavori numerati, datati e conservati in un elenco, che TreeLevel riapre.
- Sezione d'urto letta là dove ogni generatore la mette: riga `C` di Asciiv3, attributo `GenCrossSection`, o tabella d'integrazione.

### Problema noto

Se Sherpa gira in un'installazione WSL personale anziché nell'immagine, la sua sezione d'urto su fasci di leptoni risulta troppo alta: la radiazione iniziale di QED vi resta accesa, ed e⁻e⁺ → b b̄ a 200 GeV dà una quindicina di picobarn invece di 3,2. Tramite l'immagine `ghcr.io/gpasa/treelevel-tools`, è corretto.

TreeLevel Tools è sotto GPL v3 o successiva (vedi `LICENSE.txt` nell'archivio); ogni generatore mantiene la propria licenza, qui sotto.
