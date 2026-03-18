/**
 * @file i2c_comm.c
 * @brief I2C communication interface implementation
 * @date 2026-03-18
 *
 * Provides I2C-based read and write functions that operate on the
 * generic communication interface structure.
 *
 * These functions are intended to be assigned to a comm_interface_t
 * instance and used by higher-level drivers (e.g., sensors).
 *
 * @copyright Copyright (c) 2026
 */

/*******************************
 * INCLUDES
 *******************************/

#include "i2c_comm.h"
#include "stm32f7xx_hal.h"


/*******************************
 * LOCAL VARIABLES
 *******************************/


/*******************************
 * STATIC FUNCTIONS
 *******************************/


/*******************************
 * GLOBAL FUNCTIONS
 *******************************/

int8_t i2c_read(comm_interface_t *comm, const uint8_t reg, uint8_t *data, uint16_t len)
{
    if (!comm || !data) return -1;

    HAL_StatusTypeDef status;
    status = HAL_I2C_Mem_Read(comm->cfg.i2c.hi2c,
                              comm->cfg.i2c.address << 1,
                              reg,
                              I2C_MEMADD_SIZE_8BIT,
                              data,
                              len,
                              HAL_MAX_DELAY);

    return (status == HAL_OK) ? 0 : -1;
}

int8_t i2c_write(comm_interface_t *comm, const uint8_t reg, const uint8_t *data, uint16_t len)
{
    if (!comm || !data) return -1;

    HAL_StatusTypeDef status;
    status = HAL_I2C_Mem_Write(comm->cfg.i2c.hi2c,
                               comm->cfg.i2c.address << 1,
                               reg,
                               I2C_MEMADD_SIZE_8BIT,
                               (uint8_t *)data,
                               len,
                               HAL_MAX_DELAY);

    return (status == HAL_OK) ? 0 : -1;
}
