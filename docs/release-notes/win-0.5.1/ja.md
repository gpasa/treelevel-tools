Windows 上の TreeLevel 1.4（引き続き 1.3 も）のためにモンテカルロ生成器を動かすエンジンです。書庫を `%LOCALAPPDATA%\Programs` に展開するだけでインストールできます——インストーラもなく、レジストリにも何も残しません。以前のバージョンを**更新するには**、TreeLevel を閉じ、書庫を同じ場所に展開してファイルを置き換えます。

お使いのマシンに合う書庫を選んでください：Copilot+ PC や ARM タブレットなら `arm64`、それ以外はすべて `x64`。迷ったら、x64 版も ARM でエミュレーションで動きます。

**書庫の内容**：TreeLevel が起動する `treelevel-tools.exe`、各生成器のカードを書き出してそれを動かすエンジン `treelevel-engine.exe`、このアーキテクチャ向けにコンパイルされた Pythia 8 モジュール、`CREDITS.md`。Herwig、Sherpa、WHIZARD、CalcHEP はコンテナイメージを通ります。それには Docker Desktop が必要です：

```
docker pull ghcr.io/gpasa/treelevel-tools:latest
```

ほかに必要なことはありません：TreeLevel がジョブごとに使い捨てのコンテナを自ら作ります。TreeLevel の起動時に Docker Desktop が動いている必要があります。そうすれば、イメージの生成器が「(Docker)」の印付きで現れます。

**エンジンにはウィンドウがありません**。必要になるたびに TreeLevel が起動します。`treelevel-tools.exe` をダブルクリックすると、Windows SmartScreen が認識されないアプリだと警告します——エンジンは署名されていません——。警告を越えると、コンソールが使い方を表示して閉じます。これは正常で、何の影響もありません。

### 変更点

- **ホストがイメージ 0.5.0 を求めます**。イメージは公開済みで、`:latest` がそれを指しています。Windows エンジンはこれまでどおり、まず `ghcr.io/gpasa/treelevel-tools:0.5.0` を、次に `:latest` を探します。イメージ 0.5.0 では、チェックボックス「Tout faire tourner dans l'image Docker」でも相互作用領域が得られます（イメージが `spaceTimeGenerators` を告げます）。
- **Docker でこれを利用するには**：`docker pull ghcr.io/gpasa/treelevel-tools:latest`（または `:0.5.0`）でイメージ 0.4.0 が置き換わります。
- **ほかは何も変わりません**：Pythia ドライバもジョブのキーも `win-0.5.0` と同じです。TreeLevel 1.3 と 1.4 に対応します。
