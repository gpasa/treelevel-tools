Los generadores de sucesos de [TreeLevel](https://treelevel.pasahome.org), en su máquina. TreeLevel escribe un
trabajo en una carpeta local; este programa lo confía a **Pythia 8**, **Herwig 7**, **Sherpa 3**, **WHIZARD 3** o
**CalcHEP 3** — cascada y hadronización de sus sucesos, o colisiones enteras de una máquina — y vuelve a escribir el
resultado en HepMC3, que TreeLevel relee. Nada pasa por la red, ninguna cuenta, ningún servicio. En iPad, Pythia 8
compilado a WebAssembly desempeña el mismo papel, descargado desde
[su release](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia).

Se distribuye por separado porque estos generadores están bajo licencia **GPL**: este repositorio es GPL v3, y
TreeLevel no contiene nada de su código.

| sistema | descargar | lo que contiene |
|---|---|---|
| **macOS** 13 o posterior, Apple Silicon e Intel | [TreeLevelTools-0.5.0.dmg](https://github.com/gpasa/treelevel-tools/releases/download/mac-0.5.0/TreeLevelTools-0.5.0.dmg) | Pythia 8, Herwig 7, Sherpa 3 y CalcHEP 3, listos para funcionar |
| **Windows** 10 y 11 | [x64](https://github.com/gpasa/treelevel-tools/releases/download/win-0.5.1/TreeLevelTools-0.5.1-x64.zip) · [ARM64](https://github.com/gpasa/treelevel-tools/releases/download/win-0.5.1/TreeLevelTools-0.5.1-arm64.zip) | Pythia 8; los demás mediante la imagen Docker |
| **iPad** | desde los ajustes de TreeLevel ([la release](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia)) | Pythia 8 en WebAssembly |
| **Docker**, cualquier sistema | `docker pull ghcr.io/gpasa/treelevel-tools:latest` | los cinco generadores, WHIZARD 3 incluido |

**Mac**: arrastrar `TreeLevel Tools.app` a `/Applications` y abrirla una vez; TreeLevel ofrece entonces sus
generadores en el espacio Generación. **Windows**: descomprimir el archivo en `%LOCALAPPDATA%\Programs`. **iPad**: la
tarjeta *Módulo Pythia 8* de los ajustes lo descarga y comprueba cada archivo. **Docker**: con la imagen presente,
TreeLevel Tools ejecuta en ella los generadores que ningún módulo ofrece (en el Mac, una casilla le confía todos los
trabajos).
