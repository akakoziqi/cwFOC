/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * 文件名: drv_clock.c
 * 作者: akako
 * 修订版本: 1.0
 * 最后编辑: akako
 * 内容摘要: 时钟 驱动
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Email: akako.ziqi@outlook.com
 *
 * Copyright (C) 2023 akako
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "drv_clock.h"
#include "sys_lib_inc.h"
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