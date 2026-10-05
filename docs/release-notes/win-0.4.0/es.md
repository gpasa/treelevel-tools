El motor que hace funcionar los generadores Monte Carlo para TreeLevel 1.3 en Windows. Se instala desplegando el archivo en `%LOCALAPPDATA%\Programs` — sin instalador, nada en el registro. **Para actualizar** una versión anterior: cierre TreeLevel y despliegue el archivo en el mismo lugar, sustituyendo los ficheros.

Elija el archivo de su máquina: `arm64` para un PC Copilot+ o una tableta ARM, `x64` en todos los demás casos. En caso de duda, el x64 funciona también en ARM, en emulación.

**Lo que contiene el archivo**: `treelevel-tools.exe`, que TreeLevel lanza; `treelevel-engine.exe`, el motor que escribe la tarjeta de cada generador y lo controla; el módulo Pythia 8 compilado para esta arquitectura; `CREDITS.md`. Herwig, Sherpa, WHIZARD y CalcHEP pasan por la imagen de contenedor, que exige Docker Desktop:

```
docker pull ghcr.io/gpasa/treelevel-tools:0.4.0
```

No hay nada más que hacer: TreeLevel crea por sí mismo un contenedor efímero para cada trabajo. Docker Desktop debe estar en marcha cuando TreeLevel arranca; los generadores de la imagen aparecen entonces, marcados «(Docker)».

**El motor no tiene ventana.** Es TreeLevel quien lo lanza, cada vez que hace falta. Si hace doble clic en `treelevel-tools.exe`, Windows SmartScreen advierte de una aplicación no reconocida — el motor no está firmado — y, superada la advertencia, una consola muestra sus instrucciones de uso y se cierra. Es normal, y no tiene ningún efecto.

### Qué cambia

- **Un solo motor para Windows, el Mac y la imagen.** Las tarjetas de los generadores ya solo se escriben una vez, en C++ (`Backends/engine`), y el mismo programa funciona aquí, en el Mac y en el contenedor. La parte de Windows ya solo se encarga de encontrar Docker, la imagen y el módulo Pythia.
- **«Tout faire tourner dans l'image Docker»**, una casilla de los Ajustes de TreeLevel 1.3. Marcada, la imagen ejecuta todos los trabajos, Pythia incluido, y no se ofrece nada cuando faltan Docker o la imagen. Desmarcada, Pythia funciona en nativo y el resto pasa por la imagen.
- **Lo que registra el experimento**: la fuente Máquina de TreeLevel 1.3 elige un fenómeno — todo lo que ve el detector, la dispersión por un fotón, la aniquilación en γ*/Z, el W intercambiado o producido, los pares de bosones, los jets, la fotoproducción, las colisiones blandas —, y el motor lo abre con el umbral que le conviene (Q² para las dispersiones, p_T para los jets).
- **Dónde nació cada partícula**: el controlador de Pythia escribe la posición de los vértices, y el proceso duro de cada suceso; TreeLevel los dibuja y filtra según ellos.
- **Pythia 8.318** en todas partes, con sus tunes (`Monash 2013`, `A14`…) traducidos a números de Pythia.
- **Rutas con acentos**: una carpeta de trabajo bajo un nombre de usuario con acentos se abre como cualquier otra.
- Retirada: la vía WSL (Herwig o Sherpa instalados a mano en una distribución) — Docker es la vía prevista.

TreeLevel Tools está bajo GPL v3 o posterior (véase `LICENSE.txt` en el archivo); cada generador conserva su propia licencia — véase `CREDITS.md`, y más abajo.
