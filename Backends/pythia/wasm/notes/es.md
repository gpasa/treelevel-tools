Versión del módulo: **$MODULE** — Pythia **$PYTHIA_VERSION**, compilado a WebAssembly con el controlador común de
TreeLevel Tools $MODULE. Esta página conserva siempre el mismo nombre: TreeLevel en iPad (1.4 y posteriores) toma de
ella la última versión, lee su número en `module.json` y lo muestra en sus ajustes, propone la actualización cuando
se publica una versión más reciente, y comprueba cada archivo contra la huella que `module.json` da de él. Ejecuta el
módulo en una vista web, sin enviar nada a ninguna parte.

Lo que este módulo sabe hacer: `$FEATURES`. «spacetime»: situar partones y hadrones en la zona de interacción, que
TreeLevel muestra a escala del femtómetro.

| archivo | función |
|---|---|
| `module.json` | versión del módulo y de Pythia, lo que sabe hacer, la huella de cada archivo |
| `treelevel-pythia-web.wasm`, `.js` | Pythia $PYTHIA_VERSION y el controlador, en WebAssembly |
| `runner.js` | lleva a cabo un trabajo de TreeLevel: plan, partes, reunión |
| `leptons.pack` | datos de Pythia (xmldoc, tunes, setups) — haces de leptones |
| `pdfdata.pack` | densidades de partones — haces de hadrones, opcional |
| `$SOURCES` | las fuentes de Pythia $PYTHIA_VERSION, tal como se publican en pythia.org |
| `COPYING.pythia8` | la licencia de Pythia (GPL v2 o posterior) |

TreeLevel 1.3 en iPad descarga su módulo desde
[ipad-pythia-8.318](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia-8.318), cuyas huellas fija:
esa página no cambia.

**Pythia 8 y sus autores.** Pythia 8 es © Torbjörn Sjöstrand y la colaboración Pythia —
[pythia.org](https://pythia.org) — y se distribuye bajo la GPL v2 o posterior. Toda la física de este módulo es
suya. Si publica un resultado obtenido con él, cite: C. Bierlich et al., «A comprehensive guide to the physics and
usage of PYTHIA 8.3», *SciPost Phys. Codebases* 8 (2022), [arXiv:2203.11601](https://arxiv.org/abs/2203.11601).
Los demás generadores controlados por TreeLevel Tools, y sus autores:
[CREDITS.md](https://github.com/gpasa/treelevel-tools/blob/main/CREDITS.md).

Sigue siendo un programa separado de TreeLevel: la app le pasa un trabajo y relee el resultado. Las fuentes del
controlador y de `runner.js` están en este repositorio (`Backends/pythia`), en la etiqueta
`ipad-pythia-module-$MODULE`. Sumas de control en `SHA256SUMS.txt`.
