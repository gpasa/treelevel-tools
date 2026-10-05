O motor que roda os geradores Monte Carlo para o TreeLevel no Windows. Ele é instalado descompactando o arquivo em `%LOCALAPPDATA%\Programs` — sem instalador, nada no registro. **Para atualizar** uma versão anterior: feche o TreeLevel e descompacte o arquivo no mesmo lugar, substituindo os arquivos existentes.

Escolha o arquivo da sua máquina: `arm64` para um PC Copilot+ ou um tablet ARM, `x64` em todos os outros casos. Na dúvida, o x64 também funciona no ARM, em emulação.

**O que o arquivo contém**: o motor e o módulo Pythia 8 compilado para esta arquitetura. Herwig, Sherpa, WHIZARD e CalcHEP passam pela imagem de contêiner, que exige o Docker Desktop:

```
docker pull ghcr.io/gpasa/treelevel-tools
```

Não há mais nada a fazer: o próprio TreeLevel cria um contêiner efêmero para cada trabalho. O Docker Desktop precisa estar em execução quando o TreeLevel é iniciado; os geradores da imagem aparecem então, marcados “(Docker)”.

**O motor não tem janela.** É o TreeLevel que o inicia, sempre que necessário. Se você clicar duas vezes em `treelevel-tools.exe`, o Windows SmartScreen avisa sobre um aplicativo não reconhecido — o motor não é assinado — e, passado o aviso, um console mostra suas instruções de uso e se fecha. É normal, e não tem efeito algum: você nunca precisa iniciá-lo por conta própria.

### Correções desta versão

- **A imagem baixada sem número é reconhecida.** A 0.3.0 só reconhecia a etiqueta `:0.3.0`; ora, o comando que a página do pacote propõe, e o que todo mundo digita, baixa `:latest`. A imagem estava na máquina, respondia quando era iniciada à mão, e mesmo assim o TreeLevel só oferecia o Pythia. As duas etiquetas designam a mesma imagem, e agora ambas são reconhecidas.
- **Sherpa com feixes de léptons**, quando roda fora da imagem: sua seção de choque não é mais inflada pela radiação inicial de QED (uns quinze picobarns em vez de 3,2 para e⁻e⁺ → b b̄ a 200 GeV). A via que dependia disso — o Sherpa instalado por conta própria no WSL — será removida em uma próxima versão: o Docker é a via prevista.

### Cinco geradores, duas famílias

**Pythia 8** e **Herwig 7** completam os eventos partônicos que o TreeLevel lhes entrega: chuveiro, hadronização, decaimentos.

**Sherpa 3**, **WHIZARD 3** e **CalcHEP 3** não têm leitor Les Houches — eles mesmos calculam o processo descrito pelo diagrama. Por isso o protocolo lhes transmite uma descrição do processo (feixes, energias, estado final, ordens de acoplamento) junto com os eventos.

### Medido: e⁻e⁺ → W⁺W⁻ a 200 GeV

| motor | σ |
|---|---|
| TreeLevel | 19,22 pb |
| WHIZARD 3.1.6 | 19,441 ± 0,006 pb |
| CalcHEP 3.9.2 | 20,42 pb |
| Sherpa 3.0.5 | 18,2 ± 1,1 pb |

As diferenças vêm da escolha do esquema de acoplamentos, não de erros.

### Lembrete: o que a 0.3.0 trouxe

- **O modo colisor.** O gerador recebe apenas os feixes e a energia, nunca um estado final: produz a mistura inteira, como uma máquina real, e o TreeLevel conta em seguida os eventos que trazem a assinatura do processo desenhado — o que mede uma seção de choque em vez de calculá-la. Seis famílias de canais, entre elas a QCD dura, a fotoprodução e a seção de choque total. Por enquanto, Pythia 8.
- **Duas configurações de máquina combinadas.** Um feixe de léptons entra como lépton ou como o fluxo de fótons que ele irradia, nunca os dois em uma mesma geração: o motor gera os dois e guarda de cada um a parte que lhe cabe segundo sua seção de choque.
- **A seção de choque informada é a de depois do último evento.** O Pythia normaliza após o seu laço; o driver escrevia a estimativa corrente, errada em 12 % com algumas centenas de eventos.
- **O programa se chama TreeLevel Tools**, e o executável `treelevel-tools.exe`.
- Trabalhos numerados, com data e hora e guardados em uma lista, que o TreeLevel reabre; seção de choque lida onde cada gerador a coloca.

O TreeLevel Tools é GPL v3 ou posterior (veja `LICENSE.txt` no arquivo); cada gerador mantém sua própria licença, abaixo.
