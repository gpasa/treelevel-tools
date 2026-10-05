Windows 上の TreeLevel 1.4（引き続き 1.3 も）のためにモンテカルロ生成器を動かすエンジンです。書庫を `%LOCALAPPDATA%\Programs` に展開するだけでインストールできます——インストーラもなく、レジストリにも何も残しません。以前のバージョンを**更新するには**、TreeLevel を閉じ、書庫を同じ場所に展開してファイルを置き換えます。

お使いのマシンに合う書庫を選んでください：Copilot+ PC や ARM タブレットなら `arm64`、それ以外はすべて `x64`。迷ったら、x64 版も ARM でエミュレーションで動きます。

**書庫の内容**：TreeLevel が起動する `treelevel-tools.exe`、各生成器のカードを書き出してそれを動かすエンジン `treelevel-engine.exe`、このアーキテクチャ向けにコンパイルされた Pythia 8 モジュール、`CREDITS.md`。Herwig、Sherpa、WHIZARD、CalcHEP はコンテナイメージを通ります。それには Docker Desktop が必要です：

```
docker pull ghcr.io/gpasa/treelevel-tools:latest
```

ほかに必要なことはありません：TreeLevel がジョブごとに使い捨てのコンテナを自ら作ります。TreeLevel の起動時に Docker Desktop が動いている必要があります。そうすれば、イメージの生成器が「(Docker)」の印付きで現れます。

**エンジンにはウィンドウがありません**。必要になるたびに TreeLevel が起動します。`treelevel-tools.exe` をダブルクリックすると、Windows SmartScreen が認識されないアプリだと警告します——エンジンは署名されていません——。警告を越えると、コンソールが使い方を表示して閉じます。これは正常で、何の影響もありません。

### 変更点

- **フェムトメートル単位の相互作用領域**。TreeLevel 1.4 のために、Pythia ドライバは各パートン相互作用を二つのハドロンの重なりの中に、各ハドロンをそのひもが切れた場所に配置できます（ジョブのキー `spaceTime`：`PartonVertex:setVertex`、`Fragmentation:setVertices`）。各パートンについてはカラーフローと Pythia の状態を、自分の頂点以外の場所で生まれた各粒子についてはその誕生の場所を書き出します——TreeLevel 1.4 の拡大した断面と 3D ビューが描くのはこれです。これは生成器のモデルであり、測定されたものではありません。
- **ビーム衝突領域のずれは一度だけ**。これらの位置があると、Pythia はハドロンを二度ずらしていました。ドライバは今後、一つのベクトルでイベントそのものを配置します。キーがなければ何も変わりません。
- **エンジンが自分にできることを告げます**：`treelevel-tools capabilities` は `spaceTimeGenerators` を告げます（ドライバが「spacetime」と答えるときのネイティブ Pythia と、イメージが告げるもの）。TreeLevel 1.4 は、そこに含まれている場合にのみチェックボックス「相互作用領域での位置」を表示します。
- **TreeLevel 1.3 に対応**：キー `spaceTime` のないジョブは、0.4.0 とまったく同じように動きます。
- **Docker イメージ 0.5 は後に続きます**：それまでは `:latest` はイメージ 0.4.0 で、Herwig、Sherpa、WHIZARD、CalcHEP はこれまでどおりそこで動きます。相互作用領域はこの書庫のネイティブ Pythia を通ります。
- **`mac-0.5.0` と同じエンジン**：同じ Pythia ドライバ（`Backends/pythia/main.cpp`）、同じジョブのキー、書き出す属性も同じです。
