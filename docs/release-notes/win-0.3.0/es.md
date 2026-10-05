> **Sustituida por la [0.3.1](https://github.com/gpasa/treelevel-tools/releases/tag/win-0.3.1).** Esta solo reconoce la imagen con la etiqueta `:0.3.0`; la 0.3.1 acepta también `:latest`, la que descarga `docker pull` sin número.

El motor que hace funcionar los generadores Monte Carlo para TreeLevel en Windows. Se instala desplegando el archivo en `%LOCALAPPDATA%\Programs` — sin instalador, nada en el registro.

Elija el archivo de su máquina: `arm64` para un PC Copilot+ o una tableta ARM, `x64` en todos los demás casos. En caso de duda, el x64 funciona también en ARM, en emulación.

**Lo que contiene el archivo**: el motor y el módulo Pythia 8 compilado para esta arquitectura. Herwig, Sherpa, WHIZARD y CalcHEP pasan por la imagen de contenedor `ghcr.io/gpasa/treelevel-tools`, que exige Docker. Descárguela **con su número**:

```
docker pull ghcr.io/gpasa/treelevel-tools:0.3.0
```

Esta versión del motor solo reconoce esa etiqueta: una imagen descargada sin número (es decir, `:latest`) está en la máquina, pero TreeLevel no ofrece sus generadores. Las dos etiquetas designan la misma imagen; si ya tiene `latest`, el comando anterior solo añade la etiqueta. Docker Desktop debe estar en marcha cuando TreeLevel arranca.

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

### Novedades de esta versión

- **El modo colisionador.** El generador solo recibe los haces y la energía, nunca un estado final: produce la mezcla entera, como una máquina real, y TreeLevel cuenta después los sucesos que llevan la firma del proceso dibujado — lo que mide una sección eficaz en lugar de calcularla. Seis familias de canales, entre ellas la QCD dura, la fotoproducción y la sección eficaz total. Por ahora, Pythia 8.
- **Dos configuraciones de máquina combinadas.** Un haz de leptones entra como leptón o como el flujo de fotones que radia, nunca ambos en una misma generación: el motor genera los dos y conserva de cada uno la parte que le corresponde según su sección eficaz.
- **La sección eficaz indicada es la posterior al último suceso.** Pythia normaliza después de su bucle; el controlador escribía la estimación en curso, errónea en un 12 % sobre unos cientos de sucesos.
- **El programa se llama TreeLevel Tools**, y el ejecutable `treelevel-tools.exe`. Ya no lleva solo motores Monte Carlo.

### También

- Trabajos numerados, con fecha y hora y conservados en una lista, que TreeLevel vuelve a abrir.
- Sección eficaz leída allí donde cada generador la pone: línea `C` de Asciiv3, atributo `GenCrossSection`, o tabla de integración.

### Problema conocido

Si Sherpa funciona en una instalación WSL propia en lugar de en la imagen, su sección eficaz sobre haces de leptones sale demasiado alta: la radiación inicial de QED sigue activada, y e⁻e⁺ → b b̄ a 200 GeV da unos quince picobarns en lugar de 3,2. Mediante la imagen `ghcr.io/gpasa/treelevel-tools`, está corregido.

TreeLevel Tools está bajo GPL v3 o posterior (véase `LICENSE.txt` en el archivo); cada generador conserva su propia licencia, más abajo.
