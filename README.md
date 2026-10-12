Smart Underground Safety and Communication System(DEEP SAFE)

This is a ESP32-Based Worker Safety Prototype.

Project Overview
l did this for my final-year engineering project presenting  a prototype which is designed to support underground workers' safety through environmental monitoring, proximity detection, GPS positioning, and manual emergency alerts.

This system uses an ESP32 microcontroller to collect sensor readings, process the data, and activate local alerts when configured danger conditions are detected.

Key Features

- Temperature and humidity monitoring: DHT11 sensor.
- Proximity detection: Ultrasonic sensor measures the distance to nearby objects.
- Gas sensor readings: MQ-series sensor provides raw analog readings for experimental monitoring.
- GPS positioning: NEO-6M module provides coordinates when satellite reception is available that is when it has satellite exposure mainly outside.
- Manual SOS: Push button for emergency alerts.
- Local warning system: LED and buzzer provide alerts.
- Display: OLED shows sensor readings and system status.

Hardware Components

- ESP32 development board
- DHT11 temperature and humidity sensor
- MQ-series gas sensor
- HC-SR04 ultrasonic sensor
- NEO-6M GPS module
- OLED display
- LED and buzzer
- SOS push button

Software and Tools

- Embedded C++
- PlatformIO
- Visual Studio Code
- Arduino-compatible ESP32 libraries
- U8g2 OLED display library

Testing and Results

The prototype was tested using USB power in a controlled environment.Though an external power source has been added with a charging port for the lithium battery and a power regulator as well.These haven't been fully tested yet.

The following functions were demonstrated:

- Live temperature and humidity readings
- Ultrasonic distance measurements
- Raw gas sensor ADC readings
- GPS coordinates when a satellite fix was available
- Manual SOS button detection
- LED and buzzer alerts under configured conditions
- OLED display of readings and system status

Limitations

- The prototype has been validated in underground conditions to see whether the sensors will be able to take readings though l tried to create certain conditions that imitate those scenarios.
- GPS positioning depends on satellite reception and may not work underground as is the limitation of gps tracking 
- Gas sensor readings have not been calibrated to gas concentrations in parts per million (ppm)for now l was using the ADC value .
- This system is an educational prototype and is not certified mine-safety equipment.

Future Improvements

- Conduct controlled underground testing.
- Investigate underground communication and indoor positioning methods like LoRa and also make use of the ESP32 wifi funtionality
- Integrate worker breathing or respiratory monitoring so that we can be able to do some breathing analysis 
- Calibrate gas sensing and improve alert thresholds.
- Improve enclosure design, power management, and reliability.

Skills Demonstrated

ESP32 development, embedded C++, sensor integration, UART and I2C communication, analog input processing, GPS integration, hardware troubleshooting, testing, and technical documentation.

Project Status

Final-year engineering project — prototype built, tested, and demonstrated.

Note: This is just an Academic project l did.
Hardware Prototype

The assembled prototype integrates an ESP32-based monitoring system with environmental sensors, ultrasonic distance measurement, GPS positioning, an OLED display, and local LED/buzzer alerts. A manual SOS button allows the user to trigger an emergency alert.

Figure 1: Helmet-mounted hardware prototype of the Smart Underground Safety and Communication System.

 "Helmet prototype" (./Helmet%20prototype.jpg)
