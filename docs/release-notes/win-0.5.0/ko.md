Windows에서 TreeLevel 1.4(그리고 여전히 1.3)을 위해 몬테카를로 생성기를 돌리는 엔진입니다. 압축 파일을 `%LOCALAPPDATA%\Programs`에 풀기만 하면 설치됩니다—설치 프로그램도 없고 레지스트리에 남는 것도 없습니다. 이전 버전을 **업데이트하려면** TreeLevel을 닫고, 압축 파일을 같은 자리에 풀어 파일을 덮어쓰십시오.

여러분의 컴퓨터에 맞는 압축 파일을 고르십시오: Copilot+ PC나 ARM 태블릿이면 `arm64`, 그 밖에는 모두 `x64`. 헷갈릴 때는 x64판도 ARM에서 에뮬레이션으로 돌아갑니다.

**압축 파일의 내용**: TreeLevel이 실행하는 `treelevel-tools.exe`, 각 생성기의 카드를 쓰고 생성기를 구동하는 엔진 `treelevel-engine.exe`, 이 아키텍처용으로 컴파일된 Pythia 8 모듈, `CREDITS.md`. Herwig, Sherpa, WHIZARD, CalcHEP은 컨테이너 이미지를 거치며, 이 이미지에는 Docker Desktop이 필요합니다:

```
docker pull ghcr.io/gpasa/treelevel-tools:latest
```

더 할 일은 없습니다: TreeLevel이 작업마다 일회용 컨테이너를 직접 만듭니다. TreeLevel이 시작할 때 Docker Desktop이 실행 중이어야 하며, 그러면 이미지의 생성기가 ‘(Docker)’ 표시를 달고 나타납니다.

**엔진에는 창이 없습니다.** TreeLevel이 필요할 때마다 실행합니다. `treelevel-tools.exe`를 더블클릭하면 Windows SmartScreen이 인식할 수 없는 앱이라고 경고합니다—엔진은 서명되어 있지 않습니다—. 경고를 넘기면 콘솔이 사용법을 보여 주고 닫힙니다. 정상이며, 아무 영향도 없습니다.

### 바뀐 점

- **펨토미터 단위의 상호작용 영역.** TreeLevel 1.4를 위해 Pythia 드라이버는 각 파톤 상호작용을 두 강입자의 겹침 안에, 각 강입자를 그 끈이 끊어진 자리에 배치할 수 있습니다(작업 키 `spaceTime`: `PartonVertex:setVertex`, `Fragmentation:setVertices`). 각 파톤에 대해서는 색 흐름과 Pythia 상태를, 자기 꼭짓점이 아닌 곳에서 태어난 각 입자에 대해서는 그 자신의 탄생 위치를 씁니다—TreeLevel 1.4의 확대한 단면과 3D 보기가 그리는 것이 바로 이것입니다. 이는 생성기의 모형이며, 측정된 것이 아닙니다.
- **빔 충돌 영역 오프셋은 한 번만.** 이 위치들이 있으면 Pythia는 강입자를 두 번 옮겼습니다. 이제 드라이버가 벡터 하나로 사건 자체를 배치합니다. 키가 없으면 아무것도 바뀌지 않습니다.
- **엔진이 자기가 할 수 있는 일을 알립니다**: `treelevel-tools capabilities`가 `spaceTimeGenerators`를 알립니다(드라이버가 ‘spacetime’이라고 답할 때의 네이티브 Pythia, 그리고 이미지가 알리는 것). TreeLevel 1.4는 거기에 들어 있을 때만 ‘상호작용 영역의 위치’ 상자를 보여 줍니다.
- **TreeLevel 1.3과 호환**: `spaceTime` 키가 없는 작업은 0.4.0과 똑같이 실행됩니다.
- **Docker 이미지 0.5는 뒤따릅니다**: 그때까지 `:latest`는 이미지 0.4.0이며, Herwig, Sherpa, WHIZARD, CalcHEP은 예전처럼 그 안에서 돌아갑니다. 상호작용 영역은 이 압축 파일의 네이티브 Pythia를 거칩니다.
- **`mac-0.5.0`과 같은 엔진**: 같은 Pythia 드라이버(`Backends/pythia/main.cpp`), 같은 작업 키, 같은 속성을 씁니다.
