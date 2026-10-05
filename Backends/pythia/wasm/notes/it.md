Versione del modulo: **$MODULE** — Pythia **$PYTHIA_VERSION**, compilato in WebAssembly con il driver comune di
TreeLevel Tools $MODULE. Questa pagina mantiene sempre lo stesso nome: TreeLevel su iPad (1.4 e successive) vi prende
l'ultima versione, ne legge il numero in `module.json` e lo mostra nelle sue impostazioni, propone l'aggiornamento
quando esce una versione più recente, e verifica ogni file contro l'impronta che `module.json` ne fornisce. Esegue il
modulo in una vista web, senza inviare nulla da nessuna parte.

Ciò che questo modulo sa fare: `$FEATURES`. «spacetime»: collocare partoni e adroni nella zona di interazione, che
TreeLevel mostra alla scala del femtometro.

| file | ruolo |
|---|---|
| `module.json` | versione del modulo e di Pythia, ciò che sa fare, l'impronta di ogni file |
| `treelevel-pythia-web.wasm`, `.js` | Pythia $PYTHIA_VERSION e il driver, in WebAssembly |
| `runner.js` | conduce un lavoro di TreeLevel: piano, parti, riunione |
| `leptons.pack` | dati di Pythia (xmldoc, tunes, setups) — fasci di leptoni |
| `pdfdata.pack` | densità partoniche — fasci di adroni, facoltativo |
| `$SOURCES` | i sorgenti di Pythia $PYTHIA_VERSION, così come pubblicati su pythia.org |
| `COPYING.pythia8` | la licenza di Pythia (GPL v2 o successiva) |

TreeLevel 1.3 su iPad scarica il suo modulo da
[ipad-pythia-8.318](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia-8.318), di cui fissa le
impronte: quella pagina non cambia.

**Pythia 8 e i suoi autori.** Pythia 8 è © Torbjörn Sjöstrand e la collaborazione Pythia —
[pythia.org](https://pythia.org) — ed è distribuito sotto GPL v2 o successiva. Tutta la fisica di questo modulo è
loro. Se pubblicate un risultato ottenuto con esso, citate: C. Bierlich et al., «A comprehensive guide to the physics
and usage of PYTHIA 8.3», *SciPost Phys. Codebases* 8 (2022), [arXiv:2203.11601](https://arxiv.org/abs/2203.11601).
Gli altri generatori pilotati da TreeLevel Tools, e i loro autori:
[CREDITS.md](https://github.com/gpasa/treelevel-tools/blob/main/CREDITS.md).

Resta un programma separato da TreeLevel: l'app gli passa un lavoro e ne rilegge il risultato. I sorgenti del driver
e di `runner.js` sono in questo repository (`Backends/pythia`), al tag `ipad-pythia-module-$MODULE`. Somme di
controllo in `SHA256SUMS.txt`.
