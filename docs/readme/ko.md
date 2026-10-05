[TreeLevel](https://treelevel.pasahome.org)의 사건 생성기를 여러분의 컴퓨터에서. TreeLevel이 로컬 폴더에 작업을 기록하면, 이 프로그램이 그것을 **Pythia 8**, **Herwig 7**, **Sherpa 3**, **WHIZARD 3** 또는 **CalcHEP 3**에 맡깁니다 — 사건의 샤워와 하드론화, 또는 가속기의 충돌 전체 — 그리고 결과를 HepMC3로 다시 기록하며, TreeLevel이 이를 읽습니다. 네트워크를 거치는 것은 없고, 계정도 서비스도 없습니다. iPad에서는 WebAssembly로 컴파일한 Pythia 8이 같은 역할을 하며, [해당 릴리스](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia)에서 내려받습니다.

이 생성기들이 **GPL** 라이선스이므로 따로 배포합니다. 이 저장소는 GPL v3이며, TreeLevel에는 그 코드가 전혀 들어 있지 않습니다.

| 시스템 | 다운로드 | 포함 내용 |
|---|---|---|
| **macOS** 13 이상, Apple Silicon 및 Intel | [TreeLevelTools-0.5.0.dmg](https://github.com/gpasa/treelevel-tools/releases/download/mac-0.5.0/TreeLevelTools-0.5.0.dmg) | Pythia 8, Herwig 7, Sherpa 3, CalcHEP 3, 바로 실행 가능 |
| **Windows** 10 및 11 | [x64](https://github.com/gpasa/treelevel-tools/releases/download/win-0.5.1/TreeLevelTools-0.5.1-x64.zip) · [ARM64](https://github.com/gpasa/treelevel-tools/releases/download/win-0.5.1/TreeLevelTools-0.5.1-arm64.zip) | Pythia 8; 나머지는 Docker 이미지로 |
| **iPad** | TreeLevel 설정에서([릴리스](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia)) | WebAssembly용 Pythia 8 |
| **Docker**, 모든 시스템 | `docker pull ghcr.io/gpasa/treelevel-tools:latest` | 생성기 다섯 개 전부, WHIZARD 3 포함 |

**Mac**: `TreeLevel Tools.app`을 `/Applications`로 끌어다 놓고 한 번 실행합니다. 그러면 TreeLevel이 생성 작업 공간에서 그 생성기들을 제공합니다. **Windows**: 압축 파일을 `%LOCALAPPDATA%\Programs`에 풉니다. **iPad**: 설정의 *Pythia 8 모듈* 카드가 이를 내려받고 각 파일을 검증합니다. **Docker**: 이미지가 있으면 TreeLevel Tools는 어떤 모듈도 제공하지 않는 생성기를 그 안에서 실행합니다(Mac에서는 체크상자 하나로 모든 작업을 이미지에 맡길 수 있습니다).
