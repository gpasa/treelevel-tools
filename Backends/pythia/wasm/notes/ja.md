モジュールのバージョン：**$MODULE** — Pythia **$PYTHIA_VERSION**。TreeLevel Tools $MODULE の共通ドライバとともに WebAssembly にコンパイルしたものです。このページは常に同じ名前のままです。iPad 版 TreeLevel（1.4 以降）はここから最新版を取得し、`module.json` からその番号を読んで設定に表示し、より新しい版が公開されると更新を提案し、`module.json` が示すフィンガープリントと各ファイルを照合します。モジュールは Web ビューの中で動作し、どこにも何も送信しません。

このモジュールにできること：`$FEATURES`。「spacetime」：パートンとハドロンを相互作用領域に配置すること。TreeLevel はこれをフェムトメートルの尺度で表示します。

| ファイル | 役割 |
|---|---|
| `module.json` | モジュールと Pythia のバージョン、モジュールにできること、各ファイルのフィンガープリント |
| `treelevel-pythia-web.wasm`、`.js` | Pythia $PYTHIA_VERSION とドライバ（WebAssembly） |
| `runner.js` | TreeLevel の作業を実行する：計画、分割、統合 |
| `leptons.pack` | Pythia のデータ（xmldoc、tunes、setups）— レプトンビーム |
| `pdfdata.pack` | パートン密度 — ハドロンビーム、任意 |
| `$SOURCES` | pythia.org で公開されているままの Pythia $PYTHIA_VERSION のソース |
| `COPYING.pythia8` | Pythia のライセンス（GPL v2 以降） |

iPad 版 TreeLevel 1.3 は [ipad-pythia-8.318](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia-8.318) からモジュールをダウンロードし、そのフィンガープリントを固定しています。そのページは変わりません。

**Pythia 8 とその作者。** Pythia 8 は © Torbjörn Sjöstrand と Pythia コラボレーション — [pythia.org](https://pythia.org) — のものであり、GPL v2 以降で配布されています。このモジュールの物理はすべて彼らのものです。これを使って得た結果を発表する場合は、次を引用してください：C. Bierlich et al., "A comprehensive guide to the physics and usage of PYTHIA 8.3", *SciPost Phys. Codebases* 8 (2022), [arXiv:2203.11601](https://arxiv.org/abs/2203.11601)。TreeLevel Tools が動かすその他の生成器とその作者：[CREDITS.md](https://github.com/gpasa/treelevel-tools/blob/main/CREDITS.md)。

これは TreeLevel とは別のプログラムのままです。アプリは作業を渡し、結果を読み戻します。ドライバと `runner.js` のソースはこのリポジトリ（`Backends/pythia`）のタグ `ipad-pythia-module-$MODULE` にあります。チェックサムは `SHA256SUMS.txt` にあります。
