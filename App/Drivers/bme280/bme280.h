/**
 * @file bme280.h
 * @brief BME280 environmental sensor driver
 * @date 2026-03-18
 * 
 * This header defines the BME280 sensor interface, calibration data,
 * and functions to initialize the sensor and read temperature,
 * humidity, and pressure measurements.
 * 
 * @copyright Copyright (c) 2026
 */

#ifndef BME280_H
#define BME280_H

/*******************************
 * INCLUDES
 *******************************/

#include <stdint.h>
#include <stdbool.h>

#include "comm_interface.h"

/*******************************
 * DEFINES, ENUMS, STRUCTS
 *******************************/

/**
 * @brief BME280 sensor calibration data
 * 
 * These values are read from the sensor at initialization and
 * are used to compensate raw temperature, pressure, and humidity readings.
 */
typedef struct
{
    uint16_t dig_T1;
    int16_t  dig_T2;
    int16_t  dig_T3;

    uint16_t dig_P1;
    int16_t  dig_P2;
    int16_t  dig_P3;
    int16_t  dig_P4;
    int16_t  dig_P5;
    int16_t  dig_P6;
    int16_t  dig_P7;
    int16_t  dig_P8;
    int16_t  dig_P9;

    uint8_t  dig_H1;
    int16_t  dig_H2;
    uint8_t  dig_H3;
    int16_t  dig_H4;
    int16_t  dig_H5;
    int8_t   dig_H6;

} bme280_calib_data_t;

typedef struct
{
    comm_interface_t *comm;
    bme280_calib_data_t calib;
    int32_t t_fine; /**< Intermediate value used for temperature compensation */

} bme280_t;

/*******************************
 * FUNCTION DECLARATIONS
 *******************************/

/**
 * @brief Initialize the BME280 sensor
 * 
 * Reads the chip ID, resets the sensor, and retrieves calibration
 * data from non-volatile memory. Prepares the sensor for measurements.
 * 
 * @param dev Pointer to BME280 instance to initialize
 * @return true if initialization succeeded, false otherwise
 */
bool bme280_init(bme280_t *dev);

/**
 * @brief Read compensated temperature, humidity, and pressure
 * 
 * Reads raw sensor values, applies calibration compensation,
 * and returns the measured values in human-readable units.
 * 
 * @param dev Pointer to initialized BME280 instance
 * @param temperature Pointer to float to receive temperature in °C
 * @param humidity Pointer to float to receive relative humidity in %
 * @param pressure Pointer to float to receive pressure in hPa
 * @return true if read and compensation succeeded, false otherwise
 */
bool bme280_read_measurements(bme280_t *dev,
                              float *temperature,
                              float *humidity,
                              float *pressure);

/*******************************
 * MACROS
 *******************************/

#endif