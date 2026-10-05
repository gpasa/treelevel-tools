> **Substituída pela [0.3.1](https://github.com/gpasa/treelevel-tools/releases/tag/win-0.3.1).** Esta só reconhece a imagem com a etiqueta `:0.3.0`; a 0.3.1 também aceita `:latest`, a que `docker pull` baixa sem número.

O motor que roda os geradores Monte Carlo para o TreeLevel no Windows. Ele é instalado descompactando o arquivo em `%LOCALAPPDATA%\Programs` — sem instalador, nada no registro.

Escolha o arquivo da sua máquina: `arm64` para um PC Copilot+ ou um tablet ARM, `x64` em todos os outros casos. Na dúvida, o x64 também funciona no ARM, em emulação.

**O que o arquivo contém**: o motor e o módulo Pythia 8 compilado para esta arquitetura. Herwig, Sherpa, WHIZARD e CalcHEP passam pela imagem de contêiner `ghcr.io/gpasa/treelevel-tools`, que exige o Docker. Baixe-a **com o número**:

```
docker pull ghcr.io/gpasa/treelevel-tools:0.3.0
```

Esta versão do motor só reconhece essa etiqueta: uma imagem baixada sem número (portanto `:latest`) está na máquina, mas o TreeLevel não oferece os geradores dela. As duas etiquetas designam a mesma imagem; se você já tem `latest`, o comando acima só acrescenta a etiqueta. O Docker Desktop precisa estar em execução quando o TreeLevel é iniciado.

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

### Novidades desta versão

- **O modo colisor.** O gerador recebe apenas os feixes e a energia, nunca um estado final: produz a mistura inteira, como uma máquina real, e o TreeLevel conta em seguida os eventos que trazem a assinatura do processo desenhado — o que mede uma seção de choque em vez de calculá-la. Seis famílias de canais, entre elas a QCD dura, a fotoprodução e a seção de choque total. Por enquanto, Pythia 8.
- **Duas configurações de máquina combinadas.** Um feixe de léptons entra como lépton ou como o fluxo de fótons que ele irradia, nunca os dois em uma mesma geração: o motor gera os dois e guarda de cada um a parte que lhe cabe segundo sua seção de choque.
- **A seção de choque informada é a de depois do último evento.** O Pythia normaliza após o seu laço; o driver escrevia a estimativa corrente, errada em 12 % com algumas centenas de eventos.
- **O programa se chama TreeLevel Tools**, e o executável `treelevel-tools.exe`. Ele não traz mais apenas motores Monte Carlo.

### Também

- Trabalhos numerados, com data e hora e guardados em uma lista, que o TreeLevel reabre.
- Seção de choque lida onde cada gerador a coloca: linha `C` do Asciiv3, atributo `GenCrossSection`, ou tabela de integração.

### Problema conhecido

Se o Sherpa roda em uma instalação WSL própria em vez da imagem, sua seção de choque com feixes de léptons sai alta demais: a radiação inicial de QED continua ligada, e e⁻e⁺ → b b̄ a 200 GeV dá uns quinze picobarns em vez de 3,2. Pela imagem `ghcr.io/gpasa/treelevel-tools`, isso está corrigido.

O TreeLevel Tools é GPL v3 ou posterior (veja `LICENSE.txt` no arquivo); cada gerador mantém sua própria licença, abaixo.
