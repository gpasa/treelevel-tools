I generatori di eventi di [TreeLevel](https://treelevel.pasahome.org), sulla vostra macchina. TreeLevel scrive un
lavoro in una cartella locale; questo programma lo affida a **Pythia 8**, **Herwig 7**, **Sherpa 3**, **WHIZARD 3** o
**CalcHEP 3** — sciame e adronizzazione dei suoi eventi, o collisioni intere di una macchina — e riscrive il
risultato in HepMC3, che TreeLevel rilegge. Nulla passa per la rete, nessun account, nessun servizio. Su iPad,
Pythia 8 compilato in WebAssembly svolge lo stesso ruolo, scaricato dalla
[sua release](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia).

È distribuito separatamente perché questi generatori sono sotto licenza **GPL**: questo repository è GPL v3, e
TreeLevel non contiene nulla del loro codice.

| sistema | scaricare | cosa contiene |
|---|---|---|
| **macOS** 13 o successivo, Apple Silicon e Intel | [TreeLevelTools-0.5.0.dmg](https://github.com/gpasa/treelevel-tools/releases/download/mac-0.5.0/TreeLevelTools-0.5.0.dmg) | Pythia 8, Herwig 7, Sherpa 3 e CalcHEP 3, pronti all'uso |
| **Windows** 10 e 11 | [x64](https://github.com/gpasa/treelevel-tools/releases/download/win-0.5.1/TreeLevelTools-0.5.1-x64.zip) · [ARM64](https://github.com/gpasa/treelevel-tools/releases/download/win-0.5.1/TreeLevelTools-0.5.1-arm64.zip) | Pythia 8; gli altri tramite l'immagine Docker |
| **iPad** | dalle impostazioni di TreeLevel ([la release](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia)) | Pythia 8 in WebAssembly |
| **Docker**, qualsiasi sistema | `docker pull ghcr.io/gpasa/treelevel-tools:latest` | i cinque generatori, WHIZARD 3 compreso |

**Mac**: trascinare `TreeLevel Tools.app` in `/Applications` e avviarla una volta; TreeLevel propone allora i suoi
generatori nello spazio Generazione. **Windows**: estrarre l'archivio in `%LOCALAPPDATA%\Programs`. **iPad**: la
scheda *Modulo Pythia 8* delle impostazioni lo scarica e verifica ogni file. **Docker**: con l'immagine presente,
TreeLevel Tools vi esegue i generatori che nessun modulo offre (sul Mac, una casella gli affida tutti i lavori).
