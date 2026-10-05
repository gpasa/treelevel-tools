TreeLevel Tools의 공통 드라이버와 함께 WebAssembly로 컴파일된 Pythia 8입니다. iPad의 TreeLevel은 이 페이지에서 파일을 하나씩 내려받고, 각 파일을 앱에 고정된 지문과 대조합니다. 웹 보기 안에서 실행하며 어디로도 아무것도 보내지 않습니다. 사건은 샤워와 강입자화를 거쳐 나오며, TreeLevel의 ‘가속기’ 출처를 iPad에서도 쓸 수 있게 됩니다.

| 파일 | 역할 |
|---|---|
| `treelevel-pythia-web.wasm`, `.js` | Pythia 8.318과 드라이버, WebAssembly 형식 |
| `runner.js` | TreeLevel 작업을 실행: 계획, 분할, 병합 |
| `leptons.pack` | Pythia 데이터(xmldoc, tunes, setups) — 렙톤 빔 |
| `pdfdata.pack` | 파톤 밀도 — 강입자 빔, 선택 사항 |
| `pythia8318-sources.tgz` | pythia.org에 게시된 그대로의 Pythia 8.318 소스 |
| `COPYING.pythia8` | Pythia 사용권(GPL v2 이상) |

### Pythia 8과 그 저자들

Pythia 8은 © Torbjörn Sjöstrand와 Pythia 공동 연구진—[pythia.org](https://pythia.org)—이며, GPL v2 이상으로 배포됩니다. 이 모듈의 물리는 모두 그들의 것입니다. 이 모듈로 얻은 결과를 발표한다면 다음을 인용하십시오: C. Bierlich et al., “A comprehensive guide to the physics and usage of PYTHIA 8.3”, *SciPost Phys. Codebases* 8 (2022), [arXiv:2203.11601](https://arxiv.org/abs/2203.11601).

TreeLevel Tools가 조종하는 다른 생성기들과 그 저자들: [CREDITS.md](https://github.com/gpasa/treelevel-tools/blob/1.3-dev/CREDITS.md). 모듈은 TreeLevel과 별개인 프로그램으로 남습니다: 앱은 작업을 넘기고 결과를 다시 읽습니다. 드라이버와 `runner.js`의 소스는 이 저장소의, 이 릴리스의 태그(`Backends/pythia`)에 있습니다. 체크섬은 `SHA256SUMS.txt`에 있습니다.
