O motor que roda os geradores Monte Carlo para o TreeLevel 1.3 no Windows. Ele é instalado descompactando o arquivo em `%LOCALAPPDATA%\Programs` — sem instalador, nada no registro. **Para atualizar** uma versão anterior: feche o TreeLevel e descompacte o arquivo no mesmo lugar, substituindo os arquivos existentes.

Escolha o arquivo da sua máquina: `arm64` para um PC Copilot+ ou um tablet ARM, `x64` em todos os outros casos. Na dúvida, o x64 também funciona no ARM, em emulação.

**O que o arquivo contém**: `treelevel-tools.exe`, que o TreeLevel inicia; `treelevel-engine.exe`, o motor que escreve o cartão de cada gerador e o conduz; o módulo Pythia 8 compilado para esta arquitetura; `CREDITS.md`. Herwig, Sherpa, WHIZARD e CalcHEP passam pela imagem de contêiner, que exige o Docker Desktop:

```
docker pull ghcr.io/gpasa/treelevel-tools:0.4.0
```

Não há mais nada a fazer: o próprio TreeLevel cria um contêiner efêmero para cada trabalho. O Docker Desktop precisa estar em execução quando o TreeLevel é iniciado; os geradores da imagem aparecem então, marcados “(Docker)”.

**O motor não tem janela.** É o TreeLevel que o inicia, sempre que necessário. Se você clicar duas vezes em `treelevel-tools.exe`, o Windows SmartScreen avisa sobre um aplicativo não reconhecido — o motor não é assinado — e, passado o aviso, um console mostra suas instruções de uso e se fecha. É normal, e não tem efeito algum.

### O que muda

- **Um único motor para o Windows, o Mac e a imagem.** Os cartões dos geradores passam a ser escritos uma única vez, em C++ (`Backends/engine`), e o mesmo programa roda aqui, no Mac e no contêiner. A parte do Windows agora só encontra o Docker, a imagem e o módulo Pythia.
- **“Tout faire tourner dans l'image Docker”**, uma caixa dos Ajustes do TreeLevel 1.3. Marcada, a imagem conduz todos os trabalhos, inclusive o Pythia, e nada é oferecido quando faltam o Docker ou a imagem. Desmarcada, o Pythia roda nativamente e o resto passa pela imagem.
- **O que o experimento registra**: a fonte Máquina do TreeLevel 1.3 escolhe um fenômeno — tudo o que o detector vê, o espalhamento por um fóton, a aniquilação em γ*/Z, o W trocado ou produzido, os pares de bósons, os jatos, a fotoprodução, as colisões moles —, e o motor o abre com o limiar que lhe convém (Q² para os espalhamentos, p_T para os jatos).
- **Onde cada partícula nasceu**: o driver do Pythia escreve a posição dos vértices, e o processo duro de cada evento; o TreeLevel os desenha e filtra por eles.
- **Pythia 8.318** em todo lugar, com seus tunes (`Monash 2013`, `A14`…) traduzidos em números do Pythia.
- **Caminhos com acentos**: uma pasta de trabalho sob um nome de usuário com acentos abre como qualquer outra.
- Removida: a via WSL (Herwig ou Sherpa instalados à mão em uma distribuição) — o Docker é a via prevista.

O TreeLevel Tools é GPL v3 ou posterior (veja `LICENSE.txt` no arquivo); cada gerador mantém sua própria licença — veja `CREDITS.md`, e abaixo.
