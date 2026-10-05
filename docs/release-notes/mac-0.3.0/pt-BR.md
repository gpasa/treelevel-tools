As ferramentas sob licença GPL que o TreeLevel não pode conter, na sua máquina — nada sai dela. O TreeLevel roda em
sandbox e não inicia nenhum programa; este pacote é o que tem permissão para executá-las.

- Arraste `TreeLevel Tools.app` para `/Applications` e abra-o uma vez.
- Quatro geradores **já vêm dentro**, nada mais a instalar:
  - **Pythia 8** e **Herwig 7** completam os eventos do TreeLevel: chuveiro, hadronização, decaimentos.
  - **Sherpa 3** e **CalcHEP 3** não têm leitor Les Houches: eles mesmos calculam o processo descrito
    pelo diagrama, a partir de uma descrição do processo (feixes, energias, estado final, ordens de acoplamento)
    que o protocolo lhes transmite junto com os eventos.
- O TreeLevel então os oferece no espaço Geração.

**WHIZARD 3** não está incluído: ele compila cada processo com gfortran, que nem o macOS nem o Xcode fornecem.
Duas maneiras de tê-lo, ambas a marcar na janela do TreeLevel Tools:

- a **imagem Docker** `ghcr.io/gpasa/treelevel-tools:0.3.0`, que traz as cinco ferramentas em um ambiente coerente;
- sua **própria instalação** (MacPorts, Homebrew), se você tiver uma.

Nenhuma das duas é usada por padrão: de início, só os geradores incluídos aqui são oferecidos, para que o mesmo
documento dê o mesmo resultado em duas máquinas.

### Medido: e⁻e⁺ → W⁺W⁻ a 200 GeV

| motor | σ |
|---|---|
| TreeLevel | 19,22 pb |
| WHIZARD 3.1.6 | 19,441 ± 0,006 pb |
| CalcHEP 3.9.2 | 20,42 pb |
| Sherpa 3.0.5 | 18,2 ± 1,1 pb |

As diferenças vêm da escolha do esquema de acoplamentos, não de erros.

### Também

- Trabalhos numerados, com data e hora e guardados em uma lista.
- Caminhos de bibliotecas de um módulo corrigidos em tempo de execução: um módulo compilado em outro lugar funciona sem mexer nos seus binários.
- Seção de choque lida onde cada gerador a coloca: linha `C` do Asciiv3, atributo `GenCrossSection`, ou tabela de integração.

O README traz as receitas de compilação dos módulos no macOS 26, com as quatro ou cinco armadilhas que a
cadeia de ferramentas de 2026 reserva a códigos de 2023.

Assinado e notarizado pela Apple. Somas de verificação em `SHA256SUMS.txt`.
