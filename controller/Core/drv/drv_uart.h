/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * 文件名: drv_uart.h
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

#ifndef __DRV_UART_H__
#define __DRV_UART_H__

#include "sys_inc.h"

typedef struct tagUARTInstance
{
    void * __u__nused;
} *UARTInstance;


extern const UARTInstance UART_Instance2;
extern const UARTInstance UART_Instance3;

extern void drv_uart2_init(uint32_t baudrate);
extern void drv_uart3_init(uint32_t baudrate);
extern void drv_uart2_dma_init(uint32_t TxRxBuffer);
extern void drv_uart3_dma_init(void);
extern void drv_uart3_dir_tx(void);
extern void drv_uart3_dir_rx(void);
extern void drv_uart_rs485_send_byte(UARTInstance UART_Instance, uint8_t byte);
extern void drv_uart_rs485_send_string(UARTInstance UART_Instance, char *string);
extern void drv_uart_send_byte(UARTInstance UART_Instance, uint8_t byte);
extern void drv_uart_send_string(UARTInstance UART_Instance, char* string);
extern uint8_t drv_uart_recv_byte(UARTInstance UART_Instance);

#endif
