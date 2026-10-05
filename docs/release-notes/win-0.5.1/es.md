El motor que hace funcionar los generadores Monte Carlo para TreeLevel 1.4 en Windows (y todavía para 1.3). Se instala desplegando el archivo en `%LOCALAPPDATA%\Programs` — sin instalador, nada en el registro. **Para actualizar** una versión anterior: cierre TreeLevel y despliegue el archivo en el mismo lugar, sustituyendo los ficheros.

Elija el archivo de su máquina: `arm64` para un PC Copilot+ o una tableta ARM, `x64` en todos los demás casos. En caso de duda, el x64 funciona también en ARM, en emulación.

**Lo que contiene el archivo**: `treelevel-tools.exe`, que TreeLevel lanza; `treelevel-engine.exe`, el motor que escribe la tarjeta de cada generador y lo controla; el módulo Pythia 8 compilado para esta arquitectura; `CREDITS.md`. Herwig, Sherpa, WHIZARD y CalcHEP pasan por la imagen de contenedor, que exige Docker Desktop:

```
docker pull ghcr.io/gpasa/treelevel-tools:latest
```

No hay nada más que hacer: TreeLevel crea por sí mismo un contenedor efímero para cada trabajo. Docker Desktop debe estar en marcha cuando TreeLevel arranca; los generadores de la imagen aparecen entonces, marcados «(Docker)».

**El motor no tiene ventana.** Es TreeLevel quien lo lanza, cada vez que hace falta. Si hace doble clic en `treelevel-tools.exe`, Windows SmartScreen advierte de una aplicación no reconocida — el motor no está firmado — y, superada la advertencia, una consola muestra sus instrucciones de uso y se cierra. Es normal, y no tiene ningún efecto.

### Qué cambia

- **El host pide la imagen 0.5.0.** Está publicada y `:latest` apunta a ella; el motor de Windows busca primero `ghcr.io/gpasa/treelevel-tools:0.5.0`, luego `:latest`, como antes. Con la imagen 0.5.0, la casilla «Tout faire tourner dans l'image Docker» da también la zona de interacción (la imagen anuncia `spaceTimeGenerators`).
- **Para aprovecharlo con Docker**: `docker pull ghcr.io/gpasa/treelevel-tools:latest` (o `:0.5.0`) sustituye la imagen 0.4.0.
- **Nada más cambia**: el mismo controlador de Pythia y las mismas claves del trabajo que `win-0.5.0`; compatible con TreeLevel 1.3 y 1.4.
