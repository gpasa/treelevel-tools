El motor que hace funcionar los generadores Monte Carlo para TreeLevel 1.4 en Windows (y todavía para 1.3). Se instala desplegando el archivo en `%LOCALAPPDATA%\Programs` — sin instalador, nada en el registro. **Para actualizar** una versión anterior: cierre TreeLevel y despliegue el archivo en el mismo lugar, sustituyendo los ficheros.

Elija el archivo de su máquina: `arm64` para un PC Copilot+ o una tableta ARM, `x64` en todos los demás casos. En caso de duda, el x64 funciona también en ARM, en emulación.

**Lo que contiene el archivo**: `treelevel-tools.exe`, que TreeLevel lanza; `treelevel-engine.exe`, el motor que escribe la tarjeta de cada generador y lo controla; el módulo Pythia 8 compilado para esta arquitectura; `CREDITS.md`. Herwig, Sherpa, WHIZARD y CalcHEP pasan por la imagen de contenedor, que exige Docker Desktop:

```
docker pull ghcr.io/gpasa/treelevel-tools:latest
```

No hay nada más que hacer: TreeLevel crea por sí mismo un contenedor efímero para cada trabajo. Docker Desktop debe estar en marcha cuando TreeLevel arranca; los generadores de la imagen aparecen entonces, marcados «(Docker)».

**El motor no tiene ventana.** Es TreeLevel quien lo lanza, cada vez que hace falta. Si hace doble clic en `treelevel-tools.exe`, Windows SmartScreen advierte de una aplicación no reconocida — el motor no está firmado — y, superada la advertencia, una consola muestra sus instrucciones de uso y se cierra. Es normal, y no tiene ningún efecto.

### Qué cambia

- **La zona de interacción, a escala del femtómetro.** Para TreeLevel 1.4, el controlador de Pythia sabe situar cada interacción partónica en el solapamiento de los dos hadrones y cada hadrón allí donde se rompió su cuerda (clave `spaceTime` del trabajo: `PartonVertex:setVertex`, `Fragmentation:setVertices`). Escribe para cada partón su flujo de color y su estado Pythia, y para cada partícula nacida en otro lugar que su vértice su propio lugar de nacimiento — lo que dibujan el corte ampliado y la vista 3D de TreeLevel 1.4. Es el modelo del generador, nada medido.
- **Un único desplazamiento de la región luminosa.** Con estas posiciones, Pythia desplazaba los hadrones dos veces; el controlador sitúa ahora el suceso él mismo, con un único vector. Sin la clave, nada cambia.
- **El motor dice lo que sabe hacer**: `treelevel-tools capabilities` anuncia `spaceTimeGenerators` (Pythia nativo cuando su controlador responde «spacetime», y lo que anuncia la imagen). TreeLevel 1.4 solo muestra la casilla «posiciones en la zona de interacción» si figura ahí.
- **Compatible con TreeLevel 1.3**: un trabajo sin la clave `spaceTime` funciona exactamente como con la 0.4.0.
- **La imagen Docker 0.5 vendrá después**: hasta entonces, `:latest` es la imagen 0.4.0, y Herwig, Sherpa, WHIZARD y CalcHEP funcionan en ella como antes; la zona de interacción pasa por el Pythia nativo de este archivo.
- **El mismo motor que `mac-0.5.0`**: el mismo controlador de Pythia (`Backends/pythia/main.cpp`), las mismas claves del trabajo, los mismos atributos escritos.
