编译为 WebAssembly 的 Pythia 8，附带 TreeLevel Tools 的通用驱动程序。iPad 上的 TreeLevel 从本页面逐个文件下载它，并用固定在 App 中的指纹校验每个文件；它在网页视图中运行，不向任何地方发送任何内容。输出的事件经过簇射和强子化，TreeLevel 的“加速器”来源也因此可在 iPad 上使用。

| 文件 | 作用 |
|---|---|
| `treelevel-pythia-web.wasm`、`.js` | Pythia 8.318 与驱动程序，WebAssembly 版本 |
| `runner.js` | 执行 TreeLevel 的作业：规划、分块、合并 |
| `leptons.pack` | Pythia 的数据（xmldoc、tunes、setups）——轻子束流 |
| `pdfdata.pack` | 部分子密度——强子束流，可选 |
| `pythia8318-sources.tgz` | Pythia 8.318 的源代码，与 pythia.org 上发布的相同 |
| `COPYING.pythia8` | Pythia 的许可证（GPL v2 或更高版本） |

### Pythia 8 及其作者

Pythia 8 © Torbjörn Sjöstrand 与 Pythia 合作组——[pythia.org](https://pythia.org)——以 GPL v2 或更高版本发布。本模块中的全部物理都出自他们。如果您发表借助它得到的结果，请引用：C. Bierlich et al., “A comprehensive guide to the physics and usage of PYTHIA 8.3”, *SciPost Phys. Codebases* 8 (2022), [arXiv:2203.11601](https://arxiv.org/abs/2203.11601)。

TreeLevel Tools 驱动的其他生成器及其作者：[CREDITS.md](https://github.com/gpasa/treelevel-tools/blob/1.3-dev/CREDITS.md)。该模块始终是独立于 TreeLevel 的程序：App 把作业交给它，再读回结果。驱动程序和 `runner.js` 的源代码位于本仓库中本次发布的标签下（`Backends/pythia`）。校验和见 `SHA256SUMS.txt`。
