/**
 * @file system_config.h
 * @brief System-wide configuration parameters for the Air Quality Monitor
 * @date 2026-03-18
 * 
 * This file defines firmware information, debug options, power management,
 * display settings, communication parameters, and optional watchdog
 * configuration for the embedded system.
 * 
 * @copyright Copyright (c) 2026
 */

#ifndef SYSTEM_CONFIG_H
#define SYSTEM_CONFIG_H


/* ============================================================
   FIRMWARE INFORMATION
   ============================================================ */

#define FW_VERSION_MAJOR        0
#define FW_VERSION_MINOR        1
#define FW_VERSION_PATCH        0

#define FW_DEVICE_NAME          "AirQualityMonitor"


/* ============================================================
   DEBUG CONFIGURATION
   ============================================================ */

#define DEBUG_ENABLE            1
#define LOG_ENABLE              1

#define LOG_MSG_LEN             128
#define LOG_QUEUE_LEN           16


/* ============================================================
   POWER MANAGEMENT
   ============================================================ */

#define SYSTEM_LOW_POWER_ENABLE         1

#define SYSTEM_SLEEP_TIMEOUT_MS         5000


/* ============================================================
   DISPLAY CONFIGURATION
   ============================================================ */

#define DISPLAY_I2C_ADDRESS             0x3C
#define DISPLAY_UPDATE_PERIOD_MS        500


/* ============================================================
   COMMUNICATION CONFIG
   ============================================================ */

#define UART_DEBUG_BAUDRATE             115200

#define I2C_TIMEOUT_MS                  100


/* ============================================================
   WATCHDOG (optional future)
   ============================================================ */

#define WATCHDOG_ENABLE                 0
#define WATCHDOG_TIMEOUT_MS             2000


#endif // SYSTEM_CONFIG_H
