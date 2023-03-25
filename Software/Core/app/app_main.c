#include "app_main.h"
#include "cw32f030_gpio.h"
#include "cw32f030_rcc.h"
#include "api_logs.h"
#include "drv_uart.h"
#include "drv_mp6540.h"
#include "drv_as5600.h"
#include "drv_atim.h"
#include "app_foc.h"
#include "drv_clock.h"
#include "drv_adc.h"

static const char *tag = "app_main";
float angle_el = 0;
uint16_t adc_value = 0;
float vbus = 0;

static inline void LED_Init()
{
    GPIO_InitTypeDef GPIO_InitStruct;
    RCC_AHBPeriphClk_Enable(RCC_AHB_PERIPH_GPIOB, ENABLE);

    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.IT = GPIO_IT_NONE;
    GPIO_InitStruct.Pins = GPIO_PIN_4;
    GPIO_Init(CW_GPIOB, &GPIO_InitStruct);
}

int main(void)
{
    drv_clock_pll();
    LED_Init();
    // 开启两线调试接口
    RCC_SWDIO_Config(RCC_SYSCTRL_SWDIOEN);
    api_logs_init();
    drv_uart3_init(115200);
    drv_mp6540_init();
    drv_mp6540_sleep(false);
    drv_mp6540_enable(true);
    drv_as5600_init();
    app_foc_init();
    drv_adc_init();
    FirmwareDelay(100000);

    API_LOGI(tag, "HCLK:%ld", RCC_Sysctrl_GetHClkFreq());
    API_LOGI(tag, "PCLK:%ld", RCC_Sysctrl_GetPClkFreq());

    while (1)
    {
        GPIO_TogglePin(CW_GPIOB, GPIO_PIN_4);
        // drv_uart_rs485_send_byte(UART_Instance3, 'A');
        // drv_uart_rs485_send_string(UART_Instance3, "Akako test!\n");
        // USART_SendData_8bit(CW_UART2, 'A');
        // FirmwareDelay(100000);
        adc_value = drv_as5600_read_raw_angle();

        angle_el = (adc_value * 11) * (3.1415926535 * 2 / 4096);

        app_foc_handle(4, 0, angle_el + (3.1415926535 * 0.3));

        // vbus = drv_adc_get_vbus()/4096.0*2.5*6.041;

        // API_LOGI(tag, "VBUS:%6ld", (uint32_t)(vbus*10000));

        // API_LOGI(tag, "PCLK:%ld", RCC_Sysctrl_GetPClkFreq());
    }

    return 0;
}

/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
       tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
