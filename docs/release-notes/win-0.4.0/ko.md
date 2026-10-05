Windows에서 TreeLevel 1.3을 위해 몬테카를로 생성기를 돌리는 엔진입니다. 압축 파일을 `%LOCALAPPDATA%\Programs`에 풀기만 하면 설치됩니다—설치 프로그램도 없고 레지스트리에 남는 것도 없습니다. 이전 버전을 **업데이트하려면** TreeLevel을 닫고, 압축 파일을 같은 자리에 풀어 파일을 덮어쓰십시오.

여러분의 컴퓨터에 맞는 압축 파일을 고르십시오: Copilot+ PC나 ARM 태블릿이면 `arm64`, 그 밖에는 모두 `x64`. 헷갈릴 때는 x64판도 ARM에서 에뮬레이션으로 돌아갑니다.

**압축 파일의 내용**: TreeLevel이 실행하는 `treelevel-tools.exe`, 각 생성기의 카드를 쓰고 생성기를 구동하는 엔진 `treelevel-engine.exe`, 이 아키텍처용으로 컴파일된 Pythia 8 모듈, `CREDITS.md`. Herwig, Sherpa, WHIZARD, CalcHEP은 컨테이너 이미지를 거치며, 이 이미지에는 Docker Desktop이 필요합니다:

```
docker pull ghcr.io/gpasa/treelevel-tools:0.4.0
```

더 할 일은 없습니다: TreeLevel이 작업마다 일회용 컨테이너를 직접 만듭니다. TreeLevel이 시작할 때 Docker Desktop이 실행 중이어야 하며, 그러면 이미지의 생성기가 ‘(Docker)’ 표시를 달고 나타납니다.

**엔진에는 창이 없습니다.** TreeLevel이 필요할 때마다 실행합니다. `treelevel-tools.exe`를 더블클릭하면 Windows SmartScreen이 인식할 수 없는 앱이라고 경고합니다—엔진은 서명되어 있지 않습니다—. 경고를 넘기면 콘솔이 사용법을 보여 주고 닫힙니다. 정상이며, 아무 영향도 없습니다.

### 바뀐 점

- **Windows, Mac, 이미지에 하나의 엔진.** 생성기의 카드는 이제 C++(`Backends/engine`)로 한 번만 작성되며, 같은 프로그램이 여기서도, Mac에서도, 컨테이너 안에서도 돌아갑니다. Windows 쪽은 이제 Docker, 이미지, Pythia 모듈을 찾는 일만 합니다.
- **‘Tout faire tourner dans l'image Docker’**, TreeLevel 1.3 설정에 있는 상자입니다. 체크하면 Pythia를 포함한 모든 작업을 이미지가 실행하며, Docker나 이미지가 없으면 아무것도 제공되지 않습니다. 체크를 해제하면 Pythia는 네이티브로 돌아가고 나머지는 이미지를 거칩니다.
- **실험이 기록하는 것**: TreeLevel 1.3의 ‘가속기’ 출처는 현상 하나를 고릅니다—검출기가 보는 모든 것, 광자에 의한 산란, γ*/Z로 쌍소멸, 교환되거나 생성되는 W, 보손 쌍, 제트, 광생성, 무른 충돌—. 엔진은 그에 맞는 문턱값으로 이를 엽니다(산란에는 Q², 제트에는 p_T).
- **각 입자가 태어난 곳**: Pythia 드라이버는 꼭짓점의 위치와 각 사건의 경성 과정을 씁니다. TreeLevel은 이를 그리고, 이를 기준으로 거릅니다.
- 어디서나 **Pythia 8.318**, 그 튠(`Monash 2013`, `A14`…)은 Pythia 번호로 변환됩니다.
- **악센트가 들어간 경로**: 악센트가 있는 사용자 이름 아래의 작업 폴더도 다른 폴더처럼 열립니다.
- 제거됨: WSL 경로(배포판에 직접 설치한 Herwig나 Sherpa)—Docker가 예정된 경로입니다.

TreeLevel Tools는 GPL v3 이상을 따릅니다(압축 파일 안의 `LICENSE.txt` 참조). 각 생성기는 저마다의 사용권을 유지합니다—`CREDITS.md`와 아래를 보십시오.
