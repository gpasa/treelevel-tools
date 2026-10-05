Os geradores de eventos do [TreeLevel](https://treelevel.pasahome.org), na sua máquina. O TreeLevel escreve um
trabalho em uma pasta local; este programa o entrega ao **Pythia 8**, **Herwig 7**, **Sherpa 3**, **WHIZARD 3** ou
**CalcHEP 3** — chuveiro e hadronização de seus eventos, ou colisões inteiras de uma máquina — e grava o resultado
de volta em HepMC3, que o TreeLevel lê. Nada passa pela rede, nenhuma conta, nenhum serviço. No iPad, o Pythia 8
compilado em WebAssembly desempenha o mesmo papel, baixado de [sua release](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia).

Ele é distribuído separadamente porque esses geradores estão sob a licença **GPL**: este repositório é GPL v3, e o
TreeLevel não contém nenhum código deles.

| sistema | baixar | o que contém |
|---|---|---|
| **macOS** 13 ou posterior, Apple Silicon e Intel | [TreeLevelTools-0.5.0.dmg](https://github.com/gpasa/treelevel-tools/releases/download/mac-0.5.0/TreeLevelTools-0.5.0.dmg) | Pythia 8, Herwig 7, Sherpa 3 e CalcHEP 3, prontos para rodar |
| **Windows** 10 e 11 | [x64](https://github.com/gpasa/treelevel-tools/releases/download/win-0.5.1/TreeLevelTools-0.5.1-x64.zip) · [ARM64](https://github.com/gpasa/treelevel-tools/releases/download/win-0.5.1/TreeLevelTools-0.5.1-arm64.zip) | Pythia 8; os outros pela imagem Docker |
| **iPad** | pelos ajustes do TreeLevel ([a release](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia)) | Pythia 8 em WebAssembly |
| **Docker**, qualquer sistema | `docker pull ghcr.io/gpasa/treelevel-tools:latest` | os cinco geradores, WHIZARD 3 incluído |

**Mac**: arraste `TreeLevel Tools.app` para `/Applications` e abra-o uma vez; o TreeLevel passa então a oferecer
seus geradores no espaço Geração. **Windows**: descompacte o arquivo em `%LOCALAPPDATA%\Programs`. **iPad**: o
cartão *Módulo Pythia 8* dos ajustes o baixa e verifica cada arquivo. **Docker**: com a imagem presente, o
TreeLevel Tools executa nela os geradores que nenhum módulo fornece (no Mac, uma caixa de seleção faz com que ela
execute todos os trabalhos).
