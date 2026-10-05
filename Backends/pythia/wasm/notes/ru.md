Версия модуля: **$MODULE** — Pythia **$PYTHIA_VERSION**, скомпилированная в WebAssembly вместе с общей управляющей
программой TreeLevel Tools $MODULE. Эта страница всегда сохраняет одно и то же имя: TreeLevel на iPad (1.4 и новее)
берёт с неё последнюю версию, читает её номер в `module.json` и показывает его в своих настройках, предлагает
обновление, когда выходит более новая версия, и сверяет каждый файл с отпечатком, который указан для него в
`module.json`. Приложение запускает модуль в веб-представлении, ничего никуда не отправляя.

Что умеет этот модуль: `$FEATURES`. «spacetime»: размещение партонов и адронов в зоне взаимодействия, которую
TreeLevel показывает в масштабе фемтометра.

| файл | назначение |
|---|---|
| `module.json` | версия модуля и Pythia, что он умеет, отпечаток каждого файла |
| `treelevel-pythia-web.wasm`, `.js` | Pythia $PYTHIA_VERSION и управляющая программа, в WebAssembly |
| `runner.js` | выполняет задание TreeLevel: план, части, объединение |
| `leptons.pack` | данные Pythia (xmldoc, tunes, setups) — лептонные пучки |
| `pdfdata.pack` | партонные плотности — адронные пучки, необязательно |
| `$SOURCES` | исходный код Pythia $PYTHIA_VERSION в том виде, в каком он опубликован на pythia.org |
| `COPYING.pythia8` | лицензия Pythia (GPL v2 или более поздняя) |

TreeLevel 1.3 на iPad загружает свой модуль из
[ipad-pythia-8.318](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia-8.318), отпечатки которого в
нём зафиксированы: эта страница не меняется.

**Pythia 8 и её авторы.** Pythia 8 — это © Torbjörn Sjöstrand и коллаборация Pythia —
[pythia.org](https://pythia.org); она распространяется под лицензией GPL v2 или более поздней. Вся физика этого
модуля принадлежит им. Если вы публикуете результат, полученный с его помощью, цитируйте: C. Bierlich et al.,
«A comprehensive guide to the physics and usage of PYTHIA 8.3», *SciPost Phys. Codebases* 8 (2022),
[arXiv:2203.11601](https://arxiv.org/abs/2203.11601). Другие генераторы, которыми управляет TreeLevel Tools, и их
авторы: [CREDITS.md](https://github.com/gpasa/treelevel-tools/blob/main/CREDITS.md).

Модуль остаётся программой, отдельной от TreeLevel: приложение передаёт ему задание и считывает результат.
Исходный код управляющей программы и `runner.js` находится в этом репозитории (`Backends/pythia`), под тегом
`ipad-pythia-module-$MODULE`. Контрольные суммы в `SHA256SUMS.txt`.
