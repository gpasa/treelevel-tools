TreeLevel 无法包含的 GPL 工具，在您自己的机器上运行——任何东西都不会离开这台机器。TreeLevel 运行在沙盒中，不启动任何程序；本软件包就是被允许运行这些工具的那一方。

- 将 `TreeLevel Tools.app` 拖入 `/Applications` 并启动一次。
- 四个生成器**已内置**，无需再安装任何东西：
  - **Pythia 8** 与 **Herwig 7** 为 TreeLevel 的事件补全物理：簇射、强子化、衰变。
  - **Sherpa 3** 与 **CalcHEP 3** 没有 Les Houches 读取器：它们根据协议在事件之外传递给它们的过程描述（束流、能量、末态、耦合阶数），自行计算图所描述的过程。
- 之后 TreeLevel 会在“生成”工作区中提供它们。

**WHIZARD 3** 不包含在内：它用 gfortran 编译每个过程，而 macOS 和 Xcode 都不提供 gfortran。有两种方式获得它，都在 TreeLevel Tools 窗口中勾选：

- **Docker 镜像** `ghcr.io/gpasa/treelevel-tools:0.3.0`，在一个一致的环境中包含全部五个工具；
- 您**自己的安装**（MacPorts、Homebrew），如果有的话。

默认两者都不使用：开箱即用时只提供这里内置的生成器，以便同一份文档在两台机器上得到相同的结果。

### 实测：200 GeV 下的 e⁻e⁺ → W⁺W⁻

| 引擎 | σ |
|---|---|
| TreeLevel | 19.22 pb |
| WHIZARD 3.1.6 | 19.441 ± 0.006 pb |
| CalcHEP 3.9.2 | 20.42 pb |
| Sherpa 3.0.5 | 18.2 ± 1.1 pb |

差异来自耦合方案的选择，而非错误。

### 其他

- 作业带编号、带时间戳并保存在列表中。
- 模块的库路径在运行时修正：在别处编译的模块无需改动其二进制文件即可运行。
- 截面从每个生成器存放它的位置读取：Asciiv3 的 `C` 行、`GenCrossSection` 属性或积分表。

README 给出了在 macOS 26 上编译这些模块的方法，以及 2026 年的工具链给 2023 年的代码设下的四五个陷阱。

由 Apple 签名并公证。校验和见 `SHA256SUMS.txt`。
