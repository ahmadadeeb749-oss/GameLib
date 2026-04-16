# GameLib.h

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE) [![C++ Standard](https://img.shields.io/badge/C%2B%2B-11-blue.svg)](https://en.cppreference.com/w/cpp/11) [![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20macOS-0078d4.svg)](https://github.com/skywind3000/GameLib) [![Header Only](https://img.shields.io/badge/Header--Only-single%20file-green.svg)](GameLib.h) [![No Dependencies](https://img.shields.io/badge/Dependencies-zero-brightgreen.svg)](https://github.com/skywind3000/GameLib) [![GCC 4.9+](https://img.shields.io/badge/GCC-4.9%2B-orange.svg?logo=gnu)](https://gcc.gnu.org/)

给 C++ 初学者的游戏开发库，只有一个头文件，无需安装任何东西，写句 `include "GameLib.h"` 就能开始做游戏。

很多 C++ 初学者反馈，学 C++ 不像其他语言三两行就能出个东西，最痛苦的体验是学了好几周，能做的事情还是在黑窗口里 `cout` 一行字。离 "做一个真正的程序" 遥不可及，正反馈几乎为零。想用 SDL、SFML？光配环境、链接库就够折腾半天，还没写第一行游戏逻辑就已经想放弃了。

GameLib 就是为了干掉这段痛苦而生的。把 `GameLib.h` 丢进项目文件夹，十行代码画出一个能用键盘操控的彩色圆——窗口、绘图、键盘、鼠标、精灵、声音、碰撞检测全都有，不需要下载 SDK，不需要配置路径，不需要链接任何库。它就像 C++ 世界里的 PyGame：把所有复杂的东西藏起来，只留下做游戏的乐趣。

![](assets/demo.png)


## 它长什么样？

```cpp
#include "GameLib.h"

int main()
{
    GameLib game;
    game.Open(640, 480, "My Game", true);

    int x = 320, y = 240;

    while (!game.IsClosed()) {
        if (game.IsKeyDown(KEY_LEFT))  x -= 3;
        if (game.IsKeyDown(KEY_RIGHT)) x += 3;
        if (game.IsKeyDown(KEY_UP))    y -= 3;
        if (game.IsKeyDown(KEY_DOWN))  y += 3;

        game.Clear(COLOR_BLACK);
        game.FillCircle(x, y, 15, COLOR_CYAN);
        game.DrawText(10, 10, "Up/Down/Left/Right to move!", COLOR_WHITE);
        game.Update();
        game.WaitFrame(60);
    }
    return 0;
}
```

编译：

```bash
g++ main.cpp -o game.exe
```

不需要加任何编译参数，很多 C++ 初学者连命令行编译都不懂，只会直接在 Dev-C++ 里点编译+运行，让他们像用其他库一样添加一些类似 `-ld3d9x` 之类编译参数，可能直接就劝退一大群人，因此这个库完全使用默认编译参数，所有依赖都是动态库自己手工加载。

![](https://skywind3000.github.io/images/p/gamelib/demo1.png)

几行代码迅速看到反馈。


## 为什么做这个？

市面上的游戏库（SDL、SFML、raylib）都很好，但对于刚接触 C++ 的初学者来说：

- SDL 要配置头文件路径、链接十几个 dll，使用复杂
- SFML 要用 CMake
- raylib 需要懂线性代数，三维基础知识，熟练 C/C++，还需编译/安装。

**GameLib 的目标是零门槛**：把 `GameLib.h` 拷到项目文件夹，写一个 `.cpp` 文件，点编译，游戏就跑起来了。

它专门为 **Dev C++**（很多学校编程课在用的 IDE）设计，兼容其自带的 GCC 4.9.2 编译器。当然，任何支持 C++11 的 Windows 编译器都可以用。


## 特性一览

### 零配置

- 单个头文件 `GameLib.h`，拷贝即用；
- 不依赖 SDL / SFML / DirectX / OpenGL；
- 不需要再写 `-lgdi32 -lwinmm -lgdiplus -lole32` 等链接参数，可以选择性加个 `-mwindows` （启动没有黑色控制台窗口的意思）；
- 兼容 Dev C++ 自带的 GCC 4.9.2；

（注：应大家要求 port 了一个 SDL2 版本的 `GameLib.SDL.h` 供 Linux/macOS 平台使用，同样是单体头文件，详细见 [SDL2PORT.md](SDL2PORT.md) 文件）。

### 开箱即用的绘图

- 画点、线、矩形、圆、椭圆、三角形（描边和填充）
- 裁剪矩形（`SetClip`/`ClearClip`），所有绘制自动受裁剪约束
- 内嵌 8x8 像素点阵字体，支持所有可打印 ASCII 字符
- `DrawTextFont` 支持可缩放字体和 UTF-8 文本输出
- `DrawPrintf` 像 `printf` 一样在屏幕上格式化输出
- `Screenshot` 一行代码把当前画面保存为 BMP 文件
- `ShowFps(true)` 可直接在标题栏显示实时 FPS
- 所有图形算法自行实现（Bresenham 直线、中点圆、扫描线填充）

### 精灵系统

- 加载 PNG、JPG、BMP、GIF 等格式
- 支持 8-bit 调色板、24-bit、32-bit 图片（自动转换为 32 位 ARGB）
- 24 位图片自动补全 alpha 通道（设为不透明）
- 翻转、Color Key 透明、Alpha 混合、区域裁剪、缩放、旋转、按帧绘制
- 用整数 ID 管理，不需要理解指针和对象生命周期

### 键盘和鼠标

- `IsKeyDown` — 按住检测
- `IsKeyPressed` — 单次按下检测（按下瞬间触发一次）
- `IsKeyReleased` / `IsMouseReleased` — 单次松开检测
- 鼠标位置、三键状态和滚轮增量
- `IsActive()` 可判断窗口是否失焦，方便暂停游戏
- 预定义所有常用按键常量：`KEY_A`\~`KEY_Z`、方向键、F1\~F12

### 声音

- `PlayWAV` — 播放音效（WAV 格式，异步，返回是否成功启动）
- `PlayMusic` / `StopMusic` — 播放背景音乐（MP3/MIDI/WAV，按扩展名选择 MCI 类型；MIDI 循环走 notify 重播）
- `IsMusicPlaying()` — 查询库当前记录的背景音乐状态
- 音效和音乐独立通道，互不干扰

### 游戏工具

- `Random(min, max)` — 随机数
- `RectOverlap` / `CircleOverlap` — 碰撞检测
- `Distance` — 两点距离
- `DrawGrid` / `FillCell` — 网格绘制（适合俄罗斯方块、棋盘类游戏）
- `GetDeltaTime` / `GetFPS` — 帧时间和帧率

### Tilemap 系统

- `CreateTilemap` — 用 tileset 精灵创建瓦片地图
- `SaveTilemap` / `LoadTilemap` — 保存或载入纯文本 `.glm` 地图数据
- `SetTile` / `GetTile` / `FillTileRect` / `ClearTilemap` — 单点和批量设置瓦片
- `GetTilemapCols` / `GetTilemapRows` / `GetTileSize` — 读取地图元数据
- `WorldToTileCol` / `WorldToTileRow` / `GetTileAtPixel` — 把像素坐标换算成瓦片坐标
- `DrawTilemap` — 绘制地图，支持不透明、Color Key、Alpha 三种模式
- 只绘制屏幕可见范围内的瓦片，大地图也不卡
- 配合相机偏移轻松实现横版卷轴和视差滚动

### 窗口缩放

- `Open()` 第五个参数 `resizable=true` 即可创建可拖拽缩放窗口
- Framebuffer 逻辑尺寸在 `Open` 时固定，窗口缩放时自动拉伸填满
- `WinResize(w, h)` 程序端调整窗口大小，`SetMaximized(true)` 一键最大化
- 鼠标坐标自动按缩放比例映射回 framebuffer 逻辑坐标

### 场景管理

- `SetScene` / `GetScene` / `IsSceneChanged` — 用整数标识场景，下一帧生效
- `IsSceneChanged()` 在新场景首帧返回 `true`，方便做初始化
- 配合 `enum` 和 `switch` 即可实现菜单 → 游戏 → 结算的多场景切换

### 存档读写

- `SaveInt` / `SaveFloat` / `SaveString` — 一行代码保存数据到文件
- `LoadInt` / `LoadFloat` / `LoadString` — 一行代码读取，不存在时返回默认值
- 静态函数，不需要 GameLib 实例即可调用
- 纯文本 `key=value` 格式，人类可读

### UI 控件

- `Button` — 即时模式按钮，自动处理 hover / pressed 视觉状态
- `Checkbox` — 复选框，点击自动翻转状态
- `RadioBox` — 单选框，同组共享变量实现互斥
- `ToggleButton` — 开关按钮，按下后持续凹陷
- 使用内置 8x8 点阵字体，零依赖零配置


## 快速上手

### 第一步：下载

把 `GameLib.h` 放到你的项目文件夹里。

### 第二步：写代码

创建一个 `main.cpp`：

```cpp
#include "GameLib.h"

int main()
{
    GameLib game;
    game.Open(800, 600, "Hello GameLib", true);

    while (!game.IsClosed()) {
        game.Clear(COLOR_DARK_BLUE);
        game.DrawTextScale(200, 250, "Hello, World!", COLOR_GOLD, 3);
        game.DrawText(280, 320, "Press ESC to exit", COLOR_GRAY);

        if (game.IsKeyPressed(KEY_ESCAPE))
            break;

        game.Update();
        game.WaitFrame(60);
    }
    return 0;
}
```

### 第三步：编译运行

**Dev C++**：新建项目 > 添加 `main.cpp` > 编译运行。

**命令行**：

```bash
g++ -o game.exe main.cpp -mwindows
```




## 更多示例

### 弹跳小球

```cpp
#include "GameLib.h"

int main()
{
    GameLib game;
    game.Open(640, 480, "Bouncing Ball", true);

    float x = 320, y = 240;
    float vx = 4, vy = 3;
    int r = 20;

    while (!game.IsClosed()) {
        // 移动
        x += vx;
        y += vy;

        // 碰壁反弹
        if (x - r < 0 || x + r > game.GetWidth())  vx = -vx;
        if (y - r < 0 || y + r > game.GetHeight()) vy = -vy;

        // 绘制
        game.Clear(COLOR_BLACK);
        game.FillCircle((int)x, (int)y, r, COLOR_RED);
        game.DrawPrintf(10, 10, COLOR_WHITE, "FPS: %.0f", game.GetFPS());
        game.Update();
        game.WaitFrame(60);
    }
    return 0;
}
```

### 键盘控制 + 鼠标跟踪

```cpp
#include "GameLib.h"

int main()
{
    GameLib game;
    game.Open(640, 480, "Input Demo", true);

    int px = 320, py = 240;

    while (!game.IsClosed()) {
        // 键盘控制方块
        if (game.IsKeyDown(KEY_A)) px -= 3;
        if (game.IsKeyDown(KEY_D)) px += 3;
        if (game.IsKeyDown(KEY_W)) py -= 3;
        if (game.IsKeyDown(KEY_S)) py += 3;

        // 鼠标位置
        int mx = game.GetMouseX();
        int my = game.GetMouseY();

        game.Clear(COLOR_DARK_GRAY);

        // 方块
        game.FillRect(px - 15, py - 15, 30, 30, COLOR_GREEN);

        // 鼠标十字线
        game.DrawLine(mx - 20, my, mx + 20, my, COLOR_YELLOW);
        game.DrawLine(mx, my - 20, mx, my + 20, COLOR_YELLOW);

        // 鼠标点击画圆
        if (game.IsMouseDown(MOUSE_LEFT)) {
            game.FillCircle(mx, my, 10, COLOR_RED);
        }

        game.DrawPrintf(10, 10, COLOR_WHITE, "Player: %d, %d", px, py);
        game.DrawPrintf(10, 22, COLOR_WHITE, "Mouse:  %d, %d", mx, my);
        game.Update();
        game.WaitFrame(60);
    }
    return 0;
}
```

### 随机星空

```cpp
#include "GameLib.h"

int main()
{
    GameLib game;
    game.Open(800, 600, "Starfield", true);

    // 生成 200 颗星星
    int sx[200], sy[200], speed[200];
    uint32_t colors[] = {COLOR_WHITE, COLOR_LIGHT_GRAY, COLOR_YELLOW, COLOR_CYAN};
    for (int i = 0; i < 200; i++) {
        sx[i] = GameLib::Random(0, 799);
        sy[i] = GameLib::Random(0, 599);
        speed[i] = GameLib::Random(1, 5);
    }

    while (!game.IsClosed()) {
        game.Clear(COLOR_BLACK);

        for (int i = 0; i < 200; i++) {
            sx[i] -= speed[i];
            if (sx[i] < 0) {
                sx[i] = 800;
                sy[i] = GameLib::Random(0, 599);
            }
            game.SetPixel(sx[i], sy[i], colors[speed[i] % 4]);
        }

        game.DrawText(250, 290, "Press ESC to exit", COLOR_GRAY);
        if (game.IsKeyPressed(KEY_ESCAPE)) break;

        game.Update();
        game.WaitFrame(60);
    }
    return 0;
}
```

更多示例见 `examples/` 目录。




## 示例程序

`examples/` 目录包含 15 个由浅入深的示例，逐步展示 GameLib 的各项功能，覆盖窗口、图形、输入、精灵、动画、声音、Tilemap、裁剪矩形、字体文字、缩放、旋转与 UI 控件。每个示例同时兼容 Win32 (`GameLib.h`) 和 SDL (`GameLib.SDL.h`) 两条产品线，文件头通过预处理自动选择。

编译任意示例：

```bash
g++ -o 03_shapes.exe examples/03_shapes.cpp -mwindows
```

运行：

![](https://skywind3000.github.io/images/p/gamelib/shapes.png)

即可。

### 入门基础

| 示例 | 说明 | 学到什么 |
|-|-|-|
| `01_hello.cpp` | Hello World | 游戏循环、窗口创建、文字绘制 |
| `02_movement.cpp` | 键盘移动 + 弹跳小球（TAB 切换） | 键盘输入、GetDeltaTime、碰壁反弹 |
| `03_shapes.cpp` | 所有图形绘制展示 | 线、矩形、圆、椭圆、三角形的描边与填充 |
| `04_paint.cpp` | 简易画板 | 鼠标输入、滚轮调笔刷、失焦暂停 |

### 精灵与声音

| 示例 | 说明 | 学到什么 |
|-|-|-|
| `05_sprites.cpp` | 精灵基础 + 帧动画（TAB 切换） | CreateSprite、DrawSpriteEx、DrawSpriteFrameScaled、方向动画 |
| `06_sound.cpp` | 声音播放演示 | PlayBeep、PlayWAV、PlayMusic、跨平台音乐处理 |
| `07_shooting.cpp` | 简易射击 | 数组管理多对象、子弹发射、碰撞销毁 |

### 完整小游戏

| 示例 | 说明 | 学到什么 |
|-|-|-|
| `08_breakout.cpp` | 打砖块 | 碰撞检测深度运用、多对象管理、音效反馈 |
| `09_snake.cpp` | 贪吃蛇 | DrawGrid/FillCell、游戏状态机 |

### Tilemap 与文字

| 示例 | 说明 | 学到什么 |
|-|-|-|
| `10_tilemap.cpp` | 双层视差卷轴 | CreateTilemap、FillTileRect、WorldToTileCol/Row、视差滚动 |
| `11_font_text.cpp` | 可缩放字体与 UI | DrawTextFont、DrawPrintfFont、ShowMouse、ShowMessage |

### 高级特性

| 示例 | 说明 | 学到什么 |
|-|-|-|
| `12_sprite_transform.cpp` | 精灵缩放 + 旋转（TAB 切换） | DrawSpriteScaled、DrawSpriteRotated、DrawSpriteFrameRotated |
| `13_clip_rect.cpp` | 裁剪矩形 | SetClip/ClearClip/GetClip、图元/文字/精灵裁剪 |
| `14_space_shooter.cpp` | 太空射击 | 综合：精灵 + 音效 + 碰撞 + 滚动背景 + 难度递进 |
| `15_ui_controls.cpp` | UI 控件演示 | Button、Checkbox、RadioBox、ToggleButton 即时模式 UI |




## API 速查

完整的 API 接口说明见 [docs/Manual.md](docs/Manual.md)。




## 适合做什么？

- 太空射击 (Space Shooter)
- 横版卷轴 (Side-Scrolling Platformer)
- 俄罗斯方块 (Tetris)
- 贪吃蛇 (Snake)
- 打砖块 (Breakout)
- 走迷宫 (Maze)
- 接水果 (Fruit Catcher)
- 弹幕游戏 (Bullet Hell)
- 回合制 RPG（场景切换 + 存档读写）
- 视觉小说 / 文字冒险（多场景 + 分支对话）
- 地图编辑器（Tilemap + UI 控件）
- 画板程序 (Paint)
- 课程作业演示（快速出图，零配置交付）
- 任何你能想到的 2D 小游戏或互动程序




## 技术细节

- **双缓冲**：所有绘制写入内存帧缓冲（`uint32_t*` ARGB），`Update()` 时通过 DIB Section + `BitBlt`（或 `StretchBlt` 缩放）刷新到窗口，无闪烁
- **图形自实现**：不调用 `LineTo`、`Ellipse` 等 GDI 图元函数，线段、圆、椭圆和三角形算法都由库内实现
- **字体后端**：可缩放字体文字当前通过 GDI 的 `CreateFontW` / `TextOutW` / `GetTextExtentPoint32W` 实现
- **精确窗口尺寸**：`Open()` 保证客户区严格等于请求的宽高（含高 DPI 二次校正）
- **stb 风格单头文件**：默认 include 即启用实现；多文件项目可用 `GAMELIB_NO_IMPLEMENTATION` 控制




## 环境要求

- Windows 7 及以上
- 任何支持 C++11 的编译器（GCC 4.9+、MSVC 2015+、Clang）
- 推荐 IDE：Dev C++、Visual Studio、Code::Blocks

## 网络资源

想做游戏找不到资源？可以到下面几个地方转转：

- 老游戏精灵资源：https://www.spriters-resource.com
- 像素风格资源：http://www.charas-project.net/resources.php?lang=en
- 另一个像素资源：https://craftpix.net/tags/pixel-art-game-assets-download

还可以去 PyGame 的 [Resources](https://www.pygame.org/wiki/resources) 页面，里面有各种免费的图片，音频，字体资源。


## 协议

MIT License. 随便用。
