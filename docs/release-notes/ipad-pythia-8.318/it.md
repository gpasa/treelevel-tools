Pythia 8 compilato in WebAssembly, con il driver comune di TreeLevel Tools. TreeLevel su iPad lo scarica
da questa pagina, file per file, e verifica ciascuno con un'impronta fissata nell'app; lo esegue
in una vista web, senza inviare nulla da nessuna parte. Gli eventi ne escono con sciame e adronizzazione, e la
sorgente Macchina di TreeLevel diventa disponibile su iPad.

| file | ruolo |
|---|---|
| `treelevel-pythia-web.wasm`, `.js` | Pythia 8.318 e il driver, in WebAssembly |
| `runner.js` | conduce un lavoro di TreeLevel: piano, parti, riunione |
| `leptons.pack` | dati di Pythia (xmldoc, tunes, setups) — fasci di leptoni |
| `pdfdata.pack` | densità partoniche — fasci di adroni, facoltativo |
| `pythia8318-sources.tgz` | i sorgenti di Pythia 8.318, così come pubblicati su pythia.org |
| `COPYING.pythia8` | la licenza di Pythia (GPL v2 o successiva) |

### Pythia 8, i suoi autori

Pythia 8 è © Torbjörn Sjöstrand e la collaborazione Pythia — [pythia.org](https://pythia.org) — e distribuito
sotto GPL v2 o successiva. Tutta la fisica di questo modulo è loro. Se pubblicate un risultato ottenuto con esso,
citate: C. Bierlich et al., «A comprehensive guide to the physics and usage of PYTHIA 8.3»,
*SciPost Phys. Codebases* 8 (2022), [arXiv:2203.11601](https://arxiv.org/abs/2203.11601).

Gli altri generatori pilotati da TreeLevel Tools, e i loro autori:
[CREDITS.md](https://github.com/gpasa/treelevel-tools/blob/1.3-dev/CREDITS.md).
Resta un programma separato da TreeLevel: l'app gli passa un lavoro e ne rilegge il risultato. I sorgenti del
driver e di `runner.js` sono in questo repository, al tag di questa release (`Backends/pythia`).
Somme di controllo in `SHA256SUMS.txt`.
