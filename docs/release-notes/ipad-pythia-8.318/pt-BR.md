O Pythia 8 compilado em WebAssembly, com o driver comum do TreeLevel Tools. O TreeLevel no iPad o baixa
desta página, arquivo por arquivo, e verifica cada um contra uma impressão digital fixada no app; ele o executa
numa visualização web, sem enviar nada a lugar nenhum. Os eventos saem com chuveiro e hadronizados, e a
fonte Máquina do TreeLevel passa a estar disponível no iPad.

| arquivo | função |
|---|---|
| `treelevel-pythia-web.wasm`, `.js` | Pythia 8.318 e o driver, em WebAssembly |
| `runner.js` | conduz um trabalho do TreeLevel: plano, partes, junção |
| `leptons.pack` | dados do Pythia (xmldoc, tunes, setups) — feixes de léptons |
| `pdfdata.pack` | densidades de pártons — feixes de hádrons, opcional |
| `pythia8318-sources.tgz` | as fontes do Pythia 8.318, tal como publicadas em pythia.org |
| `COPYING.pythia8` | a licença do Pythia (GPL v2 ou posterior) |

### O Pythia 8 e seus autores

O Pythia 8 é © Torbjörn Sjöstrand e a colaboração Pythia — [pythia.org](https://pythia.org) — e distribuído
sob GPL v2 ou posterior. Toda a física deste módulo é deles. Se você publicar um resultado obtido com ele,
cite: C. Bierlich et al., “A comprehensive guide to the physics and usage of PYTHIA 8.3”,
*SciPost Phys. Codebases* 8 (2022), [arXiv:2203.11601](https://arxiv.org/abs/2203.11601).

Os outros geradores conduzidos pelo TreeLevel Tools, e seus autores:
[CREDITS.md](https://github.com/gpasa/treelevel-tools/blob/1.3-dev/CREDITS.md).
Ele continua sendo um programa separado do TreeLevel: o app lhe passa um trabalho e lê de volta o resultado. As fontes do
driver e de `runner.js` estão neste repositório, na etiqueta desta versão (`Backends/pythia`).
Somas de verificação em `SHA256SUMS.txt`.
