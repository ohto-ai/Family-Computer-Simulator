# Family Computer Simulator

一个使用 C++17 从零实现的 NES / Famicom（FC）模拟器，前端基于 Qt 5.15 Widgets。项目包含 6502 CPU、PPU、手柄输入和 iNES 卡带加载，适合用来学习模拟器与主机硬件的实现原理。

## 功能

- 6502 CPU 指令解释执行
- PPU 图形渲染
- iNES 卡带加载
- Mapper 0 / 1 / 2 支持
- 双人手柄输入（键盘映射）
- Qt 图形界面，按固定帧率驱动模拟
- 自带 `src/tank.nes` 测试 ROM
- 当前未实现 APU 音频

## 构建

### 环境要求

- Windows 10 / 11 x64
- Visual Studio 2022（项目使用 `v143` 工具集，C++17）
- Qt 5.15.2 `msvc2019_64`
- Qt Visual Studio Tools（`QtVS_v304`）

### 步骤

1. 用 Visual Studio 打开 [`Family Computer Simulator.sln`](Family%20Computer%20Simulator.sln)。
2. 在 Qt VS Tools 中确认 Qt 版本为 `5.15.2_msvc2019_64`。
3. 选择 `Release | x64` 或 `Debug | x64` 构建并运行。

也可以在 Qt Creator 中打开 `src/FCWin.pro.user` 对应的工程配置进行构建。

## 运行

程序启动时会从**当前工作目录**读取 `tank.nes`：

```cpp
cartridge.read_from_file("tank.nes");
```

因此请确保运行目录中存在该文件（仓库中的 `src/tank.nes` 可复制到输出目录），或修改 `src/main.cpp` 中的路径以加载其他 iNES ROM。

## 操作

| 按键 | 功能 |
|---|---|
| `W` `A` `S` `D` | 玩家 1 方向键 |
| `K` / `J` | 玩家 1 A / B |
| `Space` / `Shift` | 玩家 1 Start / Select |
| `L` `,` `.` `/` | 玩家 2 方向键（上 / 左 / 下 / 右） |
| `X` / `Z` | 玩家 2 A / B |
| `]` / `[` | 玩家 2 Start / Select |

按键映射定义在 `src/controller.cpp` 的 `SetKeyMap()` 中，可按需修改。

## 项目结构

```text
src/
├── cpu.*            6502 CPU
├── cpu_ram.*        CPU 总线 / RAM
├── ppu.*            PPU 图形处理单元
├── ppu_bus.*        PPU 总线
├── cartridge.*      iNES 卡带解析
├── controller.*     手柄与键盘映射
├── Mapper/          Mapper 0 / 1 / 2
├── mainwindow.*     Qt 窗口与帧循环
├── colors_map.h     NES 调色板
└── main.cpp         程序入口
```

## License

[GPL-3.0](LICENSE)
