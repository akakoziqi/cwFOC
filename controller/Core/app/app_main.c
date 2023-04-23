/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * 文件名: app_main.c
 * 作者: akako
 * 修订版本: 1.0
 * 最后编辑: akako
 * 内容摘要: 主函数
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
#include "utl_ffpm.h"

static const char *tag = "app_main";
fq12_t angle_el = 0;
fq12_t angle_mac = 0;
fq12_t vbus = 0;

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
        angle_mac = drv_as5600_read_raw_angle();

        angle_el = fmul(fmul(angle_mac, FQ12_2PI), 11) + TO_FQ12(FP64_PI * 0.3);
        // angle_el = (angle_mac * 11) * (3.1415926535 * 2 / 4096);

        app_foc_handle(TO_FQ12(4), TO_FQ12(0), angle_el);

        // vbus = drv_adc_get_vbus()/4096.0*2.5*6.041;

        // API_LOGI(tag, "VBUS:%6ld", (uint32_t)(vbus*10000));

        // API_LOGI(tag, "PCLK:%ld", RCC_Sysctrl_GetPClkFreq());
    }

    return 0;
}

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
}
#endif