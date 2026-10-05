# TreeLevel Tools

🌐 **[This page in your language](https://treelevel.pasahome.org/outils/)** — the TreeLevel site opens it in the language of your browser. Or unfold yours below: [Français](#lang-fr) · [Deutsch](#lang-de) · [Italiano](#lang-it) · [Español](#lang-es) · [Português (Brasil)](#lang-pt-br) · [Русский](#lang-ru) · [简体中文](#lang-zh-hans) · [日本語](#lang-ja) · [한국어](#lang-ko) · [हिन्दी](#lang-hi).

[Installation](#installation) · [The container](#the-other-way-the-container) · [Links and credits](#links-and-credits) · [Contents](#contents)

The event generators of [TreeLevel](https://treelevel.pasahome.org), on your machine. TreeLevel writes a job into a
local folder; this program hands it to **Pythia 8**, **Herwig 7**, **Sherpa 3**, **WHIZARD 3** or **CalcHEP 3** —
shower and hadronisation of its events, or whole collisions of a machine — and writes the result back in HepMC3,
which TreeLevel reads. Nothing goes over the network, no account, no service. On iPad, Pythia 8 compiled to
WebAssembly plays the same part, downloaded from [its release](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia).

It is distributed separately because these generators are under the **GPL**: this repository is GPL v3, and
TreeLevel contains none of their code.

| system | download | what it contains |
|---|---|---|
| **macOS** 13 or later, Apple Silicon and Intel | [TreeLevelTools-0.5.0.dmg](https://github.com/gpasa/treelevel-tools/releases/download/mac-0.5.0/TreeLevelTools-0.5.0.dmg) | Pythia 8, Herwig 7, Sherpa 3 and CalcHEP 3, ready to run |
| **Windows** 10 and 11 | [x64](https://github.com/gpasa/treelevel-tools/releases/download/win-0.5.1/TreeLevelTools-0.5.1-x64.zip) · [ARM64](https://github.com/gpasa/treelevel-tools/releases/download/win-0.5.1/TreeLevelTools-0.5.1-arm64.zip) | Pythia 8; the others through the Docker image |
| **iPad** | from TreeLevel's settings ([the release](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia)) | Pythia 8 in WebAssembly |
| **Docker**, any system | `docker pull ghcr.io/gpasa/treelevel-tools:latest` | the five generators, WHIZARD 3 included |

**Mac**: drag `TreeLevel Tools.app` into `/Applications` and launch it once; TreeLevel then offers its generators
in the Generation workspace. **Windows**: unfold the archive into `%LOCALAPPDATA%\Programs`. **iPad**: the
*Pythia 8 module* card of the settings downloads it and checks every file. **Docker**: with the image present,
TreeLevel Tools runs in it the generators that no module provides (on the Mac, a box makes it run every job).

<a name="lang-fr"></a>
<details>
<summary><b>Français</b></summary>

Les générateurs d'événements de [TreeLevel](https://treelevel.pasahome.org), sur votre machine. TreeLevel écrit un
travail dans un dossier local ; ce programme le confie à **Pythia 8**, **Herwig 7**, **Sherpa 3**, **WHIZARD 3** ou
**CalcHEP 3** — gerbe et hadronisation de ses événements, ou collisions entières d'une machine — et réécrit le
résultat en HepMC3, que TreeLevel relit. Rien ne transite par le réseau, aucun compte, aucun service. Sur iPad,
Pythia 8 compilé en WebAssembly joue le même rôle, téléchargé depuis
[sa release](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia).

Il est distribué séparément parce que ces générateurs sont sous licence **GPL** : ce dépôt est GPL v3, et TreeLevel
ne contient aucun de leur code.

| système | télécharger | ce qu'il contient |
|---|---|---|
| **macOS** 13 ou plus récent, Apple Silicon et Intel | [TreeLevelTools-0.5.0.dmg](https://github.com/gpasa/treelevel-tools/releases/download/mac-0.5.0/TreeLevelTools-0.5.0.dmg) | Pythia 8, Herwig 7, Sherpa 3 et CalcHEP 3, prêts à tourner |
| **Windows** 10 et 11 | [x64](https://github.com/gpasa/treelevel-tools/releases/download/win-0.5.1/TreeLevelTools-0.5.1-x64.zip) · [ARM64](https://github.com/gpasa/treelevel-tools/releases/download/win-0.5.1/TreeLevelTools-0.5.1-arm64.zip) | Pythia 8 ; les autres par l'image Docker |
| **iPad** | depuis les réglages de TreeLevel ([la release](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia)) | Pythia 8 en WebAssembly |
| **Docker**, tous systèmes | `docker pull ghcr.io/gpasa/treelevel-tools:latest` | les cinq générateurs, WHIZARD 3 compris |

**Mac** : glisser `TreeLevel Tools.app` dans `/Applications` et la lancer une fois ; TreeLevel propose alors ses
générateurs dans l'espace Génération. **Windows** : déplier l'archive dans `%LOCALAPPDATA%\Programs`. **iPad** : la
carte *Module Pythia 8* des réglages le télécharge et vérifie chaque fichier. **Docker** : l'image présente,
TreeLevel Tools y fait tourner les générateurs qu'aucun module n'offre (au Mac, une case lui confie tous les
travaux).

</details>

<a name="lang-de"></a>
<details>
<summary><b>Deutsch</b></summary>

Die Ereignisgeneratoren von [TreeLevel](https://treelevel.pasahome.org), auf Ihrem Rechner. TreeLevel schreibt einen
Auftrag in einen lokalen Ordner; dieses Programm übergibt ihn an **Pythia 8**, **Herwig 7**, **Sherpa 3**,
**WHIZARD 3** oder **CalcHEP 3** — Schauer und Hadronisierung seiner Ereignisse oder ganze Kollisionen einer
Maschine — und schreibt das Ergebnis in HepMC3 zurück, das TreeLevel wieder einliest. Nichts geht über das Netz,
kein Konto, kein Dienst. Auf dem iPad übernimmt Pythia 8, nach WebAssembly kompiliert, dieselbe Rolle,
heruntergeladen von [seinem Release](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia).

Es wird getrennt verbreitet, weil diese Generatoren unter der **GPL** stehen: Dieses Repository ist GPL v3, und
TreeLevel enthält nichts von ihrem Code.

| System | Download | Inhalt |
|---|---|---|
| **macOS** 13 oder neuer, Apple Silicon und Intel | [TreeLevelTools-0.5.0.dmg](https://github.com/gpasa/treelevel-tools/releases/download/mac-0.5.0/TreeLevelTools-0.5.0.dmg) | Pythia 8, Herwig 7, Sherpa 3 und CalcHEP 3, sofort lauffähig |
| **Windows** 10 und 11 | [x64](https://github.com/gpasa/treelevel-tools/releases/download/win-0.5.1/TreeLevelTools-0.5.1-x64.zip) · [ARM64](https://github.com/gpasa/treelevel-tools/releases/download/win-0.5.1/TreeLevelTools-0.5.1-arm64.zip) | Pythia 8; die anderen über das Docker-Image |
| **iPad** | aus den Einstellungen von TreeLevel ([das Release](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia)) | Pythia 8 in WebAssembly |
| **Docker**, jedes System | `docker pull ghcr.io/gpasa/treelevel-tools:latest` | die fünf Generatoren, WHIZARD 3 inbegriffen |

**Mac**: `TreeLevel Tools.app` nach `/Applications` ziehen und einmal starten; TreeLevel bietet seine Generatoren
dann im Arbeitsbereich Erzeugung an. **Windows**: das Archiv nach `%LOCALAPPDATA%\Programs` entpacken. **iPad**: Die
Karte *Pythia-8-Modul* der Einstellungen lädt es herunter und prüft jede Datei. **Docker**: Ist das Image vorhanden,
führt TreeLevel Tools darin die Generatoren aus, die kein Modul bietet (auf dem Mac übergibt ihm ein Kästchen alle
Aufträge).

</details>

<a name="lang-it"></a>
<details>
<summary><b>Italiano</b></summary>

I generatori di eventi di [TreeLevel](https://treelevel.pasahome.org), sulla vostra macchina. TreeLevel scrive un
lavoro in una cartella locale; questo programma lo affida a **Pythia 8**, **Herwig 7**, **Sherpa 3**, **WHIZARD 3** o
**CalcHEP 3** — sciame e adronizzazione dei suoi eventi, o collisioni intere di una macchina — e riscrive il
risultato in HepMC3, che TreeLevel rilegge. Nulla passa per la rete, nessun account, nessun servizio. Su iPad,
Pythia 8 compilato in WebAssembly svolge lo stesso ruolo, scaricato dalla
[sua release](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia).

È distribuito separatamente perché questi generatori sono sotto licenza **GPL**: questo repository è GPL v3, e
TreeLevel non contiene nulla del loro codice.

| sistema | scaricare | cosa contiene |
|---|---|---|
| **macOS** 13 o successivo, Apple Silicon e Intel | [TreeLevelTools-0.5.0.dmg](https://github.com/gpasa/treelevel-tools/releases/download/mac-0.5.0/TreeLevelTools-0.5.0.dmg) | Pythia 8, Herwig 7, Sherpa 3 e CalcHEP 3, pronti all'uso |
| **Windows** 10 e 11 | [x64](https://github.com/gpasa/treelevel-tools/releases/download/win-0.5.1/TreeLevelTools-0.5.1-x64.zip) · [ARM64](https://github.com/gpasa/treelevel-tools/releases/download/win-0.5.1/TreeLevelTools-0.5.1-arm64.zip) | Pythia 8; gli altri tramite l'immagine Docker |
| **iPad** | dalle impostazioni di TreeLevel ([la release](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia)) | Pythia 8 in WebAssembly |
| **Docker**, qualsiasi sistema | `docker pull ghcr.io/gpasa/treelevel-tools:latest` | i cinque generatori, WHIZARD 3 compreso |

**Mac**: trascinare `TreeLevel Tools.app` in `/Applications` e avviarla una volta; TreeLevel propone allora i suoi
generatori nello spazio Generazione. **Windows**: estrarre l'archivio in `%LOCALAPPDATA%\Programs`. **iPad**: la
scheda *Modulo Pythia 8* delle impostazioni lo scarica e verifica ogni file. **Docker**: con l'immagine presente,
TreeLevel Tools vi esegue i generatori che nessun modulo offre (sul Mac, una casella gli affida tutti i lavori).

</details>

<a name="lang-es"></a>
<details>
<summary><b>Español</b></summary>

Los generadores de sucesos de [TreeLevel](https://treelevel.pasahome.org), en su máquina. TreeLevel escribe un
trabajo en una carpeta local; este programa lo confía a **Pythia 8**, **Herwig 7**, **Sherpa 3**, **WHIZARD 3** o
**CalcHEP 3** — cascada y hadronización de sus sucesos, o colisiones enteras de una máquina — y vuelve a escribir el
resultado en HepMC3, que TreeLevel relee. Nada pasa por la red, ninguna cuenta, ningún servicio. En iPad, Pythia 8
compilado a WebAssembly desempeña el mismo papel, descargado desde
[su release](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia).

Se distribuye por separado porque estos generadores están bajo licencia **GPL**: este repositorio es GPL v3, y
TreeLevel no contiene nada de su código.

| sistema | descargar | lo que contiene |
|---|---|---|
| **macOS** 13 o posterior, Apple Silicon e Intel | [TreeLevelTools-0.5.0.dmg](https://github.com/gpasa/treelevel-tools/releases/download/mac-0.5.0/TreeLevelTools-0.5.0.dmg) | Pythia 8, Herwig 7, Sherpa 3 y CalcHEP 3, listos para funcionar |
| **Windows** 10 y 11 | [x64](https://github.com/gpasa/treelevel-tools/releases/download/win-0.5.1/TreeLevelTools-0.5.1-x64.zip) · [ARM64](https://github.com/gpasa/treelevel-tools/releases/download/win-0.5.1/TreeLevelTools-0.5.1-arm64.zip) | Pythia 8; los demás mediante la imagen Docker |
| **iPad** | desde los ajustes de TreeLevel ([la release](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia)) | Pythia 8 en WebAssembly |
| **Docker**, cualquier sistema | `docker pull ghcr.io/gpasa/treelevel-tools:latest` | los cinco generadores, WHIZARD 3 incluido |

**Mac**: arrastrar `TreeLevel Tools.app` a `/Applications` y abrirla una vez; TreeLevel ofrece entonces sus
generadores en el espacio Generación. **Windows**: descomprimir el archivo en `%LOCALAPPDATA%\Programs`. **iPad**: la
tarjeta *Módulo Pythia 8* de los ajustes lo descarga y comprueba cada archivo. **Docker**: con la imagen presente,
TreeLevel Tools ejecuta en ella los generadores que ningún módulo ofrece (en el Mac, una casilla le confía todos los
trabajos).

</details>

<a name="lang-pt-br"></a>
<details>
<summary><b>Português (Brasil)</b></summary>

Os geradores de eventos do [TreeLevel](https://treelevel.pasahome.org), na sua máquina. O TreeLevel escreve um
trabalho em uma pasta local; este programa o entrega ao **Pythia 8**, **Herwig 7**, **Sherpa 3**, **WHIZARD 3** ou
**CalcHEP 3** — chuveiro e hadronização de seus eventos, ou colisões inteiras de uma máquina — e grava o resultado
de volta em HepMC3, que o TreeLevel lê. Nada passa pela rede, nenhuma conta, nenhum serviço. No iPad, o Pythia 8
compilado em WebAssembly desempenha o mesmo papel, baixado de [sua release](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia).

Ele é distribuído separadamente porque esses geradores estão sob a licença **GPL**: este repositório é GPL v3, e o
TreeLevel não contém nenhum código deles.

| sistema | baixar | o que contém |
|---|---|---|
| **macOS** 13 ou posterior, Apple Silicon e Intel | [TreeLevelTools-0.5.0.dmg](https://github.com/gpasa/treelevel-tools/releases/download/mac-0.5.0/TreeLevelTools-0.5.0.dmg) | Pythia 8, Herwig 7, Sherpa 3 e CalcHEP 3, prontos para rodar |
| **Windows** 10 e 11 | [x64](https://github.com/gpasa/treelevel-tools/releases/download/win-0.5.1/TreeLevelTools-0.5.1-x64.zip) · [ARM64](https://github.com/gpasa/treelevel-tools/releases/download/win-0.5.1/TreeLevelTools-0.5.1-arm64.zip) | Pythia 8; os outros pela imagem Docker |
| **iPad** | pelos ajustes do TreeLevel ([a release](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia)) | Pythia 8 em WebAssembly |
| **Docker**, qualquer sistema | `docker pull ghcr.io/gpasa/treelevel-tools:latest` | os cinco geradores, WHIZARD 3 incluído |

**Mac**: arraste `TreeLevel Tools.app` para `/Applications` e abra-o uma vez; o TreeLevel passa então a oferecer
seus geradores no espaço Geração. **Windows**: descompacte o arquivo em `%LOCALAPPDATA%\Programs`. **iPad**: o
cartão *Módulo Pythia 8* dos ajustes o baixa e verifica cada arquivo. **Docker**: com a imagem presente, o
TreeLevel Tools executa nela os geradores que nenhum módulo fornece (no Mac, uma caixa de seleção faz com que ela
execute todos os trabalhos).

</details>

<a name="lang-ru"></a>
<details>
<summary><b>Русский</b></summary>

Генераторы событий [TreeLevel](https://treelevel.pasahome.org) на вашем компьютере. TreeLevel записывает задание в
локальную папку; эта программа передаёт его **Pythia 8**, **Herwig 7**, **Sherpa 3**, **WHIZARD 3** или
**CalcHEP 3** — ливень и адронизация его событий или целые столкновения на ускорителе — и записывает результат
обратно в HepMC3, который TreeLevel читает. Ничего не передаётся по сети, никакой учётной записи, никакого сервиса.
На iPad ту же роль играет Pythia 8, скомпилированная в WebAssembly и загружаемая из [её релиза](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia).

Программа распространяется отдельно, потому что эти генераторы выпущены под лицензией **GPL**: этот репозиторий —
GPL v3, а TreeLevel не содержит их кода.

| система | загрузка | что содержит |
|---|---|---|
| **macOS** 13 или новее, Apple Silicon и Intel | [TreeLevelTools-0.5.0.dmg](https://github.com/gpasa/treelevel-tools/releases/download/mac-0.5.0/TreeLevelTools-0.5.0.dmg) | Pythia 8, Herwig 7, Sherpa 3 и CalcHEP 3, готовые к работе |
| **Windows** 10 и 11 | [x64](https://github.com/gpasa/treelevel-tools/releases/download/win-0.5.1/TreeLevelTools-0.5.1-x64.zip) · [ARM64](https://github.com/gpasa/treelevel-tools/releases/download/win-0.5.1/TreeLevelTools-0.5.1-arm64.zip) | Pythia 8; остальные — через образ Docker |
| **iPad** | из настроек TreeLevel ([релиз](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia)) | Pythia 8 в WebAssembly |
| **Docker**, любая система | `docker pull ghcr.io/gpasa/treelevel-tools:latest` | все пять генераторов, включая WHIZARD 3 |

**Mac**: перетащите `TreeLevel Tools.app` в `/Applications` и запустите один раз; после этого TreeLevel предлагает
эти генераторы в разделе «Генерация». **Windows**: распакуйте архив в `%LOCALAPPDATA%\Programs`. **iPad**: карточка
*Модуль Pythia 8* в настройках загружает его и проверяет каждый файл. **Docker**: если образ установлен,
TreeLevel Tools запускает в нём генераторы, которых не даёт ни один модуль (на Mac флажок поручает ему все
задания).

</details>

<a name="lang-zh-hans"></a>
<details>
<summary><b>简体中文</b></summary>

[TreeLevel](https://treelevel.pasahome.org) 的事件生成器，在您自己的机器上运行。TreeLevel 把一个任务写入本地文件夹；本程序将其交给 **Pythia 8**、**Herwig 7**、**Sherpa 3**、**WHIZARD 3** 或 **CalcHEP 3** — 对其事件进行簇射与强子化，或生成加速器的完整碰撞 — 再以 HepMC3 格式写回结果，由 TreeLevel 读取。不经过网络，无需账户，没有任何服务。在 iPad 上，由编译为 WebAssembly 的 Pythia 8 承担同样的角色，从[其发布页](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia)下载。

它之所以单独分发，是因为这些生成器采用 **GPL** 许可：本仓库为 GPL v3，TreeLevel 不包含它们的任何代码。

| 系统 | 下载 | 包含内容 |
|---|---|---|
| **macOS** 13 或更高版本，Apple Silicon 与 Intel | [TreeLevelTools-0.5.0.dmg](https://github.com/gpasa/treelevel-tools/releases/download/mac-0.5.0/TreeLevelTools-0.5.0.dmg) | Pythia 8、Herwig 7、Sherpa 3 与 CalcHEP 3，可直接运行 |
| **Windows** 10 与 11 | [x64](https://github.com/gpasa/treelevel-tools/releases/download/win-0.5.1/TreeLevelTools-0.5.1-x64.zip) · [ARM64](https://github.com/gpasa/treelevel-tools/releases/download/win-0.5.1/TreeLevelTools-0.5.1-arm64.zip) | Pythia 8；其他生成器通过 Docker 镜像 |
| **iPad** | 在 TreeLevel 的设置中（[发布页](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia)） | WebAssembly 版 Pythia 8 |
| **Docker**，任何系统 | `docker pull ghcr.io/gpasa/treelevel-tools:latest` | 全部五个生成器，包括 WHIZARD 3 |

**Mac**：将 `TreeLevel Tools.app` 拖入 `/Applications` 并启动一次；之后 TreeLevel 会在“生成”工作区中提供这些生成器。**Windows**：将压缩包解压到 `%LOCALAPPDATA%\Programs`。**iPad**：设置中的 *Pythia 8 模块* 卡片负责下载并校验每个文件。**Docker**：镜像存在时，TreeLevel Tools 在其中运行没有任何模块提供的生成器（在 Mac 上，勾选一个复选框即可将所有任务交给镜像）。

</details>

<a name="lang-ja"></a>
<details>
<summary><b>日本語</b></summary>

[TreeLevel](https://treelevel.pasahome.org) の事象生成器を、あなたのマシンで。TreeLevel はローカルフォルダに作業を書き出し、このプログラムがそれを **Pythia 8**、**Herwig 7**、**Sherpa 3**、**WHIZARD 3** または **CalcHEP 3** に渡します — 事象のシャワーとハドロン化、あるいは加速器での衝突全体 — そして結果を HepMC3 で書き戻し、TreeLevel がそれを読み込みます。ネットワークを通るものは何もなく、アカウントもサービスも不要です。iPad では、WebAssembly にコンパイルした Pythia 8 が同じ役割を果たし、[そのリリース](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia)からダウンロードされます。

これらの生成器は **GPL** ライセンスであるため、別に配布しています。このリポジトリは GPL v3 で、TreeLevel はそのコードを一切含みません。

| システム | ダウンロード | 内容 |
|---|---|---|
| **macOS** 13 以降、Apple Silicon と Intel | [TreeLevelTools-0.5.0.dmg](https://github.com/gpasa/treelevel-tools/releases/download/mac-0.5.0/TreeLevelTools-0.5.0.dmg) | Pythia 8、Herwig 7、Sherpa 3、CalcHEP 3、すぐに実行可能 |
| **Windows** 10 と 11 | [x64](https://github.com/gpasa/treelevel-tools/releases/download/win-0.5.1/TreeLevelTools-0.5.1-x64.zip) · [ARM64](https://github.com/gpasa/treelevel-tools/releases/download/win-0.5.1/TreeLevelTools-0.5.1-arm64.zip) | Pythia 8。その他は Docker イメージ経由 |
| **iPad** | TreeLevel の設定から（[リリース](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia)） | WebAssembly 版 Pythia 8 |
| **Docker**、すべてのシステム | `docker pull ghcr.io/gpasa/treelevel-tools:latest` | 五つの生成器すべて、WHIZARD 3 を含む |

**Mac**：`TreeLevel Tools.app` を `/Applications` にドラッグし、一度起動します。すると TreeLevel は「生成」ワークスペースでその生成器を提示します。**Windows**：アーカイブを `%LOCALAPPDATA%\Programs` に展開します。**iPad**：設定の *Pythia 8 モジュール* カードがダウンロードし、各ファイルを照合します。**Docker**：イメージがあれば、TreeLevel Tools はどのモジュールも提供しない生成器をその中で実行します（Mac では、チェックボックス一つですべての作業をそこで実行させられます）。

</details>

<a name="lang-ko"></a>
<details>
<summary><b>한국어</b></summary>

[TreeLevel](https://treelevel.pasahome.org)의 사건 생성기를 여러분의 컴퓨터에서. TreeLevel이 로컬 폴더에 작업을 기록하면, 이 프로그램이 그것을 **Pythia 8**, **Herwig 7**, **Sherpa 3**, **WHIZARD 3** 또는 **CalcHEP 3**에 맡깁니다 — 사건의 샤워와 하드론화, 또는 가속기의 충돌 전체 — 그리고 결과를 HepMC3로 다시 기록하며, TreeLevel이 이를 읽습니다. 네트워크를 거치는 것은 없고, 계정도 서비스도 없습니다. iPad에서는 WebAssembly로 컴파일한 Pythia 8이 같은 역할을 하며, [해당 릴리스](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia)에서 내려받습니다.

이 생성기들이 **GPL** 라이선스이므로 따로 배포합니다. 이 저장소는 GPL v3이며, TreeLevel에는 그 코드가 전혀 들어 있지 않습니다.

| 시스템 | 다운로드 | 포함 내용 |
|---|---|---|
| **macOS** 13 이상, Apple Silicon 및 Intel | [TreeLevelTools-0.5.0.dmg](https://github.com/gpasa/treelevel-tools/releases/download/mac-0.5.0/TreeLevelTools-0.5.0.dmg) | Pythia 8, Herwig 7, Sherpa 3, CalcHEP 3, 바로 실행 가능 |
| **Windows** 10 및 11 | [x64](https://github.com/gpasa/treelevel-tools/releases/download/win-0.5.1/TreeLevelTools-0.5.1-x64.zip) · [ARM64](https://github.com/gpasa/treelevel-tools/releases/download/win-0.5.1/TreeLevelTools-0.5.1-arm64.zip) | Pythia 8; 나머지는 Docker 이미지로 |
| **iPad** | TreeLevel 설정에서([릴리스](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia)) | WebAssembly용 Pythia 8 |
| **Docker**, 모든 시스템 | `docker pull ghcr.io/gpasa/treelevel-tools:latest` | 생성기 다섯 개 전부, WHIZARD 3 포함 |

**Mac**: `TreeLevel Tools.app`을 `/Applications`로 끌어다 놓고 한 번 실행합니다. 그러면 TreeLevel이 생성 작업 공간에서 그 생성기들을 제공합니다. **Windows**: 압축 파일을 `%LOCALAPPDATA%\Programs`에 풉니다. **iPad**: 설정의 *Pythia 8 모듈* 카드가 이를 내려받고 각 파일을 검증합니다. **Docker**: 이미지가 있으면 TreeLevel Tools는 어떤 모듈도 제공하지 않는 생성기를 그 안에서 실행합니다(Mac에서는 체크상자 하나로 모든 작업을 이미지에 맡길 수 있습니다).

</details>

<a name="lang-hi"></a>
<details>
<summary><b>हिन्दी</b></summary>

[TreeLevel](https://treelevel.pasahome.org) के घटना जनक, आपके कंप्यूटर पर। TreeLevel एक कार्य को स्थानीय फ़ोल्डर
में लिखता है; यह प्रोग्राम उसे **Pythia 8**, **Herwig 7**, **Sherpa 3**, **WHIZARD 3** या **CalcHEP 3** को सौंपता
है — उसकी घटनाओं का शावर और हैड्रॉनीकरण, या किसी त्वरक की पूरी टक्करें — और परिणाम को HepMC3 में वापस लिखता है,
जिसे TreeLevel पढ़ता है। नेटवर्क पर कुछ नहीं जाता, न कोई खाता, न कोई सेवा। iPad पर WebAssembly में संकलित Pythia 8
यही भूमिका निभाता है, जो [उसकी रिलीज़](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia) से डाउनलोड होता है।

यह अलग से वितरित किया जाता है क्योंकि ये जनक **GPL** लाइसेंस के अंतर्गत हैं: यह रिपॉज़िटरी GPL v3 है, और
TreeLevel में इनका कोई कोड नहीं है।

| सिस्टम | डाउनलोड | इसमें क्या है |
|---|---|---|
| **macOS** 13 या उसके बाद का, Apple Silicon और Intel | [TreeLevelTools-0.5.0.dmg](https://github.com/gpasa/treelevel-tools/releases/download/mac-0.5.0/TreeLevelTools-0.5.0.dmg) | Pythia 8, Herwig 7, Sherpa 3 और CalcHEP 3, चलने के लिए तैयार |
| **Windows** 10 और 11 | [x64](https://github.com/gpasa/treelevel-tools/releases/download/win-0.5.1/TreeLevelTools-0.5.1-x64.zip) · [ARM64](https://github.com/gpasa/treelevel-tools/releases/download/win-0.5.1/TreeLevelTools-0.5.1-arm64.zip) | Pythia 8; बाकी Docker इमेज के माध्यम से |
| **iPad** | TreeLevel की सेटिंग्स से ([रिलीज़](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia)) | WebAssembly में Pythia 8 |
| **Docker**, कोई भी सिस्टम | `docker pull ghcr.io/gpasa/treelevel-tools:latest` | पाँचों जनक, WHIZARD 3 सहित |

**Mac**: `TreeLevel Tools.app` को `/Applications` में खींचें और उसे एक बार खोलें; फिर TreeLevel जनन क्षेत्र में
इसके जनक प्रस्तुत करता है। **Windows**: आर्काइव को `%LOCALAPPDATA%\Programs` में निकालें। **iPad**: सेटिंग्स का
*Pythia 8 मॉड्यूल* कार्ड उसे डाउनलोड करता है और हर फ़ाइल जाँचता है। **Docker**: इमेज मौजूद होने पर, TreeLevel Tools
उसमें वे जनक चलाता है जो कोई मॉड्यूल नहीं देता (Mac पर, एक चेकबॉक्स उसे सारे कार्य सौंप देता है)।

</details>

## Contents

- [Links and credits](#links-and-credits) — [the generators](#the-generators), [what they bundle](#what-they-bundle),
  [the libraries](#the-libraries), [the formats](#the-formats), [the tools](#the-tools-that-build-and-run-them)
- [What it does](#what-it-does)
- [Where the executables live](#where-the-executables-live)
- [Installation](#installation) — [the other way: the container](#the-other-way-the-container)
- [On the command line](#on-the-command-line)
- [Building the modules](#building-the-modules) — [the Pythia driver](#building-the-pythia-driver)
- [Building the Herwig 7 module](#building-the-herwig-7-module)
- [Building the Sherpa, WHIZARD and CalcHEP modules](#building-the-sherpa-whizard-and-calchep-modules) —
  [what each one expects](#what-each-one-expects)
- [Publishing a version](#publishing-a-version)
- [Licence](#licence)
- [Windows](#windows)

## Links and credits

TreeLevel Tools only drives these programs: it hands them a job and reads back what they return. The physics —
showers, hadronisation, matrix elements, integration — is entirely theirs, the fruit of decades of work by their
authors. They are distributed here as they are, under their own licences, with their sources. When you publish a
result obtained with one of them, cite it: that is what its authors ask, and it is what lets them carry on.

### The generators

| program | authors | site | licence | to cite |
|---|---|---|---|---|
| **Pythia 8** | © Torbjörn Sjöstrand and the Pythia collaboration | [pythia.org](https://pythia.org) | GPL v2 or later | C. Bierlich et al., "A comprehensive guide to the physics and usage of PYTHIA 8.3", *SciPost Phys. Codebases* 8 (2022), [arXiv:2203.11601](https://arxiv.org/abs/2203.11601) |
| **Herwig 7** | © the Herwig collaboration | [herwig.hepforge.org](https://herwig.hepforge.org) | GPL v3 | J. Bellm et al., "Herwig 7.0 / Herwig++ 3.0 release note", *Eur. Phys. J. C* 76 (2016) 196, [arXiv:1512.01178](https://arxiv.org/abs/1512.01178) |
| **Sherpa 3** | © the Sherpa authors (SHERPA-MC Authors) | [sherpa-team.gitlab.io](https://sherpa-team.gitlab.io) | GPL v3 or later | E. Bothmann et al., "Event generation with Sherpa 3", [arXiv:2410.22148](https://arxiv.org/abs/2410.22148) |
| **WHIZARD 3** | © 1999–2025 Wolfgang Kilian, Thorsten Ohl, Jürgen Reuter and their contributors | [whizard.hepforge.org](https://whizard.hepforge.org) | GPL v2 or later | W. Kilian, T. Ohl, J. Reuter, "WHIZARD: Simulating Multi-Particle Processes at LHC and ILC", *Eur. Phys. J. C* 71 (2011) 1742, [arXiv:0708.4233](https://arxiv.org/abs/0708.4233) |
| **CalcHEP 3** | Alexander Pukhov, Alexander Belyaev, Neil Christensen, with code from the CompHEP group | [theory.sinp.msu.ru/~pukhov/calchep.html](https://theory.sinp.msu.ru/~pukhov/calchep.html) | GPL v3 | A. Belyaev, N. Christensen, A. Pukhov, "CalcHEP 3.4 for collider physics within and beyond the Standard Model", *Comput. Phys. Commun.* 184 (2013) 1729, [arXiv:1207.6082](https://arxiv.org/abs/1207.6082) |

### What they bundle

| component | in | authors | site | to cite |
|---|---|---|---|---|
| **O'Mega** (optimised amplitudes) | WHIZARD | Mauro Moretti, Thorsten Ohl, Jürgen Reuter | [whizard.hepforge.org](https://whizard.hepforge.org) | M. Moretti, T. Ohl, J. Reuter, "O'Mega: An Optimizing Matrix Element Generator", [arXiv:hep-ph/0102195](https://arxiv.org/abs/hep-ph/0102195) |
| **CompHEP** (from which CalcHEP descends) | CalcHEP | E. Boos, V. Bunichev, M. Dubinin, L. Dudko, V. Ilyin, A. Kryukov, V. Edneral, V. Savrin, A. Semenov, A. Sherstnev | [comphep.sinp.msu.ru](https://comphep.sinp.msu.ru) | E. Boos et al., "CompHEP 4.4", *Nucl. Instrum. Meth. A* 534 (2004) 250, [arXiv:hep-ph/0403113](https://arxiv.org/abs/hep-ph/0403113) |
| **StdHEP / mcfio** (event formats) | WHIZARD | Fermilab | [cd-docdb.fnal.gov](https://cd-docdb.fnal.gov) | — |

### The libraries

| library | authors | site | licence | to cite |
|---|---|---|---|---|
| **ThePEG** (the foundation of Herwig) | © the Herwig collaboration | [herwig.hepforge.org](https://herwig.hepforge.org) | GPL v3 | see Herwig 7 above |
| **LHAPDF 6** (parton densities) | Andy Buckley, Mike Whalley et al. | [lhapdf.hepforge.org](https://lhapdf.hepforge.org) | GPL v3 | A. Buckley et al., "LHAPDF6: parton density access in the LHC precision era", *Eur. Phys. J. C* 75 (2015) 132, [arXiv:1412.7420](https://arxiv.org/abs/1412.7420) |
| **HepMC3** (event format) | the HepMC collaboration | [hepmc.web.cern.ch](http://hepmc.web.cern.ch/hepmc/) | GPL v3 | A. Buckley et al., "The HepMC3 event record library for Monte Carlo event generators", *Comput. Phys. Commun.* 260 (2021) 107310, [arXiv:1912.08005](https://arxiv.org/abs/1912.08005) |
| **FastJet** (jet algorithms) | Matteo Cacciari, Gavin P. Salam, Grégory Soyez | [fastjet.fr](https://fastjet.fr) | GPL v2 or later | M. Cacciari, G. P. Salam, G. Soyez, "FastJet user manual", *Eur. Phys. J. C* 72 (2012) 1896, [arXiv:1111.6097](https://arxiv.org/abs/1111.6097) |
| **GSL** (numerical computing) | the GNU Scientific Library and its contributors | [gnu.org/software/gsl](https://www.gnu.org/software/gsl/) | GPL v3 | M. Galassi et al., *GNU Scientific Library Reference Manual* |

### The formats

| format | to cite |
|---|---|
| **Les Houches** (parton-level events, between TreeLevel and the generators) | J. Alwall et al., "A standard format for Les Houches Event Files", *Comput. Phys. Commun.* 176 (2007) 300, [arXiv:hep-ph/0609017](https://arxiv.org/abs/hep-ph/0609017) |
| **HepMC3** (showered events, on the way back) | see HepMC3 above |

### The tools that build and run them

[Docker](https://www.docker.com) (the container image), [MacPorts](https://www.macports.org) and
[Homebrew](https://brew.sh) (the dependencies on the Mac), [GCC and gfortran](https://gcc.gnu.org) (Herwig, Sherpa,
WHIZARD, CalcHEP), [OCaml](https://ocaml.org) (O'Mega), [Emscripten](https://emscripten.org) (Pythia in
WebAssembly for the iPad), [CMake](https://cmake.org) and Microsoft Visual C++ (Pythia and the engine on Windows).

Versions shipped with TreeLevel Tools 0.5.0 and the 0.5.0 image: Pythia 8.318, Herwig 7.3.0 (ThePEG 2.3.0),
Sherpa 3.0.5, WHIZARD 3.1.6 (image only), CalcHEP 3.9.2, LHAPDF 6.5.3, HepMC3 3.2.5, FastJet 3.4.
The iPad module carries Pythia 8.318 alone.

## What it does

```
TreeLevel                       job folder                         TreeLevel Tools
  σ, |M|², events          →   job.json + events.lhe        →   Pythia 8 / Herwig 7
  histograms, detector     ←   events.hepmc + status.json   ←   shower, hadronisation, decays
```

The job folder is inside TreeLevel's container
(`~/Library/Containers/org.pasahome.Feyn/Data/Library/Application Support/MCJobs/<id>`): both programs reach it,
nobody else does.

## Where the executables live

A single rule: **everything that is launched lives in `~/Applications`** — `TreeLevel Tools.app` and, during
development, `TreeLevel (dev).app`. The `build/` and `.build/` folders of the repositories hold only disposable
build products; `scripts/install.sh` puts the usable version in `~/Applications` and removes the build copies from
the LaunchServices register, so that they are never launched by mistake. `/Applications` is kept for applications
installed by the App Store.

```bash
scripts/install.sh      # builds and installs into ~/Applications, with the Pythia module
scripts/release.sh      # builds, signs, notarises and makes the .dmg to distribute
```

## Installation

1. Download the [DMG](#treelevel-tools), drag `TreeLevel Tools.app` into `/Applications`, launch it once.
   It is signed and notarised by Apple.
2. That is all: Pythia 8, Herwig 7, Sherpa 3 and CalcHEP 3 travel inside the application, built for Apple
   Silicon and Intel and for macOS 13 and later. At the first launch it writes `capabilities.json` into its support
   folder, and TreeLevel then offers these generators in the Generation workspace.
3. WHIZARD 3 is not there — it compiles each process with gfortran, which macOS does not provide. For it, or to
   run everything in a single environment, there is the container below.

### The other way: the container

The image that carries the five generators for Windows runs just as well on a Mac, and the engine knows how to use
it. For anyone who already has Docker, it is one command instead of a series of builds:

```bash
docker pull ghcr.io/gpasa/treelevel-tools:latest
```

The image is built for `linux/amd64` and `linux/arm64`. The engine checks whether the image is **already** present
(`docker image inspect`) — it never pulls it by itself: a gigabyte is not downloaded behind someone's back. When it
is there, the generators that no module offers appear in `capabilities` followed by "(container)", and a job that
asks for them is run by the image's engine, with the job folder mounted as it is:

```
docker run --rm -v <job folder>:/job <image> run /job
```

Nothing is copied or converted: the mount *is* the protocol, and the container writes its own `status.json` into
the folder that TreeLevel reads back. Docker Desktop shares `/Users` by default, so the job folder — which lives
in TreeLevel's sandbox — is mounted without any particular setting.

**Installed modules keep priority**: they run natively, without a virtual machine, and do not require Docker to
be running. The container takes over only for a generator that is missing — or whose installation does not
answer.

Two measurements on this Mac, e⁻e⁺ → b b̄ at 200 GeV, 200 events showered and hadronised by Herwig:

| | |
|---|---|
| native modules | 3.0 s |
| container | 1.0 s |

The container is faster, which is surprising until one remembers that its binaries are those of a Linux
distribution built for itself, whereas ours come out of a cross-build under MacPorts. σ is the same to the ninth
decimal.

`TREELEVEL_MC_IMAGE` replaces the image, while trying a local build. Without it, the engine looks for `latest`,
then for the tag of its own version.

## On the command line

```bash
swift build -c release
.build/release/treelevel-tools capabilities          # what this installation can do
.build/release/treelevel-tools run /path/to/folder   # runs job.json
```

The folder holds `job.json` (written by TreeLevel, format described in `Protocol/MCEngineProtocol.swift`),
`events.lhe` as input, then `status.json`, `engine.log` and `events.hepmc` as output.

Each job receives a number (a counter kept in the support folder), its start and end times, and is added to the
`jobs.json` list that the window shows — it survives relaunches, a right click on a line opens the job folder or its
log, and "Clear the list" forgets it without deleting anything on disk.

Three generators: `pythia8`, `herwig7` and `passthrough` (no shower — the events are converted as they are, to
check the chain or to compare with the hard process).

## Building the modules

Since 0.4.0, rebuilt on 1 October 2026, everything the modules carry is built from source, for macOS 13, by
`scripts/build_stack.sh` — once on an Apple Silicon Mac, once on an Intel Mac, at the same path —, then
`scripts/merge_stack.sh` merges the two trees into a universal tree and `scripts/package_module.sh` turns it into
relocatable modules. `scripts/test_generators.sh` runs a real job per generator from the built application. The
sections that follow describe the earlier build, through MacPorts, kept for its notes on each generator.

## Building the Pythia driver

`Backends/pythia/main.cpp` is a program of about a hundred lines: it reads the command file written by the engine
and writes the HepMC3. It needs Pythia 8 compiled with HepMC3.

```bash
make -C Backends/pythia          # ./treelevel-pythia
make -C Backends/pythia install  # into Modules/pythia8/
```

## Building the Herwig 7 module

No macOS package manager provides Herwig: neither MacPorts, nor Homebrew outside an unmaintained tap (whose
binaries are linked to a GSL version that no longer exists). It is therefore built from source, with the official
bootstrap, and four precautions that the 2026 toolchain imposes:

```bash
# MacPorts gcc, never clang: ThePEG's global constructors call std::string before libc++'s initialiser has run,
# and Apple clang 21's typed allocation aborts at that very spot.
printf '#!/bin/sh\nexec /opt/local/bin/gfortran-mp-15 -fno-range-check "$@"\n' > ~/Library/TreeLevelMC/tools/gfortran-tl
chmod +x ~/Library/TreeLevelMC/tools/gfortran-tl

curl -LO https://herwig.hepforge.org/downloads/herwig-bootstrap
env PATH="$HOME/Library/TreeLevelMC/tools:/opt/local/bin:/usr/bin:/bin" \
    CC=/opt/local/bin/gcc-mp-15 CXX=/opt/local/bin/g++-mp-15 FC="$HOME/Library/TreeLevelMC/tools/gfortran-tl" \
    python3.13 herwig-bootstrap --lite -j 12 \
      --with-gsl=/opt/local --with-boost=/opt/local \
      --with-fastjet="$HOME/Library/TreeLevelMC/herwig7" \
      "$HOME/Library/TreeLevelMC/herwig7"

ln -s ~/Library/TreeLevelMC/herwig7 ~/Library/Application\ Support/TreeLevel\ MC\ Engine/Modules/herwig7
```

The four traps, for the record:

- **FastJet**: the `D0RunIICone` plugin, enabled by `--enable-allcxxplugins`, no longer compiles (`this->_Et`,
  two-phase name lookup). Herwig does not need it: build FastJet separately without the optional plugins, and pass
  it with `--with-fastjet`.
- **LHAPDF**: its Python wrapper does not find `libpython` in a MacPorts *framework*. Configure with
  `--disable-python` — and then fetch the PDF sets by hand, since the `lhapdf install` script imports that very
  module.
- **ThePEG**: see above, hence gcc rather than clang. The whole stack (FastJet, HepMC3, LHAPDF) must follow, or the
  C++ ABIs do not match.
- **LoopTools**: `parameter (nz2 = -2147483648)` overflows for gfortran 15, hence the `-fno-range-check` slipped
  into the wrapped compiler — `configure` overwrites `FCFLAGS`, so the flag cannot go through the environment.

The `lib/ThePEG` folder holds plugins linked to `@rpath/libHepMC3`, whose rpath is that of the build machine; the
engine sets `DYLD_FALLBACK_LIBRARY_PATH` to the module's `lib` folders, so there is nothing to touch up.

Measured on e⁻e⁺ → W⁺W⁻ at 200 GeV, 10,000 parton-level events written by TreeLevel: **12.2 s** of cascade and
hadronisation (Pythia 8: 6.4 s).

## Building the Sherpa, WHIZARD and CalcHEP modules

All with the same MacPorts gcc 15 as Herwig — the C++ ABIs must match — and reusing the HepMC3, LHAPDF and
FastJet installed in the `herwig7` prefix.

```bash
export PATH=/opt/local/bin:/usr/bin:/bin
export CC=/opt/local/bin/gcc-mp-15 CXX=/opt/local/bin/g++-mp-15 FC=/opt/local/bin/gfortran-mp-15
DEPS=~/Library/TreeLevelMC/herwig7

# Sherpa 3.0.5 — CMake. `_Static_assert` is a C keyword that clang also accepts in C++ and gcc refuses;
# mach/port.h uses it, and ATOOLS/Org/RUsage.C includes mach/mach.h.
cmake -S . -B build -DCMAKE_INSTALL_PREFIX=~/Library/TreeLevelMC/sherpa3 \
  -DCMAKE_CXX_FLAGS="-D_Static_assert=static_assert" \
  -DSHERPA_ENABLE_LHAPDF=ON -DLHAPDF_DIR=$DEPS \
  -DSHERPA_ENABLE_HEPMC3=ON -DHepMC3_DIR=$DEPS \
  -DSHERPA_ENABLE_FASTJET=ON -DFASTJET_DIR=$DEPS
cmake --build build -j 12 && cmake --install build

# WHIZARD 3.1.6 — autotools, MacPorts OCaml for O'Mega. mcfio/StdHEP mixes long and int32_t in its XDR calls,
# which gcc 15 turns into errors.
export CFLAGS="-O2 -std=gnu17 -Wno-incompatible-pointer-types -Wno-implicit-function-declaration -Wno-int-conversion"
./configure --prefix=~/Library/TreeLevelMC/whizard3 --with-hepmc=$DEPS --with-lhapdf=$DEPS \
            --with-fastjet=$DEPS --disable-latex && make -j 12 && make install

# CalcHEP 3.9.2 — a plain make, but it must be built where it will live: its libraries carry their absolute path.
make
```

Then a link from the modules folder, as for Herwig:

```bash
cd ~/Library/Application\ Support/TreeLevel\ MC\ Engine/Modules
ln -s ~/Library/TreeLevelMC/sherpa3 ~/Library/TreeLevelMC/whizard3 ~/Library/TreeLevelMC/calchep3 .
```

### What each one expects

Sherpa, WHIZARD and CalcHEP have no Les Houches reader: they are given the process (`MCProcess` in the protocol)
and compute everything themselves. Three details learnt the hard way:

- **Sherpa** writes its HepMC3 into the file whose base name it is given, and its cross section in the `C` line of
  the Asciiv3 format.
- **WHIZARD** refuses `?ps_isr_active` anywhere but on a hadronic collision, and writes no cross section into its
  HepMC3: it is read from the last line of its integration table, in femtobarns. The QED radiation of a lepton beam
  is `?isr_active`, left off — it would shift σ.
- **CalcHEP** stops at parton level: no shower and no hadronisation. A job runs in a copy of its tree made by
  `mkWORKdir`, and its gzipped Les Houches events are converted to HepMC3 by the same code as the passthrough.

### Measured: e⁻e⁺ → W⁺W⁻ at 200 GeV

| engine | σ | remark |
|---|---|---|
| TreeLevel | 19.22 pb | at tree level, M_W imposed by G_F |
| WHIZARD 3.1.6 | 19.441 ± 0.006 pb | O'Mega, its own scheme |
| CalcHEP 3.9.2 | 20.42 pb | another coupling scheme |
| Sherpa 3.0.5 | 18.2 ± 1.1 pb | QED initial-state radiation on by default |

The differences are choices of scheme, not errors: the coupling enters to the fourth power.

## Publishing a version

Everything happens on the developer's machine: the Developer ID key does not leave the keychain, and nothing is
entrusted to a continuous-integration service (the Docker image excepted, built by GitHub Actions).

```bash
scripts/release.sh                 # builds, signs, notarises, staples, makes the .dmg
scripts/release.sh 0.2.0           # the same, setting the version number (project.yml and sources)
scripts/release.sh --no-notarize   # stops after signing, to check offline
scripts/release.sh --upload        # also creates the GitHub release mac-<version> (gh authenticated)
```

Once only, beforehand:

- a **Developer ID Application** certificate in the keychain (Xcode › Settings › Accounts › Manage Certificates) —
  it comes with the developer programme membership, there is nothing more to pay;
- the notarisation credentials:
  `xcrun notarytool store-credentials "TreeLevelMC" --apple-id <id> --team-id 9LVGAJ594U --password <app password>`.

The script produces in `build/release/`: the signed and stapled application, the `.dmg` (with a link to
`/Applications`, the README and the licence), the `.zip`, `SHA256SUMS.txt` and a draft of release notes. The final
check, `spctl -a -t open --context context:primary-signature -v`, must answer `accepted`.

The iPad module is published by `Backends/pythia/wasm/release.sh <version> --upload`, under the stable release
`ipad-pythia`, with its notes in eleven languages (`Backends/pythia/wasm/notes/`).

## Licence

GNU General Public License v3 or later — see `LICENSE`. The file `Protocol/MCEngineProtocol.swift`, shared with
TreeLevel, is under the MIT licence (see its header) so that both programs can read it.

## Windows

The Windows port is in [`win/`](win/): a C# host, the common C++ engine (`Backends/engine`) compiled with MSVC, the
Pythia 8 module built the same way (`win/backends/pythia`); Herwig, Sherpa, WHIZARD and CalcHEP through the Docker
image. The protocol is the same: a job folder written on a Mac reads back on Windows and the other way round. See
[`win/README.md`](win/README.md).
