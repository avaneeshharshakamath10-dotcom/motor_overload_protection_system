
# Motor Overload Protection System

## Project Overview

The Motor Overload Protection System was developed for **Vachan Electric Vehicle (Vachan Motors Pvt. Ltd.)** to demonstrate motor monitoring and overload protection using embedded systems.

The project uses a microcontroller-based control system with current and temperature sensors to monitor motor operating conditions. When an overload condition is detected, the programmed protection logic controls a relay to disconnect the motor. An OLED display provides real-time operating information and system status.

## Project Objective

- Monitor motor current and temperature.
- Detect motor overload conditions using a predefined current threshold.
- Implement relay-based motor protection.
- Display operating parameters and protection status on an OLED display.
- Demonstrate embedded control techniques relevant to electric vehicle motor systems.

## Hardware Components

| Component | Function |
|---|---|
| ESP32 / microcontroller used | Processes sensor data and controls the system |
| ACS712 current sensor | Measures motor current |
| LM35 temperature sensor | Measures temperature |
| SSD1306 OLED display | Displays measurements and system status |
| Relay module | Controls motor disconnection |
| L298N motor driver | Controls the prototype motor |
| DC motor | Represents the motor under monitoring |

## Software and Technologies

- Embedded C/C++
- Arduino IDE
- Microcontroller programming
- Sensor interfacing
- OLED display interfacing using I²C
- Relay-based control logic

## Working Principle

1. **Current sensing:** The ACS712 sensor measures the current drawn by the motor.
2. **Temperature sensing:** The LM35 measures temperature.
3. **Data processing:** The microcontroller reads the sensor values and evaluates the motor's operating condition.
4. **Overload detection:** The measured current is compared with a predefined threshold.
5. **Protection:** When the programmed overload condition is met, the relay control logic disconnects the motor.
6. **Status display:** The OLED displays the measured parameters and protection status.

## Key Features

- Real-time motor current monitoring
- Temperature measurement
- Threshold-based overload detection
- Relay-based motor protection
- OLED-based status monitoring

## Applications

- Electric vehicle motor monitoring prototypes
- Embedded motor protection systems
- Electric motor control demonstrations
- Industrial motor monitoring concepts

## Future Scope

- Integration of voltage and power monitoring
- Adjustable overload protection thresholds
- Fault logging and diagnostic features
- Wireless motor monitoring
- Testing with motor-specific protection settings

## Conclusion

This project demonstrates the application of embedded systems to motor monitoring and overload protection, combining sensor interfacing, microcontroller programming, display interfacing, and relay control in a prototype relevant to electric vehicle applications.

**Project developed for:** Vachan Electric Vehicle / Vachan Motors Pvt. Ltd.

**Note:** This is a prototype-level project. Industrial or vehicle deployment requires appropriate electrical protection, calibration, and validation under actual operating conditions.
