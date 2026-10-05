As ferramentas sob licença GPL que o TreeLevel não pode conter, na sua máquina — nada sai dela. O TreeLevel roda em
sandbox e não inicia nenhum programa; este pacote é o que tem permissão para executá-las.

- Para Macs **Apple Silicon e Intel**, macOS 13 ou posterior.
- Arraste `TreeLevel Tools.app` para `/Applications` e abra-o uma vez.
- Quatro geradores **já vêm dentro**, nada mais a instalar:
  - **Pythia 8** e **Herwig 7** completam os eventos do TreeLevel entre dois léptons: chuveiro, hadronização,
    decaimentos. **Pythia 8** também conduz a fonte Máquina: dois feixes, uma energia, e tudo o que a colisão produz.
  - **Sherpa 3** e **CalcHEP 3** calculam eles mesmos o processo descrito pelo diagrama.
- O TreeLevel então os oferece no espaço Geração.

Os cartões de todos os geradores são escritos pelo mesmo motor C++ que o da imagem Docker: o mesmo trabalho dá o
mesmo cartão no Mac e no Linux.

**WHIZARD 3** não está incluído: ele compila cada processo com gfortran, que nem o macOS nem o Xcode fornecem.
Duas maneiras de tê-lo, a marcar na janela do TreeLevel Tools:

- a **imagem Docker** `ghcr.io/gpasa/treelevel-tools:latest`, que traz as cinco ferramentas; marcada, ela conduz
  **todos** os trabalhos, e os geradores incluídos aqui ficam em silêncio;
- sua **própria instalação** (MacPorts, Homebrew), se você tiver uma.

Nenhuma das duas é usada por padrão: de início, só os geradores incluídos aqui são oferecidos, para que o mesmo
documento dê o mesmo resultado em duas máquinas.

Assinado e notarizado pela Apple. Somas de verificação em `SHA256SUMS.txt`.
