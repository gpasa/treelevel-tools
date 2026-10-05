[TreeLevel](https://treelevel.pasahome.org) 的事件生成器，在您自己的机器上运行。TreeLevel 把一个任务写入本地文件夹；本程序将其交给 **Pythia 8**、**Herwig 7**、**Sherpa 3**、**WHIZARD 3** 或 **CalcHEP 3** — 对其事件进行簇射与强子化，或生成加速器的完整碰撞 — 再以 HepMC3 格式写回结果，由 TreeLevel 读取。不经过网络，无需账户，没有任何服务。在 iPad 上，由编译为 WebAssembly 的 Pythia 8 承担同样的角色，从[其发布页](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia)下载。

它之所以单独分发，是因为这些生成器采用 **GPL** 许可：本仓库为 GPL v3，TreeLevel 不包含它们的任何代码。

| 系统 | 下载 | 包含内容 |
|---|---|---|
| **macOS** 13 或更高版本，Apple Silicon 与 Intel | [TreeLevelTools-0.5.0.dmg](https://github.com/gpasa/treelevel-tools/releases/download/mac-0.5.0/TreeLevelTools-0.5.0.dmg) | Pythia 8、Herwig 7、Sherpa 3 与 CalcHEP 3，可直接运行 |
| **Windows** 10 与 11 | [x64](https://github.com/gpasa/treelevel-tools/releases/download/win-0.5.1/TreeLevelTools-0.5.1-x64.zip) · [ARM64](https://github.com/gpasa/treelevel-tools/releases/download/win-0.5.1/TreeLevelTools-0.5.1-arm64.zip) | Pythia 8；其他生成器通过 Docker 镜像 |
| **iPad** | 在 TreeLevel 的设置中（[发布页](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia)） | WebAssembly 版 Pythia 8 |
| **Docker**，任何系统 | `docker pull ghcr.io/gpasa/treelevel-tools:latest` | 全部五个生成器，包括 WHIZARD 3 |

**Mac**：将 `TreeLevel Tools.app` 拖入 `/Applications` 并启动一次；之后 TreeLevel 会在“生成”工作区中提供这些生成器。**Windows**：将压缩包解压到 `%LOCALAPPDATA%\Programs`。**iPad**：设置中的 *Pythia 8 模块* 卡片负责下载并校验每个文件。**Docker**：镜像存在时，TreeLevel Tools 在其中运行没有任何模块提供的生成器（在 Mac 上，勾选一个复选框即可将所有任务交给镜像）。
