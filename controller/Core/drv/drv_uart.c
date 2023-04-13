/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * 文件名: drv_uart.c
 * 作者: akako
 * 修订版本: 1.0
 * 最后编辑: akako
 * 内容摘要: UART 驱动
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

#include "drv_uart.h"
#include "sys_lib_inc.h"

#define DEVICE_INST(d) ((UART_TypeDef *)(d))

const UARTInstance UART_Instance2 = (UARTInstance)(CW_UART2);
const UARTInstance UART_Instance3 = (UARTInstance)(CW_UART3);

static void uart2_gpio_init(void);
static void uart3_gpio_init(void);

static inline void uart2_gpio_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHBPeriphClk_Enable(RCC_AHB_PERIPH_GPIOA, ENABLE);
    RCC_AHBPeriphClk_Enable(RCC_AHB_PERIPH_GPIOB, ENABLE);

    // UART TX RX 复用
    PB03_AFx_UART2TXD();
    PA15_AFx_UART2RXD();

    GPIO_InitStructure.Pins = GPIO_PIN_3;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
    GPIO_Init(CW_GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.Pins = GPIO_PIN_15;
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT_PULLUP;
    GPIO_Init(CW_GPIOA, &GPIO_InitStructure);
}

static inline void uart3_gpio_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHBPeriphClk_Enable(RCC_AHB_PERIPH_GPIOB, ENABLE);

    // UART TX RX 复用
    PB06_AFx_UART3TXD();
    PB07_AFx_UART3RXD();

    GPIO_InitStructure.Pins = GPIO_PIN_5;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
    GPIO_Init(CW_GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.Pins = GPIO_PIN_6;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
    GPIO_Init(CW_GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.Pins = GPIO_PIN_7;
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT_PULLUP;
    GPIO_Init(CW_GPIOB, &GPIO_InitStructure);
}

extern void drv_uart2_init(uint32_t baudrate)
{
    USART_InitTypeDef USART_InitStructure;
    RCC_APBPeriphClk_Enable1(RCC_APB1_PERIPH_UART2, ENABLE);
    uart2_gpio_init();

    USART_InitStructure.USART_BaudRate = baudrate;
    USART_InitStructure.USART_Over = USART_Over_16;
    USART_InitStructure.USART_Source = USART_Source_PCLK;
    USART_InitStructure.USART_UclkFreq = 64000000;
    USART_InitStructure.USART_StartBit = USART_StartBit_FE;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(CW_UART2, &USART_InitStructure);
}

extern void drv_uart3_init(uint32_t baudrate)
{
    USART_InitTypeDef USART_InitStructure;
    RCC_APBPeriphClk_Enable1(RCC_APB1_PERIPH_UART3, ENABLE);
    uart3_gpio_init();

    USART_InitStructure.USART_BaudRate = baudrate;
    USART_InitStructure.USART_Over = USART_Over_16;
    USART_InitStructure.USART_Source = USART_Source_PCLK;
    USART_InitStructure.USART_UclkFreq = 64000000;
    USART_InitStructure.USART_StartBit = USART_StartBit_FE;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(CW_UART3, &USART_InitStructure);
}

extern void drv_uart2_dma_init(uint32_t TxRxBuffer)
{
    DMA_InitTypeDef DMA_InitStructure;

    // 初始化DMA TX
    DMA_InitStructure.DMA_Mode = DMA_MODE_BLOCK;
    DMA_InitStructure.DMA_TransferWidth = DMA_TRANSFER_WIDTH_8BIT;
    DMA_InitStructure.DMA_SrcInc = DMA_SrcAddress_Increase;
    DMA_InitStructure.DMA_DstInc = DMA_DstAddress_Fix;
    DMA_InitStructure.TrigMode = DMA_HardTrig;
    DMA_InitStructure.HardTrigSource = DMA_HardTrig_UART2_TXBufferE;
    DMA_InitStructure.DMA_TransferCnt = 512;
    DMA_InitStructure.DMA_SrcAddress = (uint32_t)TxRxBuffer;
    DMA_InitStructure.DMA_DstAddress = (uint32_t) & (CW_UART2->TDR);
    DMA_Init(CW_DMACHANNEL2, &DMA_InitStructure);
    DMA_Cmd(CW_DMACHANNEL2, ENABLE);
}

extern void drv_uart3_dma_init(void)
{
}

extern inline void drv_uart3_dir_tx(void)
{
    GPIO_WritePin(CW_GPIOB, GPIO_PIN_5, GPIO_Pin_SET);
}

extern inline void drv_uart3_dir_rx(void)
{
    GPIO_WritePin(CW_GPIOB, GPIO_PIN_5, GPIO_Pin_RESET);
}

extern void drv_uart_send_byte(UARTInstance UART_Instance, uint8_t byte)
{
    USART_SendData_8bit((UART_TypeDef *)UART_Instance, byte);
}

extern void drv_uart_rs485_send_byte(UARTInstance UART_Instance, uint8_t byte)
{
    drv_uart3_dir_tx();
    USART_SendData_8bit((UART_TypeDef *)UART_Instance, byte);
    drv_uart3_dir_rx();
}

extern void drv_uart_rs485_send_string(UARTInstance UART_Instance, char *string)
{
    drv_uart3_dir_tx();
    while (*string != '\0')
    {
        USART_SendData_8bit((UART_TypeDef *)UART_Instance, (uint8_t)*string);
        while (USART_GetFlagStatus((UART_TypeDef *)UART_Instance, USART_FLAG_TXBUSY) == SET)
            ;
        string++;
    }
    drv_uart3_dir_rx();
}

extern void drv_uart_send_string(UARTInstance UART_Instance, char *string)
{
    while (*string != '\0')
    {
        USART_SendData_8bit((UART_TypeDef *)UART_Instance, (uint8_t)*string);
        while (USART_GetFlagStatus((UART_TypeDef *)UART_Instance, USART_FLAG_TXBUSY) == SET)
            ;
        string++;
    }
}