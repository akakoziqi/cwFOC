#include "drv_mp6540.h"
#include "cw32f030_gpio.h"
#include "cw32f030_rcc.h"

#define MP6540_SLP_Pin GPIO_PIN_12
#define MP6540_SLP_Port CW_GPIOA

#define MP6540_EN_Pin GPIO_PIN_11
#define MP6540_EN_Port CW_GPIOA

static inline void drv_mp6540_gpio_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHBPeriphClk_Enable(RCC_AHB_PERIPH_GPIOA, ENABLE);

    GPIO_InitStructure.Pins = MP6540_EN_Pin;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
    GPIO_Init(MP6540_EN_Port, &GPIO_InitStructure);

    GPIO_InitStructure.Pins = MP6540_SLP_Pin;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
    GPIO_Init(MP6540_SLP_Port, &GPIO_InitStructure);
}

extern void drv_mp6540_init(void)
{
    drv_mp6540_gpio_init();
}

extern void drv_mp6540_sleep(bool state)
{
    if (state)
    {
        GPIO_WritePin(MP6540_SLP_Port, MP6540_SLP_Pin, GPIO_Pin_RESET);
    }
    else
    {
        GPIO_WritePin(MP6540_SLP_Port, MP6540_SLP_Pin, GPIO_Pin_SET);
    }
}

extern void drv_mp6540_enable(bool state)
{
    if (state)
    {
        GPIO_WritePin(MP6540_EN_Port, MP6540_EN_Pin, GPIO_Pin_SET);
    }
    else
    {
        GPIO_WritePin(MP6540_EN_Port, MP6540_EN_Pin, GPIO_Pin_RESET);
    }
}