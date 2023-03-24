#ifndef __API_LOGS_H__
#define __API_LOGS_H__

#include "sys_inc.h"

// 日志最大缓冲区
#define LOG_BUFFER_MAX_SIZE (256) // Bytes
// 日志等级
#define API_LOG_LEVEL LEVEL_SUCCESS

#define   LEVEL_SUCCESS  0
#define   LEVEL_INFO  1
#define   LEVEL_DEBUG  2
#define   LEVEL_WARN  3
#define   LEVEL_ERROR  4
#define   LEVEL_NONE  5

#if (API_LOG_LEVEL <= LEVEL_SUCCESS)
#define API_LOGS(tag, ...) api_logs(LEVEL_SUCCESS, tag, __VA_ARGS__)
#else
#define API_LOGS(tag, ...)
#endif

#if (API_LOG_LEVEL <= LEVEL_INFO)
#define API_LOGI(tag, ...) api_logs(LEVEL_INFO, tag, __VA_ARGS__)
#else
#define API_LOGI(tag, ...)
#endif

#if (API_LOG_LEVEL <= LEVEL_DEBUG)
#define API_LOGD(tag, ...) api_logs(LEVEL_DEBUG, tag, __VA_ARGS__)
#else
#define API_LOGD(tag, ...)
#endif

#if (API_LOG_LEVEL <= LEVEL_WARN)
#define API_LOGW(tag, ...) api_logs(LEVEL_WARN, tag, __VA_ARGS__)
#else
#define API_LOGW(tag, ...)
#endif

#if (API_LOG_LEVEL <= LEVEL_ERROR)
#define API_LOGE(tag, ...) api_logs(LEVEL_ERROR, tag, __VA_ARGS__)
#else
#define API_LOGE(tag, ...)
#endif

/// @brief api_logs 模块初始化
/// @param  none
extern void api_logs_init(void);

/// @brief api_logs 打印日志信息
/// @param level 日志等级
/// @param tag 日志标签
/// @param fmt 格式化输出内容
extern void api_logs(short level, const char *tag, char *fmt, ...);

#endif
