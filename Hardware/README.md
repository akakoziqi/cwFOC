# cwFOC 硬件工程

本目录为 cwFOC 硬件设计存放目录，使用的 EDA 工具为 KiCAD

原理图设计采用分层图框，顶层图框为`cwFOC.kicad_sch`

## 硬件设计进度

- [x] 原理图设计
- [ ] 原理图核对
- [ ] PCB 设计
- [ ] ERC
- [ ] BOM 核对
- [ ] 交厂打样
- [ ] 焊接测试
- [ ] 版本迭代

## Pinout

| MCU GPIO    | 复用功能     | 硬件功能        |
| ----------- | ----------- | -------------- |
| PF0         | I2C1 SDA    | AS5600 数据线   |
| PF1         | I2C1 SCL    | AS5600 时钟线   |
| PA6         | TIM1 BRK    | 定时器硬件刹车   |
| PA8         | TIM1 CH1    | C 相 PWM 输出   |
| PA9         | TIM1 CH2    | B 相 PWM 输出   |
| PA10        | TIM1 CH3    | A 相 PWM 输出   |
| PA11        | GPIO        | MP6540 EN      |
| PA12        | GPIO        | MP6540 Sleep   |
| PA1         | ADC IN1     | AS5600 模拟输入 |
| PA2         | ADC IN2     | 母线电压测量     |
| PA3         | ADC IN3     | C 相电流采样     |
| PA4         | ADC IN4     | B 相电流采样     |
| PA5         | ADC IN5     | A 相电流采样     |
| PB5         | GPIO        | RS485 方向控制  |
| PB6         | UART3 TXD   | RS485 TXD      |
| PB7         | UART3 RXD   | RS485 RXD      |
| PA15        | UART2 RXD   | 调试串口 RXD    |
| PB3         | UART2 TXD   | 调试串口 TXD    |
| PA13        | SWDIO       | SW 调试接口     |
| PA14        | SWCLK       | SW 调试接口     |
| PB4         | GPIO        | Blinky LED     |

## 外部接插件

供电及通信控制接口为 `KEFA KF2EDGV 3.81mm 5Pin 直插`

调试接口为 `JST SH1.0mm 5Pin 立贴`

## TODO