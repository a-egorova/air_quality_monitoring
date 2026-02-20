/**
 * @file app_main.c
 * @brief Implementation of the main application entry task.
 * @date 2026-02-18
 * 
 * This file contains the static task for supervising other application tasks.
 * The AppMain task is responsible for:
 *  - Initializing application services
 *  - Starting other application tasks
 *  - Performing high-level supervision
 * 
 * @copyright Copyright (c) 2026
 */

/*******************************
 * INCLUDES
 *******************************/

#include "FreeRTOS.h"
#include "main.h"
#include "task.h"
#include "usart.h"

#include "app_main.h"
#include "logging.h"

/*******************************
 * DEFINES, ENUMS
 *******************************/

#define APP_MAIN_STACK_SIZE    256U     /**< Stack size in words; TODO: need adjusting */
#define APP_MAIN_PRIORITY      (tskIDLE_PRIORITY + 2)


/*******************************
 * LOCAL VARIABLES
 *******************************/

static StaticTask_t appMainTCB;             
static StackType_t  appMainStack[APP_MAIN_STACK_SIZE];
static TaskHandle_t appMainHandle = NULL;


/*******************************
 * STATIC FUNCTIONS
 *******************************/

/**
 * @brief Main application task function.
 *
 * This task performs high-level initialization and periodic
 * supervision of the system.
 *
 * @param pvParameters Not used.
 */
static void AppMainTask(void *pvParameters)
{

    /* -------- Application initialization -------- */
    log_init(&huart3);

    /* --------  -------- */
    INFO_LOG("System initialized");
    WARN_LOG("Battery low: %d%%", 75);
    
    /* -------- Main loop -------- */
    for (;;)
    {
        TRACE_LOG("Loop running");
        HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);
        osDelay(1000);
    }
}

/*******************************
 * GLOBAL FUNCTIONS
 *******************************/

void app_main_init(void)
{
    if (!appMainHandle)
        appMainHandle = xTaskCreateStatic(
            AppMainTask,                 /* Task function */
            "AppMain",                   /* Task name */
            APP_MAIN_STACK_SIZE,         /* Stack size (words) */
            NULL,                        /* Task parameter */
            APP_MAIN_PRIORITY,           /* Priority */
            appMainStack,                /* Stack buffer */
            &appMainTCB                  /* TCB buffer */
        );
}
