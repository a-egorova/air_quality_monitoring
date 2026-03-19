/**
 * @file ssd1306.c
 * @brief 
 * @date 2026-03-19
 * 
 * @copyright Copyright (c) 2026
 * 
 */

/*******************************
 * INCLUDES
 *******************************/

#include "ssd1306.h"
#include "system_config.h"
#include "i2c.h"

/*******************************
 * LOCAL VARIABLES
 *******************************/


/*******************************
 * STATIC FUNCTIONS
 *******************************/
static void ssd1306_write_command(uint8_t cmd)
{
    uint8_t data[2];
    data[0] = 0x00;   // Control byte: command
    data[1] = cmd;

    HAL_I2C_Master_Transmit(&hi2c1, DISPLAY_I2C_ADDRESS << 1, data, 2, HAL_MAX_DELAY);
}

static void ssd1306_write_data(uint8_t *data, size_t size)
{
    uint8_t buffer[129]; // 1 control byte + 128 data max

    buffer[0] = 0x40; // Control byte: data

    for (size_t i = 0; i < size; i++)
    {
        buffer[i + 1] = data[i];
    }

    HAL_I2C_Master_Transmit(&hi2c1, DISPLAY_I2C_ADDRESS << 1, buffer, size + 1, HAL_MAX_DELAY);
}


/*******************************
 * GLOBAL FUNCTIONS
 *******************************/

void ssd1306_display_on(void)
{
    ssd1306_write_command(0xAF);
}

void ssd1306_display_off(void)
{
    ssd1306_write_command(0xAE);
}

void ssd1306_init(void)
{
    HAL_Delay(100); // Power stabilization

    ssd1306_display_off();

    ssd1306_write_command(0x20); // Set Memory Addressing Mode
    ssd1306_write_command(0x00); // Horizontal Addressing Mode

    ssd1306_write_command(0xB0); // Set Page Start Address

    ssd1306_write_command(0xC8); // COM scan direction
    ssd1306_write_command(0x00); // Low column address
    ssd1306_write_command(0x10); // High column address

    ssd1306_write_command(0x40); // Start line address

    ssd1306_write_command(0x81); // Contrast control
    ssd1306_write_command(0x7F);

    ssd1306_write_command(0xA1); // Segment re-map
    ssd1306_write_command(0xA6); // Normal display

    ssd1306_write_command(0xA8); // Multiplex ratio
    ssd1306_write_command(0x3F);

    ssd1306_write_command(0xA4); // Display follows RAM content

    ssd1306_write_command(0xD3); // Display offset
    ssd1306_write_command(0x00);

    ssd1306_write_command(0xD5); // Display clock divide
    ssd1306_write_command(0xF0);

    ssd1306_write_command(0xD9); // Pre-charge period
    ssd1306_write_command(0x22);

    ssd1306_write_command(0xDA); // COM pins config
    ssd1306_write_command(0x12);

    ssd1306_write_command(0xDB); // VCOMH deselect level
    ssd1306_write_command(0x20);

    ssd1306_write_command(0x8D); // Charge pump
    ssd1306_write_command(0x14);

    ssd1306_display_on();
}