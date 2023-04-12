# CW32 环境搭建教程

## 开源工具链搭建

CW32 开源构建工具链主要分为以下几部分：

1. arm-none-eabi-gcc
2. GNU make
3. pyOCD
4. Visual Studio Code

### arm-none-eabi-gcc

在 ARM 官网下载 arm-none-eabi-gcc 后安装

[下载链接](https://developer.arm.com/downloads/-/gnu-rm)

注意：**安装时勾选添加到环境变量，否则需要手动添加**

### GNU make

在 GNU 官网或者 MSYS2 中安装 make for windows 并添加至系统环境变量

### pyOCD

顾名思义，首先您需要在电脑上安装 Python 环境，具体可参考 [Python 官网](https://www.python.org/)。

确保将 Python 加入环境变量之后，就可以安装 pyOCD 啦。

在命令行中输入：

``` cmd
pip install pyocd
```

如果您在访问外网的时候遇到了一些阻碍，可以试试更改 pip 源为国内源，具体操作方法如下：

设为默认：

``` cmd
pip config set global.index-url https://pypi.tuna.tsinghua.edu.cn/simple
```

临时使用清华源安装 pyOCD：

``` cmd
pip install -i https://pypi.tuna.tsinghua.edu.cn/simple pyocd
```

pyOCD 可以使用标准 CMSIS-PACK 中的烧录算法为单片机提供烧录和调试功能，所以几乎可以替代任何使用 Keil MDK 的场景。

常用命令：

``` cmd
pyocd list 列出所有可用调试接口和调试目标
pyocd pack 管理可用 CMSIS-PACK
pyocd flash 烧录程序
pypcd erase 擦除 Flash
```

具体使用方法和参数可参考 help

pyOCD 在启动时会检测当前目录下的 `pyocd.yaml` 配置文件，您可以将相关配置放在配置文件中，来避免输入冗长的~~咒语~~命令。

常见的参数配置有：

``` yaml
pack: # 预导入 CMSIS-PACK
target_override: # 目标单片机型号
frequency: # 调试时钟频率
```

以下是一个示例：

``` yaml
pack: ./Debug/WHXY.CW32F030_DFP.1.0.3.pack
target_override: CW32F030K8
frequency: 8000000
```

### Visual Studio Code

在 VS Code 官网下载安装包安装

在插件选项卡中安装以下插件：

1. C/C++
2. Cortex-Debug
3. Makefile Tool

## 模板工程移植

在提供的 GCC 模板工程目录下打开终端，执行 `make` 命令即可


