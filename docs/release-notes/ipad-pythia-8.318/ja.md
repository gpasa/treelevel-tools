TreeLevel Tools の共通ドライバとともに WebAssembly にコンパイルされた Pythia 8 です。iPad の TreeLevel はこのページからファイルごとにダウンロードし、App に固定された指紋で各ファイルを検証します。Web ビューの中で動かし、どこにも何も送信しません。イベントはシャワーとハドロン化を経て出てきて、TreeLevel の「加速器」ソースが iPad でも使えるようになります。

| ファイル | 役割 |
|---|---|
| `treelevel-pythia-web.wasm`、`.js` | Pythia 8.318 とドライバ（WebAssembly） |
| `runner.js` | TreeLevel のジョブを実行する：計画、分割、統合 |
| `leptons.pack` | Pythia のデータ（xmldoc、tunes、setups）— レプトンビーム |
| `pdfdata.pack` | パートン密度 — ハドロンビーム、任意 |
| `pythia8318-sources.tgz` | pythia.org で公開されているままの Pythia 8.318 のソース |
| `COPYING.pythia8` | Pythia のライセンス（GPL v2 以降） |

### Pythia 8 とその作者

Pythia 8 は © Torbjörn Sjöstrand と Pythia コラボレーション——[pythia.org](https://pythia.org)——で、GPL v2 以降のもとで配布されています。このモジュールの物理はすべて彼らのものです。これを使って得た結果を発表するときは、次を引用してください：C. Bierlich et al., 「A comprehensive guide to the physics and usage of PYTHIA 8.3」, *SciPost Phys. Codebases* 8 (2022), [arXiv:2203.11601](https://arxiv.org/abs/2203.11601)。

TreeLevel Tools が操るほかの生成器とその作者：[CREDITS.md](https://github.com/gpasa/treelevel-tools/blob/1.3-dev/CREDITS.md)。モジュールは TreeLevel とは別のプログラムのままです：App はジョブを渡し、結果を読み戻します。ドライバと `runner.js` のソースは、このリポジトリの、このリリースのタグ（`Backends/pythia`）にあります。チェックサムは `SHA256SUMS.txt` にあります。
