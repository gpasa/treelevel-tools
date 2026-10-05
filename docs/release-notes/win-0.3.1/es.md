El motor que hace funcionar los generadores Monte Carlo para TreeLevel en Windows. Se instala desplegando el archivo en `%LOCALAPPDATA%\Programs` — sin instalador, nada en el registro. **Para actualizar** una versión anterior: cierre TreeLevel y despliegue el archivo en el mismo lugar, sustituyendo los ficheros.

Elija el archivo de su máquina: `arm64` para un PC Copilot+ o una tableta ARM, `x64` en todos los demás casos. En caso de duda, el x64 funciona también en ARM, en emulación.

**Lo que contiene el archivo**: el motor y el módulo Pythia 8 compilado para esta arquitectura. Herwig, Sherpa, WHIZARD y CalcHEP pasan por la imagen de contenedor, que exige Docker Desktop:

```
docker pull ghcr.io/gpasa/treelevel-tools
```

No hay nada más que hacer: TreeLevel crea por sí mismo un contenedor efímero para cada trabajo. Docker Desktop debe estar en marcha cuando TreeLevel arranca; los generadores de la imagen aparecen entonces, marcados «(Docker)».

**El motor no tiene ventana.** Es TreeLevel quien lo lanza, cada vez que hace falta. Si hace doble clic en `treelevel-tools.exe`, Windows SmartScreen advierte de una aplicación no reconocida — el motor no está firmado — y, superada la advertencia, una consola muestra sus instrucciones de uso y se cierra. Es normal, y no tiene ningún efecto: nunca tiene que lanzarlo usted mismo.

### Correcciones de esta versión

- **Se reconoce la imagen descargada sin número.** La 0.3.0 solo reconocía la etiqueta `:0.3.0`; ahora bien, el comando que propone la página del paquete, y el que escribe todo el mundo, descarga `:latest`. La imagen estaba en la máquina, respondía cuando se lanzaba a mano, y sin embargo TreeLevel solo ofrecía Pythia. Las dos etiquetas designan la misma imagen, y ahora se reconocen ambas.
- **Sherpa sobre haces de leptones**, cuando funciona fuera de la imagen: su sección eficaz ya no está inflada por la radiación inicial de QED (unos quince picobarns en lugar de 3,2 para e⁻e⁺ → b b̄ a 200 GeV). La vía que dependía de ello — Sherpa instalado por uno mismo en WSL — se retirará en una próxima versión: Docker es la vía prevista.

### Cinco generadores, dos familias

**Pythia 8** y **Herwig 7** visten los sucesos partónicos que TreeLevel les da: cascada, hadronización, desintegraciones.

**Sherpa 3**, **WHIZARD 3** y **CalcHEP 3** no tienen lector Les Houches — calculan por sí mismos el proceso descrito por el diagrama. Por eso el protocolo les transmite una descripción del proceso (haces, energías, estado final, órdenes de acoplamiento) junto a los sucesos.

### Medido: e⁻e⁺ → W⁺W⁻ a 200 GeV

| motor | σ |
|---|---|
| TreeLevel | 19,22 pb |
| WHIZARD 3.1.6 | 19,441 ± 0,006 pb |
| CalcHEP 3.9.2 | 20,42 pb |
| Sherpa 3.0.5 | 18,2 ± 1,1 pb |

Las diferencias se deben a la elección del esquema de acoplamientos, no a errores.

### Recordatorio: lo que trajo la 0.3.0

- **El modo colisionador.** El generador solo recibe los haces y la energía, nunca un estado final: produce la mezcla entera, como una máquina real, y TreeLevel cuenta después los sucesos que llevan la firma del proceso dibujado — lo que mide una sección eficaz en lugar de calcularla. Seis familias de canales, entre ellas la QCD dura, la fotoproducción y la sección eficaz total. Por ahora, Pythia 8.
- **Dos configuraciones de máquina combinadas.** Un haz de leptones entra como leptón o como el flujo de fotones que radia, nunca ambos en una misma generación: el motor genera los dos y conserva de cada uno la parte que le corresponde según su sección eficaz.
- **La sección eficaz indicada es la posterior al último suceso.** Pythia normaliza después de su bucle; el controlador escribía la estimación en curso, errónea en un 12 % sobre unos cientos de sucesos.
- **El programa se llama TreeLevel Tools**, y el ejecutable `treelevel-tools.exe`.
- Trabajos numerados, con fecha y hora y conservados en una lista, que TreeLevel vuelve a abrir; sección eficaz leída allí donde cada generador la pone.

TreeLevel Tools está bajo GPL v3 o posterior (véase `LICENSE.txt` en el archivo); cada generador conserva su propia licencia, más abajo.
