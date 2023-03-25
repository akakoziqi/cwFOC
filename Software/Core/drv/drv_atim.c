#include "drv_atim.h"
#include "cw32f030_atim.h"
#include "cw32f030_rcc.h"
#include "cw32f030_gpio.h"

static inline void drv_atim_gpio_init()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHBPeriphClk_Enable(RCC_AHB_PERIPH_GPIOA, ENABLE);

    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;

    PA08_AFx_ATIMCH1A();
    PA09_AFx_ATIMCH2A();
    PA10_AFx_ATIMCH3A();

    GPIO_InitStructure.Pins = GPIO_PIN_8;
    GPIO_Init(CW_GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.Pins = GPIO_PIN_9;
    GPIO_Init(CW_GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.Pins = GPIO_PIN_10;
    GPIO_Init(CW_GPIOA, &GPIO_InitStructure);
}

extern void drv_atim_init()
{
    ATIM_InitTypeDef ATIM_InitStruct;
    ATIM_OCInitTypeDef ATIM_OCInitStruct;

    drv_atim_gpio_init();

    RCC_APBPeriphClk_Enable2(RCC_APB2_PERIPH_ATIM, ENABLE);
    ATIM_InitStruct.BufferState = DISABLE;
    ATIM_InitStruct.ClockSelect = ATIM_CLOCK_PCLK;
    ATIM_InitStruct.CounterAlignedMode = ATIM_COUNT_MODE_CENTER_ALIGN;
    ATIM_InitStruct.CounterDirection = ATIM_COUNTING_UP;
    ATIM_InitStruct.CounterOPMode = ATIM_OP_MODE_REPETITIVE;
    ATIM_InitStruct.OverFlowMask = DISABLE;
    ATIM_InitStruct.Prescaler = ATIM_Prescaler_DIV1; // 计数时钟64MHz
    ATIM_InitStruct.ReloadValue = 1000;               // 频率64KHz
    ATIM_InitStruct.RepetitionCounter = 0;
    ATIM_InitStruct.UnderFlowMask = ENABLE;
    ATIM_InitStruct.OverFlowMask = ENABLE;

    ATIM_Init(&ATIM_InitStruct);

    ATIM_OCInitStruct.BufferState = DISABLE;
    ATIM_OCInitStruct.OCDMAState = DISABLE;
    ATIM_OCInitStruct.OCInterruptSelect = ATIM_OC_IT_NONE;
    ATIM_OCInitStruct.OCInterruptState = DISABLE;
    ATIM_OCInitStruct.OCMode = ATIM_OCMODE_PWM1;
    ATIM_OCInitStruct.OCPolarity = ATIM_OCPOLARITY_NONINVERT;

    ATIM_OC1AInit(&ATIM_OCInitStruct);
    ATIM_OC2AInit(&ATIM_OCInitStruct);
    ATIM_OC3AInit(&ATIM_OCInitStruct);


    ATIM_SetCompare1A(0);
    ATIM_SetCompare2A(0);
    ATIM_SetCompare3A(0);

    ATIM_Cmd(ENABLE);
    ATIM_CtrlPWMOutputs(ENABLE);
}

extern inline void drv_atim_set_ccr_a(uint16_t ccr)
{
    ATIM_SetCompare3A(ccr);
}

extern inline void drv_atim_set_ccr_b(uint16_t ccr)
{
    ATIM_SetCompare2A(ccr);
}

extern inline void drv_atim_set_ccr_c(uint16_t ccr)
{
    ATIM_SetCompare1A(ccr);
}
