> **已被 [0.3.1](https://github.com/gpasa/treelevel-tools/releases/tag/win-0.3.1) 取代**。本版本只识别标签为 `:0.3.0` 的镜像；0.3.1 还接受 `:latest`，即不带版本号的 `docker pull` 所拉取的标签。

本引擎为 Windows 上的 TreeLevel 运行蒙特卡罗生成器。安装方法是把压缩包解压到 `%LOCALAPPDATA%\Programs`——没有安装程序，注册表里什么也不留。

选择与您的机器相符的压缩包：Copilot+ PC 或 ARM 平板用 `arm64`，其他情况一律用 `x64`。拿不准时，x64 版本在 ARM 上也能以模拟方式运行。

**压缩包内容**：引擎以及为该架构编译的 Pythia 8 模块。Herwig、Sherpa、WHIZARD 与 CalcHEP 经由容器镜像 `ghcr.io/gpasa/treelevel-tools` 运行，这需要 Docker。拉取时请**带上版本号**：

```
docker pull ghcr.io/gpasa/treelevel-tools:0.3.0
```

此版本的引擎只识别这个标签：不带版本号拉取的镜像（即 `:latest`）确实在机器上，但 TreeLevel 不会提供其中的生成器。两个标签指向同一个镜像；如果您已经有 `latest`，上面的命令只会添加标签。TreeLevel 启动时 Docker Desktop 必须已在运行。

### 五个生成器，两个家族

**Pythia 8** 与 **Herwig 7** 为 TreeLevel 交给它们的部分子事件补全物理：簇射、强子化、衰变。

**Sherpa 3**、**WHIZARD 3** 与 **CalcHEP 3** 没有 Les Houches 读取器——它们自行计算图所描述的过程。因此，协议在事件之外还向它们传递过程的描述（束流、能量、末态、耦合阶数）。

### 实测：200 GeV 下的 e⁻e⁺ → W⁺W⁻

| 引擎 | σ |
|---|---|
| TreeLevel | 19.22 pb |
| WHIZARD 3.1.6 | 19.441 ± 0.006 pb |
| CalcHEP 3.9.2 | 20.42 pb |
| Sherpa 3.0.5 | 18.2 ± 1.1 pb |

差异来自耦合方案的选择，而非错误。

### 本版本新增

- **对撞机模式**。生成器只接收束流和能量，从不接收末态：它像一台真正的加速器那样产生完整的混合，TreeLevel 随后统计带有所画过程特征的事件——这是在测量截面，而不是计算截面。共有六类道，其中包括硬 QCD、光致产生和总截面。目前仅限 Pythia 8。
- **两种加速器配置的组合**。轻子束流要么作为轻子进入，要么作为它所辐射的光子流进入，从不在同一次抽样中兼为两者：引擎对两者都进行抽样，并从每一种中保留其截面所对应的份额。
- **报告的截面是最后一个事件之后的值**。Pythia 在其循环结束后进行归一化；驱动程序原先写出的是当前的估计值，在几百个事件上偏差 12%。
- **程序名为 TreeLevel Tools**，可执行文件为 `treelevel-tools.exe`。它承载的已不只是蒙特卡罗引擎。

### 其他

- 作业带编号、带时间戳并保存在列表中，可由 TreeLevel 重新打开。
- 截面从每个生成器存放它的位置读取：Asciiv3 的 `C` 行、`GenCrossSection` 属性或积分表。

### 已知问题

如果 Sherpa 在个人的 WSL 安装中运行，而不是在镜像中运行，它在轻子束流上的截面会偏高：QED 初态辐射在那里仍处于开启状态，200 GeV 下的 e⁻e⁺ → b b̄ 给出约十五皮靶，而非 3.2。通过镜像 `ghcr.io/gpasa/treelevel-tools` 运行时，此问题已修正。

TreeLevel Tools 以 GPL v3 或更高版本发布（见压缩包中的 `LICENSE.txt`）；每个生成器保留其自身的许可证，见下文。
