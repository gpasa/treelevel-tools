Versão do módulo: **$MODULE** — Pythia **$PYTHIA_VERSION**, compilado em WebAssembly com o driver comum do
TreeLevel Tools $MODULE. Esta página mantém sempre o mesmo nome: o TreeLevel no iPad (1.4 e posteriores) obtém
dela a versão mais recente, lê seu número em `module.json` e o mostra nos seus ajustes, propõe a atualização quando
uma versão mais recente é publicada, e verifica cada arquivo contra a impressão digital que `module.json` dá para
ele. O app executa o módulo em uma visualização web, sem enviar nada a lugar nenhum.

O que este módulo sabe fazer: `$FEATURES`. "spacetime": situar pártons e hádrons na zona de interação, que o
TreeLevel mostra no femtômetro.

| arquivo | função |
|---|---|
| `module.json` | versão do módulo e do Pythia, o que ele sabe fazer, a impressão digital de cada arquivo |
| `treelevel-pythia-web.wasm`, `.js` | Pythia $PYTHIA_VERSION e o driver, em WebAssembly |
| `runner.js` | conduz um trabalho do TreeLevel: plano, partes, junção |
| `leptons.pack` | dados do Pythia (xmldoc, tunes, setups) — feixes de léptons |
| `pdfdata.pack` | densidades de pártons — feixes de hádrons, opcional |
| `$SOURCES` | as fontes do Pythia $PYTHIA_VERSION, tal como publicadas em pythia.org |
| `COPYING.pythia8` | a licença do Pythia (GPL v2 ou posterior) |

O TreeLevel 1.3 no iPad baixa seu módulo de
[ipad-pythia-8.318](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia-8.318), cujas impressões
digitais ele fixa: essa página não muda.

**O Pythia 8 e seus autores.** O Pythia 8 é © Torbjörn Sjöstrand e a colaboração Pythia —
[pythia.org](https://pythia.org) — e é distribuído sob a GPL v2 ou posterior. Toda a física deste módulo é deles.
Se você publicar um resultado obtido com ele, cite: C. Bierlich et al., "A comprehensive guide to the physics
and usage of PYTHIA 8.3", *SciPost Phys. Codebases* 8 (2022), [arXiv:2203.11601](https://arxiv.org/abs/2203.11601).
Os outros geradores conduzidos pelo TreeLevel Tools, e seus autores:
[CREDITS.md](https://github.com/gpasa/treelevel-tools/blob/main/CREDITS.md).

Ele continua sendo um programa separado do TreeLevel: o app lhe passa um trabalho e lê de volta o resultado. As
fontes do driver e de `runner.js` estão neste repositório (`Backends/pythia`), na tag `ipad-pythia-module-$MODULE`.
Somas de verificação em `SHA256SUMS.txt`.
