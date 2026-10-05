Pythia 8, скомпилированная в WebAssembly вместе с общей управляющей программой TreeLevel Tools. TreeLevel на iPad загружает её
с этой страницы, файл за файлом, и сверяет каждый с отпечатком, зафиксированным в приложении; он запускает её
в веб-представлении, ничего никуда не отправляя. События выходят из неё уже с ливнем и адронизацией, и источник
«Ускоритель» в TreeLevel становится доступен на iPad.

| файл | назначение |
|---|---|
| `treelevel-pythia-web.wasm`, `.js` | Pythia 8.318 и управляющая программа, в WebAssembly |
| `runner.js` | выполняет задание TreeLevel: план, части, объединение |
| `leptons.pack` | данные Pythia (xmldoc, tunes, setups) — лептонные пучки |
| `pdfdata.pack` | партонные плотности — адронные пучки, необязательно |
| `pythia8318-sources.tgz` | исходный код Pythia 8.318 в том виде, в каком он опубликован на pythia.org |
| `COPYING.pythia8` | лицензия Pythia (GPL v2 или более поздняя) |

### Pythia 8 и её авторы

Pythia 8 — © Torbjörn Sjöstrand и коллаборация Pythia — [pythia.org](https://pythia.org) — распространяется
под GPL v2 или более поздней. Вся физика этого модуля — их. Если вы публикуете результат, полученный с его помощью,
цитируйте: C. Bierlich et al., «A comprehensive guide to the physics and usage of PYTHIA 8.3»,
*SciPost Phys. Codebases* 8 (2022), [arXiv:2203.11601](https://arxiv.org/abs/2203.11601).

Другие генераторы, которыми управляет TreeLevel Tools, и их авторы:
[CREDITS.md](https://github.com/gpasa/treelevel-tools/blob/1.3-dev/CREDITS.md).
Модуль остаётся программой, отдельной от TreeLevel: приложение передаёт ему задание и считывает результат. Исходный код
управляющей программы и `runner.js` находится в этом репозитории, под тегом этого выпуска (`Backends/pythia`).
Контрольные суммы в `SHA256SUMS.txt`.
