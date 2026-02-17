/**
 * @file log_task.h
 * @brief Modular logging service for STM32 + FreeRTOS
 * @date 2026-02-17
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#ifndef LOG_TASK_H
#define LOG_TASK_H

/*******************************
 * INCLUDES
 *******************************/

#include "FreeRTOS.h"
#include "queue.h"
#include "usart.h"

/*******************************
 * DEFINES, ENUMS
 *******************************/

#define LOG_MSG_LEN 128
#define LOG_QUEUE_LEN 16
#define LOG_TASK_STACK_SIZE 256   // 1 KB

typedef enum {
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_TRACE
} log_level_t;

/*******************************
 * FUNCTION DECLARATIONS
 *******************************/

// Initialize the log service with the given UART handle
void log_init(UART_HandleTypeDef *uart);

// Logging function
// By default non-blocking (drops message if queue full)
void log_print(log_level_t level, const char *fmt, ...);

/*******************************
 * MACROS
 *******************************/

#define INFO_LOG(...)    log_print(LOG_LEVEL_INFO, __VA_ARGS__)
#define WARN_LOG(...)    log_print(LOG_LEVEL_WARN, __VA_ARGS__)
#define ERROR_LOG(...)   log_print(LOG_LEVEL_ERROR, __VA_ARGS__)
#define TRACE_LOG(...)   log_print(LOG_LEVEL_TRACE, __VA_ARGS__)

#endif // LOG_TASK_H
