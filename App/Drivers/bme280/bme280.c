/**
 * @file bme280.c
 * @brief BME280 environmental sensor driver
 * @date 2026-03-18
 * 
 * This header defines the BME280 sensor interface, calibration data,
 * and functions to initialize the sensor and read temperature,
 * humidity, and pressure measurements.
 * 
 * @copyright Copyright (c) 2026
 */

/*******************************
 * INCLUDES
 *******************************/

#include "bme280.h"
#include "logging.h"
#include "sensors_config.h"

/*******************************
 * LOCAL VARIABLES
 *******************************/

static bool bme280_inited = false;


/*******************************
 * STATIC FUNCTIONS
 *******************************/

/**
 * @brief Read calibration data from the BME280 sensor
 * 
 * Reads temperature, pressure, and humidity calibration registers
 * from the sensor and stores them in the device struct for later
 * compensation calculations.
 * 
 * @param dev Pointer to the BME280 device instance
 * @return true if calibration data was successfully read
 * @return false if a communication error occurred
 */
static bool read_calibration_data(bme280_t *dev)
{
    uint8_t calib1[26];
    uint8_t calib2[7];

    if (dev->comm->read(dev->comm, 0x88, calib1, 26) != 0)
        return false;

    if (dev->comm->read(dev->comm, 0xE1, calib2, 7) != 0)
        return false;

    dev->calib.dig_T1 = (calib1[1] << 8) | calib1[0];
    dev->calib.dig_T2 = (calib1[3] << 8) | calib1[2];
    dev->calib.dig_T3 = (calib1[5] << 8) | calib1[4];

    dev->calib.dig_P1 = (calib1[7] << 8) | calib1[6];
    dev->calib.dig_P2 = (calib1[9] << 8) | calib1[8];
    dev->calib.dig_P3 = (calib1[11] << 8) | calib1[10];
    dev->calib.dig_P4 = (calib1[13] << 8) | calib1[12];
    dev->calib.dig_P5 = (calib1[15] << 8) | calib1[14];
    dev->calib.dig_P6 = (calib1[17] << 8) | calib1[16];
    dev->calib.dig_P7 = (calib1[19] << 8) | calib1[18];
    dev->calib.dig_P8 = (calib1[21] << 8) | calib1[20];
    dev->calib.dig_P9 = (calib1[23] << 8) | calib1[22];

    dev->calib.dig_H1 = calib1[25];
    dev->calib.dig_H2 = (calib2[1] << 8) | calib2[0];
    dev->calib.dig_H3 = calib2[2];
    dev->calib.dig_H4 = (calib2[3] << 4) | (calib2[4] & 0x0F);
    dev->calib.dig_H5 = (calib2[5] << 4) | (calib2[4] >> 4);
    dev->calib.dig_H6 = calib2[6];

    return true;
}

/**
 * @brief Compensate raw temperature reading
 * 
 * Applies the BME280 compensation formula to the raw ADC temperature
 * value and updates the t_fine field in the device struct.
 * 
 * @param dev Pointer to the BME280 device instance
 * @param adc_T Raw ADC temperature reading from the sensor
 * @return int32_t Compensated temperature scaled as per BME280 datasheet
 */
static int32_t compensate_temperature(bme280_t *dev, int32_t adc_T)
{
    float var1 = (((float)adc_T)/16384.0f - ((float)dev->calib.dig_T1)/1024.0f)
                 * ((float)dev->calib.dig_T2);

    float var2 = ((((float)adc_T)/131072.0f - ((float)dev->calib.dig_T1)/8192.0f) *
                  (((float)adc_T)/131072.0f - ((float)dev->calib.dig_T1)/8192.0f))
                  * ((float)dev->calib.dig_T3);

    dev->t_fine = (int32_t)(var1 + var2);

    return (int32_t)((var1 + var2) * 5.0f + 128.0f) >> 8;
}


/**
 * @brief Compensate raw pressure reading
 * 
 * Applies the BME280 compensation formula to the raw ADC pressure
 * value using the t_fine field previously calculated from temperature.
 * 
 * @param dev Pointer to the BME280 device instance
 * @param adc_P Raw ADC pressure reading from the sensor
 * @return float Compensated pressure in hPa
 */
static float compensate_pressure(bme280_t *dev, int32_t adc_P)
{
    float var1 = ((float)dev->t_fine / 2.0f) - 64000.0f;
    float var2 = var1 * var1 * ((float)dev->calib.dig_P6) / 32768.0f;
    var2 = var2 + var1 * ((float)dev->calib.dig_P5) * 2.0f;
    var2 = (var2 / 4.0f) + (((float)dev->calib.dig_P4) * 65536.0f);
    var1 = (((float)dev->calib.dig_P3) * var1 * var1 / 524288.0f +
            ((float)dev->calib.dig_P2) * var1) / 524288.0f;
    var1 = (1.0f + var1 / 32768.0f) * ((float)dev->calib.dig_P1);

    if (var1 == 0.0f)
        return 0;

    float p = 1048576.0f - (float)adc_P;
    p = (p - (var2 / 4096.0f)) * 6250.0f / var1;
    var1 = ((float)dev->calib.dig_P9) * p * p / 2147483648.0f;
    var2 = p * ((float)dev->calib.dig_P8) / 32768.0f;

    p = p + (var1 + var2 + ((float)dev->calib.dig_P7)) / 16.0f;

    return p / 100.0f;  // hPa
}


/**
 * @brief Compensate raw pressure reading
 * 
 * Applies the BME280 compensation formula to the raw ADC pressure
 * value using the t_fine field previously calculated from temperature.
 * 
 * @param dev Pointer to the BME280 device instance
 * @param adc_P Raw ADC pressure reading from the sensor
 * @return float Compensated pressure in hPa
 */
static float compensate_humidity(bme280_t *dev, int32_t adc_H)
{
    float h = ((float)dev->t_fine) - 76800.0f;

    h = (adc_H - (((float)dev->calib.dig_H4) * 64.0f +
         ((float)dev->calib.dig_H5) / 16384.0f * h)) *
        (((float)dev->calib.dig_H2) / 65536.0f *
        (1.0f + ((float)dev->calib.dig_H6) / 67108864.0f * h *
        (1.0f + ((float)dev->calib.dig_H3) / 67108864.0f * h)));

    h = h * (1.0f - ((float)dev->calib.dig_H1) * h / 524288.0f);

    if (h > 100.0f) h = 100.0f;
    if (h < 0.0f)   h = 0.0f;

    return h;
}


/*******************************
 * GLOBAL FUNCTIONS
 *******************************/

bool bme280_init(bme280_t *dev)
{
    if (bme280_inited)
    {
        WARN_LOG("BME280 already inited\r\n");
        return true;
    }

    if (dev == NULL)
    {
        ERROR_LOG("BME280 init failed\r\n");
        return false;
    }

    /* Check chip ID */
    uint8_t chip_id;
    int8_t rslt = dev->comm->read(dev->comm, BME280_REG_ID, &chip_id, 1);
    if (rslt != 0)
    {
        ERROR_LOG("BME280 ID read failed\r\n");
        return false;
    }

    if (chip_id != BME280_CHIP_ID)
    {
        ERROR_LOG("BME280 ID does not match\r\n");
        return false;
    }

    /* Soft reset */
    uint8_t reset_cmd = 0xB6;
    rslt = dev->comm->write(dev->comm, BME280_REG_RESET, &reset_cmd, 1);
    if (rslt != 0)
    {
        ERROR_LOG("BME280 reset failed\r\n");
        return false;
    }

    vTaskDelay(pdMS_TO_TICKS(10));

    /* Wait for NVM (Non-Volatile Memory) copy to complete */
    uint8_t status;
    do
    {
        rslt = dev->comm->read(dev->comm, BME280_REG_STATUS, &status, 1);
        if (rslt != 0)
        {
            ERROR_LOG("BME280 status read failed after reset\r\n");
            return false;
        }

    } while (status & 0x01);

    /* Read calibration data */
    if (!read_calibration_data(dev))
    {
        ERROR_LOG("BME280 calibration read failed\r\n");
        return false;
    }

    /* Configure humidity oversampling */
    uint8_t ctrl_hum = BME280_OVERSAMPLING_HUM;
    rslt = dev->comm->write(dev->comm, BME280_REG_CTRL_HUM, &ctrl_hum, 1);
    if (rslt != 0)
    {
        ERROR_LOG("BME280 humidity oversampling set failed\r\n");
        return false;
    }

    /* Configure measurement */
    uint8_t ctrl_meas =
        (BME280_OVERSAMPLING_TEMP  << 5) |
        (BME280_OVERSAMPLING_PRESS << 2) |
        (BME280_MODE);

    rslt = dev->comm->write(dev->comm, BME280_REG_CTRL_MEAS, &ctrl_meas, 1);
    if (rslt != 0)
    {
        ERROR_LOG("BME280 measurement set failed\r\n");
        return false;
    }

    /* Configure filter / standby */

    uint8_t config =
        (BME280_STANDBY_TIME << 5) |
        (BME280_FILTER_COEFF << 2);

    rslt = dev->comm->write(dev->comm, BME280_REG_CONFIG, &config, 1);
    if (rslt != 0)
    {
        ERROR_LOG("BME280 config set failed\r\n");
        return false;
    }
    bme280_inited = true;

    INFO_LOG("BME280 init OK\r\n");
    return true;

}

/* ---------------------------------------------------------- */

bool bme280_read_measurements(bme280_t *dev,
                              float *temperature,
                              float *humidity,
                              float *pressure)
{
    uint8_t data[8];

    if (dev->comm->read(dev->comm, BME280_REG_PRESS_MSB, data, 8) != 0)
    {
        ERROR_LOG("BME280 measurement read failed\r\n");
        return false;
    }

    int32_t adc_P = (int32_t)((data[0] << 12) | (data[1] << 4) | (data[2] >> 4));
    int32_t adc_T = (int32_t)((data[3] << 12) | (data[4] << 4) | (data[5] >> 4));
    int32_t adc_H = (int32_t)((data[6] << 8)  | data[7]);
    
    int32_t temp = compensate_temperature(dev, adc_T);
    *temperature = temp / 100.0f;

    *pressure = compensate_pressure(dev, adc_P);
    *humidity = compensate_humidity(dev, adc_H);

    return true;
}

/* ---------------------------------------------------------- */

