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
