모듈 버전: **$MODULE** — Pythia **$PYTHIA_VERSION**, TreeLevel Tools $MODULE의 공통 드라이버와 함께 WebAssembly로 컴파일했습니다. 이 페이지는 항상 같은 이름을 유지합니다. iPad용 TreeLevel(1.4 이상)은 여기서 최신 버전을 가져오고, `module.json`에서 그 번호를 읽어 설정에 표시하며, 더 새로운 버전이 게시되면 업데이트를 제안하고, 각 파일을 `module.json`이 제시하는 지문과 대조합니다. 모듈은 웹 보기 안에서 실행되며 어디로도 아무것도 보내지 않습니다.

이 모듈이 할 수 있는 것: `$FEATURES`. ‘spacetime’: 파톤과 하드론을 상호작용 영역에 배치하는 것으로, TreeLevel은 이를 펨토미터 규모로 보여 줍니다.

| 파일 | 역할 |
|---|---|
| `module.json` | 모듈과 Pythia의 버전, 모듈이 할 수 있는 것, 각 파일의 지문 |
| `treelevel-pythia-web.wasm`, `.js` | Pythia $PYTHIA_VERSION와 드라이버, WebAssembly 형식 |
| `runner.js` | TreeLevel 작업을 실행: 계획, 분할, 병합 |
| `leptons.pack` | Pythia 데이터(xmldoc, tunes, setups) — 렙톤 빔 |
| `pdfdata.pack` | 파톤 밀도 — 하드론 빔, 선택 사항 |
| `$SOURCES` | pythia.org에 게시된 그대로의 Pythia $PYTHIA_VERSION 소스 |
| `COPYING.pythia8` | Pythia 라이선스(GPL v2 이상) |

iPad용 TreeLevel 1.3은 [ipad-pythia-8.318](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia-8.318)에서 모듈을 내려받으며, 그 지문을 고정해 둡니다. 그 페이지는 바뀌지 않습니다.

**Pythia 8과 그 저자들.** Pythia 8은 © Torbjörn Sjöstrand와 Pythia 공동 연구진 — [pythia.org](https://pythia.org) — 의 것이며 GPL v2 이상으로 배포됩니다. 이 모듈의 물리는 모두 그들의 것입니다. 이 모듈로 얻은 결과를 발표한다면 다음을 인용하십시오: C. Bierlich et al., "A comprehensive guide to the physics and usage of PYTHIA 8.3", *SciPost Phys. Codebases* 8 (2022), [arXiv:2203.11601](https://arxiv.org/abs/2203.11601). TreeLevel Tools가 구동하는 다른 생성기와 그 저자들: [CREDITS.md](https://github.com/gpasa/treelevel-tools/blob/main/CREDITS.md).

이 모듈은 TreeLevel과 별개인 프로그램으로 남습니다. 앱은 작업을 넘기고 결과를 다시 읽을 뿐입니다. 드라이버와 `runner.js`의 소스는 이 저장소(`Backends/pythia`)의 태그 `ipad-pythia-module-$MODULE`에 있습니다. 체크섬은 `SHA256SUMS.txt`에 있습니다.
