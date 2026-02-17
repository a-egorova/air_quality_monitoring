/**
 * @file log_task.c
 * @brief Modular logging service for STM32 + FreeRTOS
 * @date 2026-02-17
 * 
 * @copyright Copyright (c) 2026
 * 
 */

/*******************************
 * INCLUDES
 *******************************/

#include "log_task.h"
#include "stm32f7xx_hal.h"  // For HAL_UART_Transmit
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>


/*******************************
 * STATIC VARIABLES
 *******************************/

typedef struct {
    log_level_t level;
    char msg[LOG_MSG_LEN];
} log_message_t;

static UART_HandleTypeDef *logUart = NULL;
static bool logInitialized = false;

/* Queue static memory */
static StaticQueue_t logQueueStruct;
static uint8_t logQueueStorage[LOG_QUEUE_LEN * sizeof(log_message_t)];
static QueueHandle_t logQueue = NULL;

/* Task static memory */
static StaticTask_t logTaskTCB;
static StackType_t logTaskStack[LOG_TASK_STACK_SIZE];

/*******************************
 * STATIC FUNCTIONS
 *******************************/

// Log task dequeues messages and sends via UART
static void LogTask(void *params)
{
    log_message_t logMsg;
    char prefix[16];

    for (;;)
    {
        if (xQueueReceive(logQueue, &logMsg, portMAX_DELAY) == pdTRUE)
        {
            // Add log level prefix
            switch (logMsg.level)
            {
                case LOG_LEVEL_INFO:  strcpy(prefix, "[INFO] "); break;
                case LOG_LEVEL_WARN:  strcpy(prefix, "[WARN] "); break;
                case LOG_LEVEL_ERROR: strcpy(prefix, "[ERROR] "); break;
                case LOG_LEVEL_TRACE: strcpy(prefix, "[TRACE] "); break;
                default: strcpy(prefix, "[UNK] "); break;
            }

            char buffer[LOG_MSG_LEN + 32];
            snprintf(buffer, sizeof(buffer), "%s%s\r\n", prefix, logMsg.msg);

            if (logUart != NULL)
            {
                HAL_UART_Transmit(logUart, (uint8_t*)buffer, strlen(buffer), HAL_MAX_DELAY);
            }
        }
    }
}

/*******************************
 * GLOBAL FUNCTIONS
 *******************************/

void log_init(UART_HandleTypeDef *uart)
{
    if (logInitialized)
    {
        return;   // Already initialized
    }

    logUart = uart;

    logQueue = xQueueCreateStatic(
        LOG_QUEUE_LEN,
        sizeof(log_message_t),
        logQueueStorage,
        &logQueueStruct
    );

    xTaskCreateStatic(
        LogTask,
        "LogTask",
        LOG_TASK_STACK_SIZE,
        NULL,
        tskIDLE_PRIORITY + 1,
        logTaskStack,
        &logTaskTCB
    );

    logInitialized = true;
}


void log_print(log_level_t level, const char *fmt, ...)
{
    if (logQueue == NULL) return;

    log_message_t msg;
    msg.level = level;

    va_list args;
    va_start(args, fmt);
    vsnprintf(msg.msg, LOG_MSG_LEN, fmt, args);
    va_end(args);

    xQueueSend(logQueue, &msg, 0); // 0 means if the queue is full, the message is dropped immediately
}
