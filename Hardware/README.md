# cwFOC 硬件工程

本目录为 cwFOC 硬件设计存放目录，使用的 EDA 工具为 KiCAD

原理图设计采用分层图框，顶层图框为`cwFOC.kicad_sch`

## 硬件设计进度

Rev 1.0 已知问题：

1. 螺丝孔位有偏差
2. **泵升电压没有处理，容易导致电机驱动和 LDO 损坏！**
3. 电流采样处有尖峰噪声

Rev 1.1 计划：

1. 修正螺丝孔位
2. 添加防反灌二极管及 TVS
3. 电流采样加滤波

- [ ] 原理图修正
- [ ] PCB 布局
- [ ] ERC
- [ ] 生产
- [ ] 测试

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

## 成本预估

| 类型        | 器件          | 数量 |  预估价格  |
| ----------- | ------------ | --- | --------- | 
| 主控芯片     | CW32F030K8U6 |  1  |  ￥3      | 
| 电机驱动芯片 |  MP6540GU     |  1  |  ￥6      |  
| 通信协议芯片 |  SP485EEN     |  1  |  ￥1      |  
| 传感器      |  AS5600       |  1  |  ￥4      |  
| 电源芯片    |  HT7150-1     |  1  |  ￥0.5    | 
| 电源芯片    |  HT7533-1     |  1  |  ￥0.5    | 

成本总计：￥15

## TODO