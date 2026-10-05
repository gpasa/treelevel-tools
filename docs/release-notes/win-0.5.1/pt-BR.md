O motor que roda os geradores Monte Carlo para o TreeLevel 1.4 no Windows (e ainda para o 1.3). Ele é instalado descompactando o arquivo em `%LOCALAPPDATA%\Programs` — sem instalador, nada no registro. **Para atualizar** uma versão anterior: feche o TreeLevel e descompacte o arquivo no mesmo lugar, substituindo os arquivos existentes.

Escolha o arquivo da sua máquina: `arm64` para um PC Copilot+ ou um tablet ARM, `x64` em todos os outros casos. Na dúvida, o x64 também funciona no ARM, em emulação.

**O que o arquivo contém**: `treelevel-tools.exe`, que o TreeLevel inicia; `treelevel-engine.exe`, o motor que escreve o cartão de cada gerador e o conduz; o módulo Pythia 8 compilado para esta arquitetura; `CREDITS.md`. Herwig, Sherpa, WHIZARD e CalcHEP passam pela imagem de contêiner, que exige o Docker Desktop:

```
docker pull ghcr.io/gpasa/treelevel-tools:latest
```

Não há mais nada a fazer: o próprio TreeLevel cria um contêiner efêmero para cada trabalho. O Docker Desktop precisa estar em execução quando o TreeLevel é iniciado; os geradores da imagem aparecem então, marcados “(Docker)”.

**O motor não tem janela.** É o TreeLevel que o inicia, sempre que necessário. Se você clicar duas vezes em `treelevel-tools.exe`, o Windows SmartScreen avisa sobre um aplicativo não reconhecido — o motor não é assinado — e, passado o aviso, um console mostra suas instruções de uso e se fecha. É normal, e não tem efeito algum.

### O que muda

- **O host pede a imagem 0.5.0.** Ela está publicada e `:latest` aponta para ela; o motor do Windows procura primeiro `ghcr.io/gpasa/treelevel-tools:0.5.0`, depois `:latest`, como antes. Com a imagem 0.5.0, a caixa “Tout faire tourner dans l'image Docker” também dá a zona de interação (a imagem anuncia `spaceTimeGenerators`).
- **Para aproveitar com o Docker**: `docker pull ghcr.io/gpasa/treelevel-tools:latest` (ou `:0.5.0`) substitui a imagem 0.4.0.
- **Nada mais muda**: o mesmo driver do Pythia e as mesmas chaves do trabalho que a `win-0.5.0`; compatível com o TreeLevel 1.3 e 1.4.
