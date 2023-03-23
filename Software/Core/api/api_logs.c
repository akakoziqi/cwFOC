#include "api_logs.h"

#include "drv_uart.h"
#include <stdint.h>
#include <stdarg.h>

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
    uart_print_init(115200);
}

static inline void LOG_Print(char *buffer)
{
    printf("%s", buffer);
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