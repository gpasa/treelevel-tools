[TreeLevel](https://treelevel.pasahome.org) の事象生成器を、あなたのマシンで。TreeLevel はローカルフォルダに作業を書き出し、このプログラムがそれを **Pythia 8**、**Herwig 7**、**Sherpa 3**、**WHIZARD 3** または **CalcHEP 3** に渡します — 事象のシャワーとハドロン化、あるいは加速器での衝突全体 — そして結果を HepMC3 で書き戻し、TreeLevel がそれを読み込みます。ネットワークを通るものは何もなく、アカウントもサービスも不要です。iPad では、WebAssembly にコンパイルした Pythia 8 が同じ役割を果たし、[そのリリース](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia)からダウンロードされます。

これらの生成器は **GPL** ライセンスであるため、別に配布しています。このリポジトリは GPL v3 で、TreeLevel はそのコードを一切含みません。

| システム | ダウンロード | 内容 |
|---|---|---|
| **macOS** 13 以降、Apple Silicon と Intel | [TreeLevelTools-0.5.0.dmg](https://github.com/gpasa/treelevel-tools/releases/download/mac-0.5.0/TreeLevelTools-0.5.0.dmg) | Pythia 8、Herwig 7、Sherpa 3、CalcHEP 3、すぐに実行可能 |
| **Windows** 10 と 11 | [x64](https://github.com/gpasa/treelevel-tools/releases/download/win-0.5.1/TreeLevelTools-0.5.1-x64.zip) · [ARM64](https://github.com/gpasa/treelevel-tools/releases/download/win-0.5.1/TreeLevelTools-0.5.1-arm64.zip) | Pythia 8。その他は Docker イメージ経由 |
| **iPad** | TreeLevel の設定から（[リリース](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia)） | WebAssembly 版 Pythia 8 |
| **Docker**、すべてのシステム | `docker pull ghcr.io/gpasa/treelevel-tools:latest` | 五つの生成器すべて、WHIZARD 3 を含む |

**Mac**：`TreeLevel Tools.app` を `/Applications` にドラッグし、一度起動します。すると TreeLevel は「生成」ワークスペースでその生成器を提示します。**Windows**：アーカイブを `%LOCALAPPDATA%\Programs` に展開します。**iPad**：設定の *Pythia 8 モジュール* カードがダウンロードし、各ファイルを照合します。**Docker**：イメージがあれば、TreeLevel Tools はどのモジュールも提供しない生成器をその中で実行します（Mac では、チェックボックス一つですべての作業をそこで実行させられます）。
