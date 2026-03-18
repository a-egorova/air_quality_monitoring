/**
 * @file comm_interface.c
 * @brief Common communication interface for I2C, SPI, and UART
 * @date 2026-03-18
 * 
 * @copyright Copyright (c) 2026
 * 
 */

/*******************************
 * INCLUDES
 *******************************/

#include "i2c_comm.h"
#include "comm_interface.h"


/*******************************
 * LOCAL VARIABLES
 *******************************/


/*******************************
 * STATIC FUNCTIONS
 *******************************/


/*******************************
 * GLOBAL FUNCTIONS
 *******************************/

void comm_interface_i2c_fill(comm_interface_t *comm, 
                            I2C_HandleTypeDef *hi2c, 
                            const uint8_t address)
{
    if (!comm || !hi2c) return;

    /* Set interface type */
    comm->type = COMM_TYPE_I2C;

    /* Assign I2C-specific operations */
    comm->read = i2c_read;
    comm->write = i2c_write;

    /* Bind hardware configuration */
    comm->cfg.i2c.hi2c = hi2c;
    comm->cfg.i2c.address = address;
}

// void comm_interface_spi_fill(comm_interface_t *comm,
//                             SPI_HandleTypeDef *hspi,
//                             GPIO_TypeDef *cs_port,
//                             uint16_t cs_pin)
// {
//     if (!comm || !hspi) return;

//     comm->type = COMM_TYPE_SPI;
//     comm->read = spi_comm_read;
//     comm->write = spi_comm_write;

//     comm->cfg.spi.hspi = hspi;
//     comm->cfg.spi.cs_port = cs_port;
//     comm->cfg.spi.cs_pin = cs_pin;
// }

// void comm_interface_uart_fill(comm_interface_t *comm, 
//                              UART_HandleTypeDef *huart)
// {
//     if (!comm || !huart) return;

//     comm->type = COMM_TYPE_UART;
//     comm->read = uart_comm_read;
//     comm->write = uart_comm_write;

//     comm->cfg.uart.huart = huart;
// }
