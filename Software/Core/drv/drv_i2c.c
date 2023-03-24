#include "drv_i2c.h"

#include "cw32f030_gpio.h"
#include "cw32f030_i2c.h"
#include "cw32f030_rcc.h"

static inline void drv_i2c_gpio_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHBPeriphClk_Enable(RCC_AHB_PERIPH_GPIOF, ENABLE);

    PF00_AFx_I2C1SDA();
    PF01_AFx_I2C1SCL();

    GPIO_InitStructure.Pins = GPIO_PIN_0;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_OD; // GPIO_MODE_OUTPUT_PP; //
    GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
    GPIO_Init(CW_GPIOF, &GPIO_InitStructure);

    GPIO_InitStructure.Pins = GPIO_PIN_1;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_Init(CW_GPIOF, &GPIO_InitStructure);
}

extern void drv_i2c_init(void)
{
    I2C_InitTypeDef I2C_InitStruct;
    drv_i2c_gpio_init();
    I2C_InitStruct.I2C_BaudEn = ENABLE;
    I2C_InitStruct.I2C_Baud = 0x01; // 500K=(8000000/(8*(1+1))
    I2C_InitStruct.I2C_FLT = DISABLE;
    I2C_InitStruct.I2C_AA = DISABLE;
    I2C_Master_Init(CW_I2C1, &I2C_InitStruct); // 初始化模块
    I2C_Cmd(CW_I2C1, ENABLE);                  // 模块使能
}

