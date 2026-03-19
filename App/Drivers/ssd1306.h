/**
 * @file ssd1306.h
 * @brief 
 * @date 2026-03-19
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#ifndef SSD1306_H
#define SSD1306_H

/*******************************
 * INCLUDES
 *******************************/

#include "stm32f7xx_hal.h"
#include <stdint.h>

/*******************************
 * DEFINES, ENUMS, STRUCTS
 *******************************/

/*******************************
 * FUNCTION DECLARATIONS
 *******************************/

void ssd1306_init(void);
void ssd1306_display_on(void);
void ssd1306_display_off(void);

/*******************************
 * MACROS
 *******************************/

#endif // SSD1306_H
