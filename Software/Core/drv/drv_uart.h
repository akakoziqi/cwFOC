#ifndef __DRV_UART_H__
#define __DRV_UART_H__

#include <stdint.h>

typedef struct tagUARTInstance
{
    void * __unused;
} *UARTInstance;


extern const UARTInstance UART_Instance2;
extern const UARTInstance UART_Instance3;

extern void drv_uart2_init(uint32_t baudrate);
extern void drv_uart3_init(uint32_t baudrate);
extern void drv_uart2_dma_init(uint32_t TxRxBuffer);
extern void drv_uart3_dma_init(void);
extern void drv_uart3_dir_tx(void);
extern void drv_uart3_dir_rx(void);


#endif
