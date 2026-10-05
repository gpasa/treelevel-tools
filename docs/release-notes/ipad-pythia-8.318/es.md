Pythia 8 compilado a WebAssembly, con el controlador común de TreeLevel Tools. TreeLevel en iPad lo descarga
desde esta página, archivo por archivo, y comprueba cada uno contra una huella fijada en la app; lo ejecuta
en una vista web, sin enviar nada a ninguna parte. Los sucesos salen con cascada y hadronizados, y la
fuente Máquina de TreeLevel pasa a estar disponible en iPad.

| archivo | función |
|---|---|
| `treelevel-pythia-web.wasm`, `.js` | Pythia 8.318 y el controlador, en WebAssembly |
| `runner.js` | lleva a cabo un trabajo de TreeLevel: plan, partes, reunión |
| `leptons.pack` | datos de Pythia (xmldoc, tunes, setups) — haces de leptones |
| `pdfdata.pack` | densidades de partones — haces de hadrones, opcional |
| `pythia8318-sources.tgz` | las fuentes de Pythia 8.318, tal como se publican en pythia.org |
| `COPYING.pythia8` | la licencia de Pythia (GPL v2 o posterior) |

### Pythia 8 y sus autores

Pythia 8 es © Torbjörn Sjöstrand y la colaboración Pythia — [pythia.org](https://pythia.org) — y se distribuye
bajo GPL v2 o posterior. Toda la física de este módulo es suya. Si publica un resultado obtenido con él,
cite: C. Bierlich et al., «A comprehensive guide to the physics and usage of PYTHIA 8.3»,
*SciPost Phys. Codebases* 8 (2022), [arXiv:2203.11601](https://arxiv.org/abs/2203.11601).

Los demás generadores controlados por TreeLevel Tools, y sus autores:
[CREDITS.md](https://github.com/gpasa/treelevel-tools/blob/1.3-dev/CREDITS.md).
Sigue siendo un programa separado de TreeLevel: la app le pasa un trabajo y relee el resultado. Las fuentes del
controlador y de `runner.js` están en este repositorio, en la etiqueta de esta versión (`Backends/pythia`).
Sumas de control en `SHA256SUMS.txt`.
