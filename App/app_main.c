/**
 * @file app_main.c
 * @brief Implementation of the main application entry task.
 * @date 2026-02-18
 * 
 * This file contains the static task for supervising other application tasks.
 * The AppMain task is responsible for:
 *  - Initializing and starting application tasks
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
#include "i2c.h"

#include "app_main.h"
#include "logging.h"
#include "env_sensor_task.h"
#include "ssd1306.h"
#include "tasks_config.h"


/*******************************
 * LOCAL VARIABLES
 *******************************/

static StaticTask_t appMainTCB;             
static StackType_t  appMainStack[APP_MAIN_TASK_STACK_SIZE];
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
    env_sensor_task_init(&hi2c1);
    ssd1306_init();

    /* ---- Start services ---- */


    INFO_LOG("All services started");
    INFO_LOG("System initialized");
    
    /* -------- Main loop -------- */
    for (;;)
    {
        TRACE_LOG("Loop running");
        HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);
        osDelay(pdMS_TO_TICKS(APP_MAIN_TASK_PERIOD_MS));

        ssd1306_display_on();
        HAL_Delay(2000);

        ssd1306_display_off();
        HAL_Delay(2000);
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
            APP_MAIN_TASK_STACK_SIZE,    /* Stack size (words) */
            NULL,                        /* Task parameter */
            APP_MAIN_TASK_PRIORITY,      /* Priority */
            appMainStack,                /* Stack buffer */
            &appMainTCB                  /* TCB buffer */
        );
}
