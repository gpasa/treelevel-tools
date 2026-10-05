Las herramientas GPL que TreeLevel no puede contener, en su máquina — nada sale de ella. TreeLevel funciona en un
sandbox y no lanza ningún programa; este paquete es lo que tiene permiso para ejecutarlas.

### Novedades de la 0.5.0

- **Pythia 8 sitúa las partículas en la zona de interacción** cuando TreeLevel 1.4 se lo pide (la opción
  «posiciones en la zona de interacción»): dónde nace cada hadrón, a escala del femtómetro, el flujo de color y el
  estado de los partones, y un único desplazamiento de la región luminosa para todo el suceso. TreeLevel lo muestra
  a escala del femtómetro, en los cortes y en 3D.
- TreeLevel 1.3 no pide nada de esto y recibe los mismos sucesos que con la 0.4.0; mismos generadores, mismas
  versiones.
- Probado en un Mac Apple Silicon y en un iMac Intel: cada generador incluido lleva a cabo un trabajo real.

### Instalar

- Para Mac **Apple Silicon e Intel**, macOS 13 o posterior.
- Arrastrar `TreeLevel Tools.app` a `/Applications` y abrirla una vez.
- Cuatro generadores están **ya dentro**, nada más que instalar:
  - **Pythia 8** y **Herwig 7** visten los sucesos de TreeLevel entre dos leptones: cascada, hadronización,
    desintegraciones. **Pythia 8** controla también la fuente Máquina: dos haces, una energía, y todo lo que produce
    la colisión.
  - **Sherpa 3** y **CalcHEP 3** calculan por sí mismos el proceso descrito por el diagrama.
- TreeLevel los ofrece entonces en el espacio Generación.

Las tarjetas de todos los generadores las escribe el mismo motor C++ que dentro de la imagen Docker: un mismo trabajo
da la misma tarjeta en el Mac y en Linux.

**WHIZARD 3** no está incluido: compila cada proceso con gfortran, que ni macOS ni Xcode proporcionan. Dos maneras de
tenerlo, que se marcan en la ventana de TreeLevel Tools:

- la **imagen Docker** `ghcr.io/gpasa/treelevel-tools:latest`, que lleva las cinco herramientas; marcada, ejecuta
  **todos** los trabajos, y los generadores incluidos aquí callan;
- su **propia instalación** (MacPorts, Homebrew), si tiene una.

Ninguna de las dos se usa por defecto: de entrada solo se ofrecen los generadores incluidos aquí, para que un mismo
documento dé el mismo resultado en dos máquinas.

Firmado y notarizado por Apple. Sumas de control en `SHA256SUMS.txt`.
