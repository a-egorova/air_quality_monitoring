/**
 * @file tasks_config.h
 * @brief FreeRTOS task configuration for Air Quality Monitor
 * @date 2026-03-18
 * 
 * This file defines task priorities, stack sizes, and periodicities
 * for the main application, sensor subsystem, display subsystem,
 * and logging/debug tasks.
 * 
 * Task priorities must be within 0 .. (configMAX_PRIORITIES - 1)
 * according to FreeRTOS rules.
 * 
 * @copyright Copyright (c) 2026
 */

#ifndef TASKS_CONFIG_H
#define TASKS_CONFIG_H

/************************************************************
 * FREERTOS PRIORITY MAP
 * Higher number = higher priority
 *
 * 4  Critical system tasks
 * 3  High priority
 * 2  Normal tasks
 * 1  Low priority
 * 0  Idle-like / background tasks
 ************************************************************/

#define TASK_PRIO_LOW        1
#define TASK_PRIO_NORMAL     2
#define TASK_PRIO_HIGH       3
#define TASK_PRIO_CRITICAL   4

/* ============================================================
   APP MAIN TASK
   ============================================================ */

#define APP_MAIN_TASK_STACK_SIZE   512  // TODO: needs to be adjusted
#define APP_MAIN_TASK_PRIORITY     TASK_PRIO_NORMAL
#define APP_MAIN_TASK_PERIOD_MS    1000


/* ============================================================
   SENSOR SUBSYSTEM
   ============================================================ */

#define ENV_SENSOR_TASK_STACK_SIZE     512
#define ENV_SENSOR_TASK_PRIORITY       TASK_PRIO_NORMAL
#define ENV_SENSOR_TASK_PERIOD_MS      1000


// /* ============================================================
//    DISPLAY SUBSYSTEM
//    ============================================================ */

// #define DISPLAY_TASK_STACK_SIZE    512
// #define DISPLAY_TASK_PRIORITY      TASK_PRIO_LOW
// #define DISPLAY_TASK_PERIOD_MS     500


/* ============================================================
   LOGGING / DEBUG
   ============================================================ */

#define LOG_TASK_STACK_SIZE        512
#define LOG_TASK_PRIORITY          TASK_PRIO_LOW

#endif