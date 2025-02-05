# A02 water level gauge
Simple water level gauge using  multiple A02 (Modbus) ultrasonic
#
This project uses A02 Ultrasonic sensor with Modbus interface on ESP32. On this repositories, i created a simple modbus wrapper for simpler usage.
Using emelianov's modbus library, this project read or write the holding register of the A02 synchronously and output the water level to a LCD.
ESP32 used in this project is connected to RS485 module using ESP32's serial pin.
# Usage
Create a class with modbus object and the address of the A02
- Use readRange function to get real-time measurement.
- Use setAddress to change the current adress of the A02.
