Windows에서 TreeLevel 1.4(그리고 여전히 1.3)을 위해 몬테카를로 생성기를 돌리는 엔진입니다. 압축 파일을 `%LOCALAPPDATA%\Programs`에 풀기만 하면 설치됩니다—설치 프로그램도 없고 레지스트리에 남는 것도 없습니다. 이전 버전을 **업데이트하려면** TreeLevel을 닫고, 압축 파일을 같은 자리에 풀어 파일을 덮어쓰십시오.

여러분의 컴퓨터에 맞는 압축 파일을 고르십시오: Copilot+ PC나 ARM 태블릿이면 `arm64`, 그 밖에는 모두 `x64`. 헷갈릴 때는 x64판도 ARM에서 에뮬레이션으로 돌아갑니다.

**압축 파일의 내용**: TreeLevel이 실행하는 `treelevel-tools.exe`, 각 생성기의 카드를 쓰고 생성기를 구동하는 엔진 `treelevel-engine.exe`, 이 아키텍처용으로 컴파일된 Pythia 8 모듈, `CREDITS.md`. Herwig, Sherpa, WHIZARD, CalcHEP은 컨테이너 이미지를 거치며, 이 이미지에는 Docker Desktop이 필요합니다:

```
docker pull ghcr.io/gpasa/treelevel-tools:latest
```

더 할 일은 없습니다: TreeLevel이 작업마다 일회용 컨테이너를 직접 만듭니다. TreeLevel이 시작할 때 Docker Desktop이 실행 중이어야 하며, 그러면 이미지의 생성기가 ‘(Docker)’ 표시를 달고 나타납니다.

**엔진에는 창이 없습니다.** TreeLevel이 필요할 때마다 실행합니다. `treelevel-tools.exe`를 더블클릭하면 Windows SmartScreen이 인식할 수 없는 앱이라고 경고합니다—엔진은 서명되어 있지 않습니다—. 경고를 넘기면 콘솔이 사용법을 보여 주고 닫힙니다. 정상이며, 아무 영향도 없습니다.

### 바뀐 점

- **호스트가 이미지 0.5.0을 요청합니다.** 이미지는 게시되었고 `:latest`가 이를 가리킵니다. Windows 엔진은 예전처럼 먼저 `ghcr.io/gpasa/treelevel-tools:0.5.0`을, 그다음 `:latest`를 찾습니다. 이미지 0.5.0에서는 ‘Tout faire tourner dans l'image Docker’ 상자도 상호작용 영역을 제공합니다(이미지가 `spaceTimeGenerators`를 알립니다).
- **Docker에서 이를 활용하려면**: `docker pull ghcr.io/gpasa/treelevel-tools:latest`(또는 `:0.5.0`)가 이미지 0.4.0을 대체합니다.
- **그 밖에는 바뀌는 것이 없습니다**: Pythia 드라이버도 작업 키도 `win-0.5.0`과 같으며, TreeLevel 1.3 및 1.4와 호환됩니다.
