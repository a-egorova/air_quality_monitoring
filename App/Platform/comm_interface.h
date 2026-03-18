/**
 * @file comm_interface.h
 * @brief Common communication interface for I2C, SPI, and UART
 * @date 2026-03-18
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#ifndef COMM_INTERFACE_H
#define COMM_INTERFACE_H


/*******************************
 * INCLUDES
 *******************************/

#include <stdint.h>
#include "stm32f7xx_hal.h"


/*******************************
 * DEFINES, ENUMS, STRUCTS
 *******************************/

typedef enum
{
    COMM_TYPE_I2C,
    COMM_TYPE_SPI,
    COMM_TYPE_UART
} comm_type_t;

typedef struct comm_interface comm_interface_t;

struct comm_interface
{
    comm_type_t type;

    int8_t (*read)(comm_interface_t *comm, uint8_t reg, uint8_t *data, uint16_t len);
    int8_t (*write)(comm_interface_t *comm, uint8_t reg, const uint8_t *data, uint16_t len);

    union
    {
        struct
        {
            I2C_HandleTypeDef *hi2c;
            uint8_t address;
        } i2c;

        // struct
        // {
        //     SPI_HandleTypeDef *hspi;
        //     GPIO_TypeDef *cs_port;
        //     uint16_t cs_pin;
        // } spi;

        // struct
        // {
        //     UART_HandleTypeDef *huart;
        // } uart;

    } cfg;

};


/*******************************
 * FUNCTION DECLARATIONS
 *******************************/

/**
 * @brief Initialize an I2C communication interface.
 *
 * Configures the communication interface structure to use I2C,
 * assigning read/write operations and binding it to the provided
 * I2C peripheral handle and device address.
 *
 * @param[out] comm     Pointer to communication interface to initialize
 * @param[in]  hi2c     Pointer to initialized I2C peripheral handle
 * @param[in]  address  7-bit I2C device address
 */
void comm_interface_i2c_fill(comm_interface_t *comm, I2C_HandleTypeDef *hi2c, const uint8_t address);

// void comm_interface_spi_fill(comm_interface_t *comm, SPI_HandleTypeDef *hspi, GPIO_TypeDef *cs_port, uint16_t cs_pin);
// void comm_interface_uart_fill(comm_interface_t *comm, UART_HandleTypeDef *huart);

/*******************************
 * MACROS
 *******************************/

#endif // COMM_INTERFACE_H
