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
