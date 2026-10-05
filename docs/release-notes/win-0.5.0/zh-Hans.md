本引擎为 Windows 上的 TreeLevel 1.4（以及仍然支持的 1.3）运行蒙特卡罗生成器。安装方法是把压缩包解压到 `%LOCALAPPDATA%\Programs`——没有安装程序，注册表里什么也不留。**要更新**旧版本：关闭 TreeLevel，把压缩包解压到同一位置，替换原有文件。

选择与您的机器相符的压缩包：Copilot+ PC 或 ARM 平板用 `arm64`，其他情况一律用 `x64`。拿不准时，x64 版本在 ARM 上也能以模拟方式运行。

**压缩包内容**：`treelevel-tools.exe`，由 TreeLevel 启动；`treelevel-engine.exe`，为每个生成器写出卡片并驱动其运行的引擎；为该架构编译的 Pythia 8 模块；`CREDITS.md`。Herwig、Sherpa、WHIZARD 与 CalcHEP 经由容器镜像运行，这需要 Docker Desktop：

```
docker pull ghcr.io/gpasa/treelevel-tools:latest
```

无需其他操作：TreeLevel 会为每个作业自行创建一个临时容器。TreeLevel 启动时 Docker Desktop 必须已在运行；镜像中的生成器随即出现，并标有“(Docker)”。

**引擎没有窗口**。它由 TreeLevel 在需要时启动。如果您双击 `treelevel-tools.exe`，Windows SmartScreen 会警告这是一个无法识别的应用——引擎没有签名——越过警告后，会有一个控制台显示其使用说明，随即关闭。这是正常的，也不会产生任何影响。

### 变更内容

- **飞米尺度的相互作用区**。为 TreeLevel 1.4，Pythia 驱动程序能够把每个部分子相互作用放在两个强子的重叠区内，把每个强子放在其弦断裂的地方（作业键 `spaceTime`：`PartonVertex:setVertex`、`Fragmentation:setVertices`）。它为每个部分子写出其色流与 Pythia 状态，并为每个不在其顶点处诞生的粒子写出它自己的诞生位置——这正是 TreeLevel 1.4 的放大剖面与 3D 视图所绘制的内容。这是生成器的模型，并非任何测量结果。
- **束流对撞区只偏移一次**。有了这些位置，Pythia 原先会把强子偏移两次；驱动程序现在自行放置事件，只用一个矢量。没有该键时，一切不变。
- **引擎会说明自己能做什么**：`treelevel-tools capabilities` 声明 `spaceTimeGenerators`（其驱动程序回答“spacetime”时的原生 Pythia，以及镜像所声明的内容）。只有当其中列有相应条目时，TreeLevel 1.4 才会显示复选框“相互作用区中的位置”。
- **兼容 TreeLevel 1.3**：不带 `spaceTime` 键的作业，运行方式与 0.4.0 完全相同。
- **Docker 镜像 0.5 随后跟进**：在此之前，`:latest` 是 0.4.0 镜像，Herwig、Sherpa、WHIZARD 与 CalcHEP 在其中照常运行；相互作用区由本压缩包中的原生 Pythia 提供。
- **与 `mac-0.5.0` 相同的引擎**：相同的 Pythia 驱动程序（`Backends/pythia/main.cpp`）、相同的作业键、写出相同的属性。
