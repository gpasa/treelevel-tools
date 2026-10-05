模块版本：**$MODULE** — Pythia **$PYTHIA_VERSION**，与 TreeLevel Tools $MODULE 的通用驱动程序一起编译为 WebAssembly。本页面始终保持同一名称：iPad 上的 TreeLevel（1.4 及更高版本）从这里获取最新版本，从 `module.json` 读取其版本号并显示在设置中，有更新的版本发布时提供更新，并按照 `module.json` 给出的指纹校验每个文件。它在网页视图中运行该模块，不向任何地方发送任何内容。

本模块的功能：`$FEATURES`。“spacetime”：将部分子和强子放置在相互作用区中，TreeLevel 以飞米尺度显示。

| 文件 | 作用 |
|---|---|
| `module.json` | 模块与 Pythia 的版本、模块的功能、每个文件的指纹 |
| `treelevel-pythia-web.wasm`、`.js` | Pythia $PYTHIA_VERSION 与驱动程序，WebAssembly 版本 |
| `runner.js` | 执行 TreeLevel 的任务：规划、分块、合并 |
| `leptons.pack` | Pythia 的数据（xmldoc、tunes、setups）— 轻子束流 |
| `pdfdata.pack` | 部分子密度 — 强子束流，可选 |
| `$SOURCES` | Pythia $PYTHIA_VERSION 的源代码，与 pythia.org 上发布的相同 |
| `COPYING.pythia8` | Pythia 的许可证（GPL v2 或更高版本） |

iPad 上的 TreeLevel 1.3 从 [ipad-pythia-8.318](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia-8.318) 下载其模块，并固定其中文件的指纹：那个页面不会改变。

**Pythia 8 及其作者。** Pythia 8 版权归 © Torbjörn Sjöstrand 与 Pythia 合作组所有 — [pythia.org](https://pythia.org) — 以 GPL v2 或更高版本分发。本模块的全部物理都出自他们之手。如果您发表借助它得到的结果，请引用：C. Bierlich et al., "A comprehensive guide to the physics and usage of PYTHIA 8.3", *SciPost Phys. Codebases* 8 (2022), [arXiv:2203.11601](https://arxiv.org/abs/2203.11601)。TreeLevel Tools 驱动的其他生成器及其作者：[CREDITS.md](https://github.com/gpasa/treelevel-tools/blob/main/CREDITS.md)。

它始终是独立于 TreeLevel 的程序：应用把任务交给它，再读回结果。驱动程序与 `runner.js` 的源代码位于本仓库（`Backends/pythia`）的标签 `ipad-pythia-module-$MODULE` 处。校验和见 `SHA256SUMS.txt`。
