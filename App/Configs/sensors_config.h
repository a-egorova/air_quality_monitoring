/**
 * @file sensors_config.h
 * @brief Configuration parameters for environmental sensors
 * @date 2026-03-18
 * 
 * This file contains the configurable parameters for sensors
 * used in the environmental monitoring system, including
 * sampling periods, sensor addresses, operational modes, and
 * validation limits for measured data.
 * 
 * @copyright Copyright (c) 2026
 */

#ifndef SENSORS_CONFIG_H
#define SENSORS_CONFIG_H


/* ============================================================
   SENSOR SAMPLING
   ============================================================ */

#define SENSOR_SAMPLE_PERIOD_MS        1000


/* ============================================================
   BME280 CONFIGURATION
   ============================================================ */

/** Primary and secondary I2C addresses for BME280 */
#define BME280_I2C_ADDRESS_PRIMARY     0x76
#define BME280_I2C_ADDRESS_SECONDARY   0x77

/** Oversampling settings for temperature, pressure, and humidity */
#define BME280_OVERSAMPLING_TEMP       1   /**< 1x oversampling for temperature */
#define BME280_OVERSAMPLING_PRESS      1   /**< 1x oversampling for pressure */
#define BME280_OVERSAMPLING_HUM        1   /**< 1x oversampling for humidity */

/** Filter coefficient (for IIR filter) */
#define BME280_FILTER_COEFF            2

/** Standby time between measurements in normal mode (ms) */
#define BME280_STANDBY_TIME            4

/** Sensor operating mode:
 *  0 = sleep, 1 = forced, 3 = normal
 */
#define BME280_MODE                    3   /**< normal mode */

/** BME280 register addresses */
#define BME280_REG_ID                  0xD0
#define BME280_REG_RESET               0xE0
#define BME280_REG_CTRL_HUM            0xF2
#define BME280_REG_STATUS              0xF3
#define BME280_REG_CTRL_MEAS           0xF4
#define BME280_REG_CONFIG              0xF5
#define BME280_REG_PRESS_MSB           0xF7

/** Expected chip ID for verification */
#define BME280_CHIP_ID                 0x60


// /* ============================================================
//    SCD41 (CO2 SENSOR)
//    ============================================================ */

// #define SCD41_I2C_ADDRESS              0x62

// #define SCD41_MEASUREMENT_INTERVAL_S   5


// /* ============================================================
//    SPS30 (PARTICULATE SENSOR)
//    ============================================================ */

// #define SPS30_UART_BAUDRATE            115200

// #define SPS30_SAMPLE_PERIOD_MS         1000


/* ============================================================
   SENSOR DATA VALIDATION
   ============================================================ */

#define SENSOR_TEMP_MIN_C              -40
#define SENSOR_TEMP_MAX_C               85

#define SENSOR_HUM_MIN_PERCENT         0
#define SENSOR_HUM_MAX_PERCENT         100

#define SENSOR_PRESS_MIN_PA            30000
#define SENSOR_PRESS_MAX_PA            110000


#endif // SENSORS_CONFIG_H
