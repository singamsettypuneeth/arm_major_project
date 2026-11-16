# ARM Major Project -Adaptive Vehicle Dashboard Simulator

## Overview
This project simulates a vehicle dashboard system using ARM7 LPC2129 microcontroller and CAN protocol communication between two nodes
The system is designed with dual-node architecture to demonstrate real-time vehicle data acquisition, processing, and display.

## System Architecture

### NODE_A - Sensor Node (Transmitter)
- *Microcontroller:* LPC2129 (ARM7)
- *Sensors Interfaced:*
    - LM35 Temperature Sensor (temperature)
    - Ultrasonic Sensor HC-SR04 (fuel Measurement)
    - potentimeter (speed)
- *Communication:* CAN Protocol (CAN1)
- *Function:* Reads sensor data, processes it, and transmits via CAN bus.

### NODE_B - Dashboard Node (Receiver)
- *Microcontroller:* LPC2129 (ARM7)
- *Display:*  PC Terminal via UART
- *Communication:* CAN Protocol 
- *Function:* Receives CAN data from Node A and displays on dashboard (Speed, Temperature, Distance, Fuel).

## Hardware Used
- LPC2129 ARM7 Development Boards x 2
- MCP2551 CAN Transceivers
- HC-SR04 Ultrasonic Sensor
- LM35 Temperature Sensor

## Software & Drivers
- adc_driver.c/.h - ADC and Ultrasonic sensor interfacing
- can1_driver.c/.h - CAN1 initialization and transmission (125 kbps)
- delay.c/.h - Delay functions for microseconds, milliseconds, and seconds
- uart_driver.c - UART for PC display (9600 baud)

## CAN Protocol Configuration
- *Bit Rate:* 125 kbps
- *PCLK:* 60 MHz (VPBDIV = 1)
- *Mode:* Standard Data Frame

## How It Works
1. Node A reads temperature from LM35 via ADC (CH0)
2. Node A measures distance via Ultrasonic sensor using Timer capture
3. Node A packs data into CAN frame and transmits
4. Node B receives CAN frame in ISR
5. Node B displays values on and UART terminal
