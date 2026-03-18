/**
 * @file env_sensor_task.h
 * @brief FreeRTOS task to read environmental sensors (BME280, future SCD41, SPS30)
 * @date 2026-03-18
 * 
 * This module implements a FreeRTOS task that periodically reads data
 * from environmental sensors, stores the latest measurements in a
 * thread-safe structure, and provides API for other tasks to access
 * the data safely.
 * 
 * @copyright Copyright (c) 2026
 */

#ifndef ENV_SENSOR_TASK_H
#define ENV_SENSOR_TASK_H

/*******************************
 * INCLUDES
 *******************************/

#include <stdbool.h>
#include <stdint.h>
#include "stm32f7xx_hal.h"


/*******************************
 * DEFINES, ENUMS, STRUCTS
 *******************************/

typedef struct
{
    float temperature;   // °C
    float humidity;      // %
    float pressure;      // hPa
} env_data_t;


/*******************************
 * FUNCTION DECLARATIONS
 *******************************/

/**
 * @brief Initialize environmental sensor task
 * 
 * @param hi2c HAL I2C handle used for BME280 communication
 * @return true if initialization succeeded, false otherwise
 */
bool env_sensor_task_init(I2C_HandleTypeDef *hi2c);

/**
 * @brief Retrieve the latest environmental measurements
 * 
 * Copies the latest sensor values into the provided output structure.
 * 
 * @param out Pointer to env_data_t to receive the latest measurements
 * @return true if data was successfully retrieved, false if mutex was unavailable
 */
bool env_sensor_task_get_data(env_data_t *out);

/*******************************
 * MACROS
 *******************************/

#endif
