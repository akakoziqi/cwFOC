#include "drv_clock.h"
#include "cw32f030_rcc.h"
#include "cw32f030_gpio.h"
#include "cw32f030_flash.h"

extern void drv_clock_pll()
{
    RCC_AHBPeriphClk_Enable(RCC_AHB_PERIPH_FLASH, ENABLE); // 打开FLASH时钟
    RCC_HSI_Enable(RCC_HSIOSC_DIV6);                       // 设置HSI = HSIOSC/6; 8MHz

    // 以下从HSI切换到PLL
    RCC_PLL_Enable(RCC_PLLSOURCE_HSI, 8000000, RCC_PLL_MUL_8); // 开启PLL，PLL源为HSI PLL输出为8MHz x 8 = 64MHz
    FLASH_SetLatency(FLASH_Latency_2);                         // 频率大于24M需要配置FlashWait=2

    RCC_PCLKPRS_Config(RCC_PCLK_DIV1);
    RCC_HCLKPRS_Config(RCC_HCLK_DIV1);

    while (RCC_SysClk_Switch(RCC_SYSCLKSRC_PLL))
    {
        ;
    }

    RCC_SystemCoreClockUpdate(64000000);
}