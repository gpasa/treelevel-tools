本引擎为 Windows 上的 TreeLevel 1.4（以及仍然支持的 1.3）运行蒙特卡罗生成器。安装方法是把压缩包解压到 `%LOCALAPPDATA%\Programs`——没有安装程序，注册表里什么也不留。**要更新**旧版本：关闭 TreeLevel，把压缩包解压到同一位置，替换原有文件。

选择与您的机器相符的压缩包：Copilot+ PC 或 ARM 平板用 `arm64`，其他情况一律用 `x64`。拿不准时，x64 版本在 ARM 上也能以模拟方式运行。

**压缩包内容**：`treelevel-tools.exe`，由 TreeLevel 启动；`treelevel-engine.exe`，为每个生成器写出卡片并驱动其运行的引擎；为该架构编译的 Pythia 8 模块；`CREDITS.md`。Herwig、Sherpa、WHIZARD 与 CalcHEP 经由容器镜像运行，这需要 Docker Desktop：

```
docker pull ghcr.io/gpasa/treelevel-tools:latest
```

无需其他操作：TreeLevel 会为每个作业自行创建一个临时容器。TreeLevel 启动时 Docker Desktop 必须已在运行；镜像中的生成器随即出现，并标有“(Docker)”。

**引擎没有窗口**。它由 TreeLevel 在需要时启动。如果您双击 `treelevel-tools.exe`，Windows SmartScreen 会警告这是一个无法识别的应用——引擎没有签名——越过警告后，会有一个控制台显示其使用说明，随即关闭。这是正常的，也不会产生任何影响。

### 变更内容

- **宿主程序请求 0.5.0 镜像**。该镜像已发布，`:latest` 指向它；Windows 引擎与以前一样，先查找 `ghcr.io/gpasa/treelevel-tools:0.5.0`，再查找 `:latest`。使用 0.5.0 镜像时，复选框“Tout faire tourner dans l'image Docker”也能提供相互作用区（镜像声明了 `spaceTimeGenerators`）。
- **要在 Docker 中使用这一功能**：`docker pull ghcr.io/gpasa/treelevel-tools:latest`（或 `:0.5.0`）会替换 0.4.0 镜像。
- **其余不变**：Pythia 驱动程序与作业键均与 `win-0.5.0` 相同；兼容 TreeLevel 1.3 与 1.4。
