本引擎为 Windows 上的 TreeLevel 1.3 运行蒙特卡罗生成器。安装方法是把压缩包解压到 `%LOCALAPPDATA%\Programs`——没有安装程序，注册表里什么也不留。**要更新**旧版本：关闭 TreeLevel，把压缩包解压到同一位置，替换原有文件。

选择与您的机器相符的压缩包：Copilot+ PC 或 ARM 平板用 `arm64`，其他情况一律用 `x64`。拿不准时，x64 版本在 ARM 上也能以模拟方式运行。

**压缩包内容**：`treelevel-tools.exe`，由 TreeLevel 启动；`treelevel-engine.exe`，为每个生成器写出卡片并驱动其运行的引擎；为该架构编译的 Pythia 8 模块；`CREDITS.md`。Herwig、Sherpa、WHIZARD 与 CalcHEP 经由容器镜像运行，这需要 Docker Desktop：

```
docker pull ghcr.io/gpasa/treelevel-tools:0.4.0
```

无需其他操作：TreeLevel 会为每个作业自行创建一个临时容器。TreeLevel 启动时 Docker Desktop 必须已在运行；镜像中的生成器随即出现，并标有“(Docker)”。

**引擎没有窗口**。它由 TreeLevel 在需要时启动。如果您双击 `treelevel-tools.exe`，Windows SmartScreen 会警告这是一个无法识别的应用——引擎没有签名——越过警告后，会有一个控制台显示其使用说明，随即关闭。这是正常的，也不会产生任何影响。

### 变更内容

- **Windows、Mac 与镜像共用一个引擎**。生成器的卡片现在只写出一次，用 C++（`Backends/engine`），同一个程序在这里、在 Mac 上和在容器中运行。Windows 部分只负责找到 Docker、镜像和 Pythia 模块。
- **“Tout faire tourner dans l'image Docker”**，TreeLevel 1.3 设置中的一个复选框。勾选后，由镜像运行所有作业，包括 Pythia；Docker 或镜像缺失时不提供任何生成器。取消勾选时，Pythia 以原生方式运行，其余经由镜像。
- **实验记录的内容**：TreeLevel 1.3 的“加速器”来源选择一种现象——探测器所见的一切、经光子散射、湮灭为 γ*/Z、交换或产生的 W、玻色子对、喷注、光致产生、软碰撞——，引擎以适合它的阈值开启它（散射用 Q²，喷注用 p_T）。
- **每个粒子在哪里诞生**：Pythia 驱动程序写出顶点的位置以及每个事件的硬过程；TreeLevel 绘制它们，并可据此筛选。
- **Pythia 8.318** 全面采用，其 tune（`Monash 2013`、`A14`…）转换为 Pythia 的编号。
- **带重音的路径**：位于带重音用户名之下的作业文件夹，也能像其他文件夹一样打开。
- 已移除：WSL 途径（在某个发行版中手动安装的 Herwig 或 Sherpa）——Docker 是预定的途径。

TreeLevel Tools 以 GPL v3 或更高版本发布（见压缩包中的 `LICENSE.txt`）；每个生成器保留其自身的许可证——见 `CREDITS.md` 及下文。
