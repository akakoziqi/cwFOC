#include "drv_uart.h"
#include "cw32f030_uart.h"
#include "cw32f030_dma.h"
#include "cw32f030_gpio.h"

#define DEVICE_INST(d) ((UART_TypeDef *)(d))

const UARTInstance UART_Instance2 = (UARTInstance)(CW_UART2);
const UARTInstance UART_Instance3 = (UARTInstance)(CW_UART3);

static void uart2_gpio_init(void);
static void uart3_gpio_init(void);

static inline void uart2_gpio_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

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
    uart2_gpio_init();

    USART_InitStructure.USART_BaudRate = baudrate;
    USART_InitStructure.USART_Over = USART_Over_16;
    USART_InitStructure.USART_Source = USART_Source_PCLK;
    USART_InitStructure.USART_UclkFreq = 8000000;
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
    uart3_gpio_init();

    USART_InitStructure.USART_BaudRate = baudrate;
    USART_InitStructure.USART_Over = USART_Over_16;
    USART_InitStructure.USART_Source = USART_Source_PCLK;
    USART_InitStructure.USART_UclkFreq = 8000000;
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
    GPIO_WritePin(CW_GPIOB, GPIO_PIN_5, GPIO_Pin_RESET);
}

extern inline void drv_uart3_dir_rx(void)
{
    GPIO_WritePin(CW_GPIOB, GPIO_PIN_5, GPIO_Pin_SET);
}