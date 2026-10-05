TreeLevel 无法包含的 GPL 工具，在您自己的机器上运行——任何东西都不会离开这台机器。TreeLevel 运行在沙盒中，不启动任何程序；本软件包就是被允许运行这些工具的那一方。

- 适用于 **Apple Silicon 与 Intel** Mac，macOS 13 或更高版本。
- 将 `TreeLevel Tools.app` 拖入 `/Applications` 并启动一次。
- 四个生成器**已内置**，无需再安装任何东西：
  - **Pythia 8** 与 **Herwig 7** 为 TreeLevel 在两个轻子之间产生的事件补全物理：簇射、强子化、衰变。**Pythia 8** 还驱动“加速器”来源：两束束流、一个能量，以及碰撞产生的一切。
  - **Sherpa 3** 与 **CalcHEP 3** 自行计算图所描述的过程。
- 之后 TreeLevel 会在“生成”工作区中提供它们。

所有生成器的卡片都由与 Docker 镜像中相同的 C++ 引擎写出：同一个作业在 Mac 和 Linux 上得到同一张卡片。

**WHIZARD 3** 不包含在内：它用 gfortran 编译每个过程，而 macOS 和 Xcode 都不提供 gfortran。有两种方式获得它，在 TreeLevel Tools 窗口中勾选：

- **Docker 镜像** `ghcr.io/gpasa/treelevel-tools:latest`，其中包含全部五个工具；勾选后由它运行**所有**作业，这里内置的生成器不再参与；
- 您**自己的安装**（MacPorts、Homebrew），如果有的话。

默认两者都不使用：开箱即用时只提供这里内置的生成器，以便同一份文档在两台机器上得到相同的结果。

由 Apple 签名并公证。校验和见 `SHA256SUMS.txt`。
