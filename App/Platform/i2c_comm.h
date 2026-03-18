/**
 * @file i2c_comm.h
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

#ifndef I2C_COMM_H
#define I2C_COMM_H

/*******************************
 * INCLUDES
 *******************************/

#include <stdint.h>
#include "comm_interface.h"

/*******************************
 * DEFINES, ENUMS, STRUCTS
 *******************************/


/*******************************
 * FUNCTION DECLARATIONS
 *******************************/

/**
 * @brief Read data from an I2C device register.
 *
 * Performs a memory read transaction using the I2C peripheral
 * configured in the communication interface.
 *
 * @param[in]  comm   Pointer to initialized communication interface
 * @param[in]  reg    Register address to read from
 * @param[out] data   Buffer to store received data
 * @param[in]  len    Number of bytes to read
 *
 * @return 0 on success, negative value on error
 */
int8_t i2c_read(comm_interface_t *comm, const uint8_t reg, uint8_t *data, uint16_t len);

/**
 * @brief Write data to an I2C device register.
 *
 * Performs a memory write transaction using the I2C peripheral
 * configured in the communication interface.
 *
 * @param[in] comm   Pointer to initialized communication interface
 * @param[in] reg    Register address to write to
 * @param[in] data   Buffer containing data to send
 * @param[in] len    Number of bytes to write
 *
 * @return 0 on success, negative value on error
 */
int8_t i2c_write(comm_interface_t *comm, const uint8_t reg, const uint8_t *data, uint16_t len);


/*******************************
 * MACROS
 *******************************/

#endif // I2C_COMM_H
