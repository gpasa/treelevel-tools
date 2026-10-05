Las herramientas bajo licencia GPL que TreeLevel no puede contener, en su máquina — nada sale de ella.
TreeLevel funciona en un sandbox y no lanza ningún programa; este paquete es lo que tiene permiso para ejecutarlas.

- Arrastrar `TreeLevel Tools.app` a `/Applications` y abrirla una vez.
- Cuatro generadores están **ya dentro**, nada más que instalar:
  - **Pythia 8** y **Herwig 7** visten los sucesos de TreeLevel: cascada, hadronización, desintegraciones.
  - **Sherpa 3** y **CalcHEP 3** no tienen lector Les Houches: calculan por sí mismos el proceso descrito
    por el diagrama, a partir de una descripción del proceso (haces, energías, estado final, órdenes de acoplamiento)
    que el protocolo les transmite junto a los sucesos.
- TreeLevel los ofrece entonces en el espacio Generación.

**WHIZARD 3** no está incluido: compila cada proceso con gfortran, que ni macOS ni Xcode proporcionan. Dos maneras de
tenerlo, ambas se marcan en la ventana de TreeLevel Tools:

- la **imagen Docker** `ghcr.io/gpasa/treelevel-tools:0.3.0`, que lleva las cinco herramientas en un entorno coherente;
- su **propia instalación** (MacPorts, Homebrew), si tiene una.

Ninguna de las dos se usa por defecto: de entrada solo se ofrecen los generadores incluidos aquí, para que un
mismo documento dé el mismo resultado en dos máquinas.

### Medido: e⁻e⁺ → W⁺W⁻ a 200 GeV

| motor | σ |
|---|---|
| TreeLevel | 19,22 pb |
| WHIZARD 3.1.6 | 19,441 ± 0,006 pb |
| CalcHEP 3.9.2 | 20,42 pb |
| Sherpa 3.0.5 | 18,2 ± 1,1 pb |

Las diferencias se deben a la elección del esquema de acoplamientos, no a errores.

### También

- Trabajos numerados, con fecha y hora y conservados en una lista.
- Rutas de bibliotecas de un módulo corregidas en tiempo de ejecución: un módulo compilado en otro lugar funciona sin retocar sus binarios.
- Sección eficaz leída allí donde cada generador la pone: línea `C` de Asciiv3, atributo `GenCrossSection`, o tabla de integración.

El README da las recetas para compilar los módulos en macOS 26, con las cuatro o cinco trampas que la
cadena de herramientas de 2026 reserva a códigos de 2023.

Firmado y notarizado por Apple. Sumas de control en `SHA256SUMS.txt`.
