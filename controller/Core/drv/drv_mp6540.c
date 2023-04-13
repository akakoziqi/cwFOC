/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * 文件名: drv_mp6540.c
 * 作者: akako
 * 修订版本: 1.0
 * 最后编辑: akako
 * 内容摘要: MP6540 驱动
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

#include "drv_mp6540.h"
#include "sys_lib_inc.h"

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