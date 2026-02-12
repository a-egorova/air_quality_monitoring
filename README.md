# 🌿 Embedded Air Quality Monitor (STM32 IoT Device)

## 📌 Project Overview

This project is a modular environmental air-quality monitoring system built around STM32 microcontrollers and environmental sensors.  

The device measures particulate matter (PM), CO₂ concentration, temperature, humidity, and barometric pressure, and presents real-time data on an embedded display.

The goal is to evolve the system from an early prototype into a compact, connected, battery-powered embedded product, which involves:

- Embedded firmware architecture
- Sensor integration (I²C / UART)
- Low-power and battery design
- Hardware prototyping → custom PCB
- IoT connectivity concepts
- Testing & validation methodology

For this project, I will be using an STM32 microcontroller, programming in C, FreeRTOS for real-time task management, and CMake as the build system. The project will also involve I²C and UART sensor interfacing, low-power techniques, and modular firmware design to support future hardware and IoT expansions.

Testing is performed throughout all development stages. It is performed using unit tests and modular validation to ensure correct sensor handling, data processing, and RTOS task execution.

⚠️ This is an evolving engineering project developed in multiple stages.

## 📈 Development Progress

| Stage | Status |
|------|--------|
| Stage 1 — Functional Prototype | 🚧 In Progress |
| Stage 2 — Portable Device | ⏳ Planned |
| Stage 2.5 — Bootloader | ⏳ Planned |
| Stage 3 — Custom PCB | ⏳ Planned |
| Stage 4 — IoT Integration | ⏳ Planned |


---

## ⚙️ Hardware

### Stage 1 — Functional Prototype Hardware

- STM32F767 Evaluation Board (at stage 3 will be replaced with a smaller MCU)
- BME280 — Temperature / Humidity / Pressure Sensor
- SCD41 — CO₂ Sensor
- SPS30 — Particulate Matter Sensor
- 1.3" OLED Display (I²C)
- Push Button

### Stage 2+ — Additional Hardware (Portable Device)

- DS3231 RTC (planned for later stage)
- Rechargeable Battery
- Power Regulation Circuitry
- Battery Monitoring / Voltage Measurement

---  

## 🛠️ Development Stages

### 👉 📐 Stage 1 — Functional Prototype (Evaluation Board)

Goal: Validate sensing, firmware structure, and local UI. Sensors connected via breadboard.

Features:

- Sensor integration via I²C and UART
- OLED display output
- Button interaction
- FreeRTOS-based firmware architecture
- Data acquisition and processing
- Debug logging

###   🔋 Stage 2 — Portable Prototype (Battery + RTC)

Goal: Transition to real-world portable device usage.

Additions:

- Battery power supply
- Real-Time Clock (RTC)
- Power monitoring

Engineering Focus:

- Low-power firmware design
- Sleep and wake scheduling
- Timestamped measurements
- Power consumption analysis

### 🔄 Stage 2.5 — Bootloader & Firmware Infrastructure

Goal: Prepare the firmware architecture for safe updates and future product evolution before hardware redesign.

Features:

- Dedicated bootloader implementation
- Flash memory partitioning (bootloader / application)
- Firmware update via UART (initial)
- Application image validation
- Recovery mechanism for failed updates

Engineering Focus:

- Reliable firmware deployment workflow
- Memory layout planning before PCB design
- Separation of bootloader and application builds
- Preparation for future OTA updates (Stage 4)

###   🧩 Stage 3 — Custom Hardware (PCB + Smaller STM32)

Goal: Convert prototype into a compact embedded product.

Changes:

- Selection of a smaller STM32 MCU
- Custom schematic design
- PCB layout and assembly
- Integrated sensor connections
- Dedicated power management circuitry

Engineering Focus:

- Hardware/software co-design
- Production-oriented firmware
- Debug interface planning
- Mechanical and layout considerations

###   🌐 Stage 4 — IoT Integration (Future Expansion)

Goal: Extend the finished device into a connected environmental monitoring node.

Features:

- Communication module (BLE / Wi-Fi / Cellular — TBD)
- Data serialization and communication protocol
- Remote monitoring capabilities
- Firmware extensibility

Engineering Focus:

- Networking stack integration
- Memory and power trade-offs
- Secure data transmission
- OTA update considerations
