/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * 文件名: drv_adc.c
 * 作者: akako
 * 修订版本: 1.0
 * 最后编辑: akako
 * 内容摘要: ADC 驱动层
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


#include "drv_adc.h"
#include "sys_lib_inc.h"

static inline void drv_adc_gpio_init()
{
    RCC_AHBPeriphClk_Enable(RCC_AHB_PERIPH_GPIOA, ENABLE);
    PA01_ANALOG_ENABLE();
    PA02_ANALOG_ENABLE();
    PA03_ANALOG_ENABLE();
    PA04_ANALOG_ENABLE();
    PA05_ANALOG_ENABLE();
}

extern void drv_adc_init()
{
    ADC_InitTypeDef ADC_InitStructure;
    ADC_WdtTypeDef ADC_WdtStructure;
    ADC_SingleChTypeDef ADC_SingleChStructure;

    RCC_APBPeriphClk_Enable2(RCC_APB2_PERIPH_ADC, ENABLE);
    drv_adc_gpio_init();
    ADC_StructInit(&ADC_InitStructure);
    ADC_InitStructure.ADC_ClkDiv = ADC_Clk_Div2;
    ADC_WdtInit(&ADC_WdtStructure);

    // 配置单通道转换模式
    ADC_SingleChStructure.ADC_DiscardEn = ADC_DiscardNull;
    ADC_SingleChStructure.ADC_Chmux = ADC_ExInputCH2; // 选择ADC转换通道，AIN2:PA02
    ADC_SingleChStructure.ADC_InitStruct = ADC_InitStructure;
    ADC_SingleChStructure.ADC_WdtStruct = ADC_WdtStructure;

    ADC_SingleChContinuousModeCfg(&ADC_SingleChStructure);
    // ADC_ITConfig(ADC_IT_EOC, ENABLE);

    // ADC_EnableIrq(ADC_INT_PRIORITY);
    ADC_ClearITPendingAll();

    // ADC使能
    ADC_Enable();
    CW_ADC->CR1_f.CHMUX = 0x02;
    ADC_SoftwareStartConvCmd(ENABLE);
}

extern uint16_t drv_adc_get_vbus()
{
    uint16_t v = ADC_GetConversionValue();
    ADC_SoftwareStartConvCmd(ENABLE);

    return v;
}
