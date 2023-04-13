/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * 文件名: api_logs.c
 * 作者: akako
 * 修订版本: 1.0
 * 最后编辑: akako
 * 内容摘要: 分级日志输出
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

#include "api_logs.h"
#include "drv_uart.h"

#define LOG_COLOR_NONE "\033[0m"
#define LOG_COLOR_RED "\033[31m"
#define LOG_COLOR_GREEN "\033[32m"
#define LOG_COLOR_YELLOW "\033[33m"
#define LOG_COLOR_BLUE "\033[34m"
#define LOG_COLOR_PURPLE "\033[35m"
#define LOG_COLOR_VIOLATE "\033[36m"
#define LOG_COLOR_WHITE "\033[37m"

char log_buffer[LOG_BUFFER_MAX_SIZE] = {0};

static const char *log_level_prefix[] =
    {
        ""
        "\n\r" LOG_COLOR_GREEN "[SUCC] "
        "",
        ""
        "\n\r" LOG_COLOR_WHITE "[INFO] "
        "",
        ""
        "\n\r" LOG_COLOR_VIOLATE "[DEBG] "
        "",
        ""
        "\n\r" LOG_COLOR_YELLOW "[WARN] "
        "",
        ""
        "\n\r" LOG_COLOR_RED "[ERRO] "
        "",
};

extern void api_logs_init(void)
{
    drv_uart2_init(115200);
}

static inline void LOG_Print(char *buffer)
{
    drv_uart_send_string(UART_Instance2, buffer);
}

static inline char *append2String(char *string, const char *append)
{
    uint32_t stringCnt = 0;

    while ((append[stringCnt] != '\0') &&
           (stringCnt < LOG_BUFFER_MAX_SIZE))
    {
        string[stringCnt] = append[stringCnt];
        stringCnt++;
    }

    return (string + stringCnt);
}

extern void api_logs(short level, const char *tag, char *fmt, ...)
{
    char *pBuffer = log_buffer;
    va_list ap;

    pBuffer = append2String(pBuffer, log_level_prefix[level]);
    pBuffer = append2String(pBuffer, tag);
    pBuffer = append2String(pBuffer, ": ");

    va_start(ap, fmt);
    vsprintf(pBuffer, fmt, ap);
    va_end(ap);

    log_buffer[LOG_BUFFER_MAX_SIZE - 1] = '\0';

    LOG_Print(log_buffer);
}