/**
 * @file app_main.h
 * @brief Application entry point task
 * @date 2026-02-18
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#ifndef APP_MAIN_H
#define APP_MAIN_H

/*******************************
 * INCLUDES
 *******************************/

#include "cmsis_os2.h"   // FreeRTOS wrapper for CMSIS-RTOS2


/*******************************
 * FUNCTION DECLARATIONS
 *******************************/

/**
 * @brief Initialize the main application task.
 *
 * Creates the AppMain task using static allocation.
 * Must be called before vTaskStartScheduler().
 */
void app_main_init(void);

#endif // APP_MAIN_H
