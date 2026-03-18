/**
 * @file env_sensor_task.c
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

/*******************************
 * INCLUDES
 *******************************/

#include <string.h>
#include "stm32f7xx_hal.h"

#include "bme280.h"
#include "env_sensor_task.h"
#include "i2c_comm.h"
#include "logging.h"
#include "sensors_config.h"
#include "tasks_config.h"

#include "semphr.h"


/*******************************
 * LOCAL VARIABLES
 *******************************/

static bme280_t bme;
static SemaphoreHandle_t data_mutex;  // Protects latest_data

static env_data_t latest_data;
static TaskHandle_t env_sensor_task_handle = NULL;

static StaticTask_t envSensorTCB;             
static StackType_t  envSensorStack[ENV_SENSOR_TASK_STACK_SIZE];


/*******************************
 * STATIC FUNCTIONS
 *******************************/

/**
 * @brief FreeRTOS task that reads sensors periodically
 * 
 * This task reads sensor measurements, updates the shared
 * `latest_data` structure, and logs the results.
 * 
 * Designed for slow sensors (~1 Hz).
 * 
 * @param argument Task parameter (unused)
 */
static void environment_task(void *argument)
{
    env_data_t temp;

    for (;;)
    {
        if (bme280_read_measurements(&bme,
                                     &temp.temperature,
                                     &temp.humidity,
                                     &temp.pressure))
        {
            if (xSemaphoreTake(data_mutex, portMAX_DELAY) == pdTRUE)
            {
                latest_data = temp;
                xSemaphoreGive(data_mutex);
            }

            INFO_LOG("Temp: %.2f C | Hum: %.2f %% | Press: %.2f hPa\r\n",
                temp.temperature,
                temp.humidity,
                temp.pressure);
        }
        else
        {
            ERROR_LOG("Failed to read measurements\r\n");
        }

        vTaskDelay(pdMS_TO_TICKS(ENV_SENSOR_TASK_PERIOD_MS));
    }
}

/*******************************
 * GLOBAL FUNCTIONS
 *******************************/

bool env_sensor_task_init(I2C_HandleTypeDef *hi2c)
{
    if (env_sensor_task_handle)
    {
        WARN_LOG("Environment manager already initialized\r\n");
        return true;
    }

    INFO_LOG("Environment manager initialization started\r\n");

    /* Create mutex for shared sensor data */
    data_mutex = xSemaphoreCreateMutex();
    if (data_mutex == NULL)
    {
        ERROR_LOG("Failed to create data mutex\r\n");
        return false;
    }
    INFO_LOG("Data mutex created\r\n");


    /* Initialize BME280 communication interface */
    static comm_interface_t bme_comm;

    bme_comm.type = COMM_TYPE_I2C;
    bme_comm.cfg.i2c.hi2c   = hi2c;
    bme_comm.cfg.i2c.address = BME280_I2C_ADDRESS_PRIMARY;
    bme_comm.read  = i2c_read;
    bme_comm.write = i2c_write;

    bme.comm = &bme_comm;

   /* Initialize BME280 sensor */
    INFO_LOG("Initializing BME280 sensor...\r\n");
    if (!bme280_init(&bme))
    {
        ERROR_LOG("BME280 initialization failed\r\n");
        return false;
    }
    INFO_LOG("BME280 initialized successfully\r\n");

    memset(&latest_data, 0, sizeof(latest_data));
    env_sensor_task_handle = xTaskCreateStatic(
                                            environment_task,
                                            "EnvTask",
                                            ENV_SENSOR_TASK_STACK_SIZE,
                                            NULL,
                                            ENV_SENSOR_TASK_PRIORITY,
                                            envSensorStack,
                                            &envSensorTCB);
    if (env_sensor_task_handle == NULL)
    {
        ERROR_LOG("Failed to create environment task\r\n");
        return false;
    }
    INFO_LOG("Environment task created\r\n");

    INFO_LOG("Environment manager initialization complete\r\n");

    return true;
}

bool env_sensor_task_get_data(env_data_t *out)
{
    if (out == NULL)
        return false;

    if (xSemaphoreTake(data_mutex, pdMS_TO_TICKS(10)) == pdTRUE)
    {
        *out = latest_data;
        xSemaphoreGive(data_mutex);
        return true;
    }

    return false;
}
