TreeLevel이 담을 수 없는 GPL 도구를 여러분의 컴퓨터에서—아무것도 밖으로 나가지 않습니다. TreeLevel은 샌드박스 안에서 실행되며 어떤 프로그램도 실행하지 않습니다. 이 패키지가 그 도구들을 실행할 수 있도록 허용된 쪽입니다.

- **Apple Silicon 및 Intel** Mac용, macOS 13 이상.
- `TreeLevel Tools.app`을 `/Applications`로 끌어다 놓고 한 번 실행합니다.
- 생성기 네 개가 **이미 들어 있으므로** 따로 설치할 것이 없습니다:
  - **Pythia 8**과 **Herwig 7**은 두 렙톤 사이의 TreeLevel 사건을 완성합니다: 샤워, 강입자화, 붕괴. **Pythia 8**은 ‘가속기’ 출처도 구동합니다: 빔 두 개, 에너지 하나, 그리고 충돌이 만들어 내는 모든 것.
  - **Sherpa 3**과 **CalcHEP 3**은 다이어그램이 기술하는 과정을 직접 계산합니다.
- 그러면 TreeLevel이 ‘생성’ 작업 공간에서 이들을 제공합니다.

모든 생성기의 카드는 Docker 이미지 안과 같은 C++ 엔진이 작성합니다: 같은 작업은 Mac에서나 Linux에서나 같은 카드를 만듭니다.

**WHIZARD 3**은 포함되어 있지 않습니다: 각 과정을 gfortran으로 컴파일하는데, macOS도 Xcode도 gfortran을 제공하지 않습니다. 이를 갖추는 방법은 두 가지이며, TreeLevel Tools 창에서 체크합니다:

- **Docker 이미지** `ghcr.io/gpasa/treelevel-tools:latest`, 다섯 가지 도구를 모두 담고 있습니다. 체크하면 **모든** 작업을 이 이미지가 실행하고, 여기에 번들된 생성기는 쓰이지 않습니다;
- 여러분 **자신의 설치**(MacPorts, Homebrew), 있다면.

기본적으로는 둘 다 쓰이지 않습니다: 처음 상태에서는 여기에 번들된 생성기만 제공되므로, 같은 문서는 두 컴퓨터에서 같은 결과를 냅니다.

Apple이 서명하고 공증했습니다. 체크섬은 `SHA256SUMS.txt`에 있습니다.
