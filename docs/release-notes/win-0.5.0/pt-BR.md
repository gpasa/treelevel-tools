O motor que roda os geradores Monte Carlo para o TreeLevel 1.4 no Windows (e ainda para o 1.3). Ele é instalado descompactando o arquivo em `%LOCALAPPDATA%\Programs` — sem instalador, nada no registro. **Para atualizar** uma versão anterior: feche o TreeLevel e descompacte o arquivo no mesmo lugar, substituindo os arquivos existentes.

Escolha o arquivo da sua máquina: `arm64` para um PC Copilot+ ou um tablet ARM, `x64` em todos os outros casos. Na dúvida, o x64 também funciona no ARM, em emulação.

**O que o arquivo contém**: `treelevel-tools.exe`, que o TreeLevel inicia; `treelevel-engine.exe`, o motor que escreve o cartão de cada gerador e o conduz; o módulo Pythia 8 compilado para esta arquitetura; `CREDITS.md`. Herwig, Sherpa, WHIZARD e CalcHEP passam pela imagem de contêiner, que exige o Docker Desktop:

```
docker pull ghcr.io/gpasa/treelevel-tools:latest
```

Não há mais nada a fazer: o próprio TreeLevel cria um contêiner efêmero para cada trabalho. O Docker Desktop precisa estar em execução quando o TreeLevel é iniciado; os geradores da imagem aparecem então, marcados “(Docker)”.

**O motor não tem janela.** É o TreeLevel que o inicia, sempre que necessário. Se você clicar duas vezes em `treelevel-tools.exe`, o Windows SmartScreen avisa sobre um aplicativo não reconhecido — o motor não é assinado — e, passado o aviso, um console mostra suas instruções de uso e se fecha. É normal, e não tem efeito algum.

### O que muda

- **A zona de interação, no femtômetro.** Para o TreeLevel 1.4, o driver do Pythia sabe situar cada interação partônica na sobreposição dos dois hádrons e cada hádron onde sua corda se rompeu (chave `spaceTime` do trabalho: `PartonVertex:setVertex`, `Fragmentation:setVertices`). Ele escreve para cada párton seu fluxo de cor e seu estado no Pythia, e para cada partícula nascida fora do seu vértice o seu próprio local de nascimento — o que o corte ampliado e a vista 3D do TreeLevel 1.4 desenham. É o modelo do gerador, nada medido.
- **Um único deslocamento da região luminosa.** Com essas posições, o Pythia deslocava os hádrons duas vezes; agora o próprio driver posiciona o evento, com um único vetor. Sem a chave, nada muda.
- **O motor diz o que sabe fazer**: `treelevel-tools capabilities` anuncia `spaceTimeGenerators` (o Pythia nativo quando seu driver responde “spacetime”, e o que a imagem anuncia). O TreeLevel 1.4 só mostra a caixa “posições na zona de interação” se ela constar ali.
- **Compatível com o TreeLevel 1.3**: um trabalho sem a chave `spaceTime` roda exatamente como com a 0.4.0.
- **A imagem Docker 0.5 virá depois**: até lá, `:latest` é a imagem 0.4.0, e Herwig, Sherpa, WHIZARD e CalcHEP rodam nela como antes; a zona de interação passa pelo Pythia nativo deste arquivo.
- **O mesmo motor que a `mac-0.5.0`**: o mesmo driver do Pythia (`Backends/pythia/main.cpp`), as mesmas chaves do trabalho, os mesmos atributos escritos.
