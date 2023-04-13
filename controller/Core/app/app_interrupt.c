/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * 文件名: app_interrupt.c
 * 作者: akako
 * 修订版本: 1.0
 * 最后编辑: akako
 * 内容摘要: 中断处理
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

#include "app_main.h"

void NMI_Handler(void)
{
}

void HardFault_Handler(void)
{
  while (1)
  {
  }
}

void SVC_Handler(void)
{
}

void PendSV_Handler(void)
{
}

void WDT_IRQHandler(void)
{
}

void LVD_IRQHandler(void)
{
}

void RTC_IRQHandler(void)
{
}

void FLASHRAM_IRQHandler(void)
{
}

void RCC_IRQHandler(void)
{
}

void GPIOA_IRQHandler(void)
{
}

void GPIOB_IRQHandler(void)
{
}

void GPIOC_IRQHandler(void)
{
}

void GPIOF_IRQHandler(void)
{
}

void DMACH1_IRQHandler(void)
{
}

void DMACH23_IRQHandler(void)
{
}

void DMACH45_IRQHandler(void)
{
}

void ADC_IRQHandler(void)
{
}

void ATIM_IRQHandler(void)
{
}

void VC1_IRQHandler(void)
{
}

void VC2_IRQHandler(void)
{
}

void GTIM1_IRQHandler(void)
{
}

void GTIM2_IRQHandler(void)
{
}

void GTIM3_IRQHandler(void)
{
}

void GTIM4_IRQHandler(void)
{
}

void BTIM1_IRQHandler(void)
{
}

void BTIM2_IRQHandler(void)
{
}

void BTIM3_IRQHandler(void)
{
}

void I2C1_IRQHandler(void)
{
}

void I2C2_IRQHandler(void)
{
}

void SPI1_IRQHandler(void)
{
}

void SPI2_IRQHandler(void)
{
}

void UART1_IRQHandler(void)
{
}

void UART2_IRQHandler(void)
{
}

void UART3_IRQHandler(void)
{
}

void AWT_IRQHandler(void)
{
}

void FAULT_IRQHandler(void)
{
}