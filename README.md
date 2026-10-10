# Multi-Sensor Integrated Monitoring System

A microcontroller-based monitoring unit that reads temperature, distance, IR obstacle and motion sensors in real time and raises a buzzer and LED alert when a threshold is crossed.

## Hardware
- ESP32 development board [or Arduino Uno]
- DHT11 temperature sensor
- HC-SR04 ultrasonic distance sensor
- IR obstacle sensor module
- PIR motion sensor
- Buzzer and LED

## Pin connections
| Component | ESP32 GPIO |
|---|---|
| DHT11 data | 4 |
| HC-SR04 TRIG | 5 |
| HC-SR04 ECHO | 18 (through voltage divider) |
| IR sensor OUT | 19 |
| PIR sensor OUT | 21 |
| Buzzer | 25 |
| LED | 2 (on-board) |

## How it works
1. Every second the firmware reads all four sensors.
2. Distance is measured from the ultrasonic echo pulse width (time-of-flight).
3. Each reading is checked against a threshold: temperature above 35 C, obstacle closer than 20 cm, IR detection, or motion.
4. If any condition is true, the buzzer and LED turn on.
5. All values and the alert status are printed on the Serial Monitor.

## Concepts used
GPIO input/output, digital and timed pulse measurement, sensor interfacing, threshold-based alert logic, serial debugging

## How to run
1. Install Arduino IDE and the ESP32 board package.
2. Install the "DHT sensor library" by Adafruit (Tools → Manage Libraries).
3. Open `multi_sensor_monitor.ino`, select ESP32 Dev Module and the COM port, and upload.
4. Open Serial Monitor at 115200 baud.

## Future improvements
- Show readings on an OLED display (I2C)
- Publish data to a cloud dashboard over MQTT
- Replace delay() with non-blocking timing or FreeRTOS tasks
- 
