# 🚨 Smart Helmet Accident Detection System (ESP32 + IoT)

## 📌 Overview

This project is an IoT-based smart helmet system that detects accidents using sensor fusion and sends real-time alerts with location via cloud notifications.

## ⚙️ Features

* 📊 Real-time motion monitoring (MPU6050)
* 📉 Tilt angle detection (>60°)
* 🔔 Vibration-based impact detection (SW420)
* 🖥️ OLED Display (SSD1306) for real-time data visualization
* 🚨 Smart accident detection logic (multi-condition)
* 📱 IoT alert via Blynk (push notification)
* 📍 Google Maps location sharing (GPS Neo-6M)
* 🔊 Buzzer + LED emergency alert system

## 🧠 Working Principle

Accident is detected when:

* High acceleration (>2.2g) + vibration
  OR
* High tilt angle (>60°) + vibration
* Displays real-time sensor data (AX, AY, Angle, Vibration, GPS status) on OLED

This reduces false positives compared to single-sensor systems.

## 🔌 Hardware Used

* ESP32
* MPU6050 (Accelerometer + Gyroscope)
* SW420 Vibration Sensor
* Neo-6M GPS Module
* SSD1306 OLED Display
* Buzzer (Active)
* LED
* Push Button

## 📡 IoT Integration

* Platform: Blynk IoT
* Sends push notifications to mobile
* Includes Google Maps link:
  https://maps.google.com/?q=lat,lon
  
## 🖥️ OLED Display Functionality

The OLED display provides real-time feedback of system status:

- AX, AY acceleration values  
- Tilt angles (AngleX, AngleY)  
- Vibration status  
- GPS status (Searching / Coordinates)  
- Accident alert + countdown timer  

This allows the system to operate independently even without IoT connectivity.
## 🔧 Pin Configuration

| Component   | ESP32 Pin |
| ----------- | --------- |
| MPU6050 SDA | GPIO21    |
| MPU6050 SCL | GPIO22    |
| SW420       | GPIO34    |
| GPS TX      | GPIO16    |
| GPS RX      | GPIO17    |
| Buzzer      | GPIO25    |
| LED         | GPIO26    |
| Button      | GPIO27    |
| OLED SDA    | GPIO21    |
| OLED SCL    | GPIO22    |

## 🔄 System Flow

1. Read sensor data (MPU + Vibration)
2. Calculate acceleration & tilt angle
3. Apply threshold logic
4. Detect accident
5. Trigger:

   * Buzzer + LED
   * IoT notification
6. Send GPS location (if available)

## 📊 Results

* Accurate accident detection
* Reduced false triggers
* Real-time alert with location

## 🚀 Future Improvements

* GSM module (SIM800L) for no-internet alerts
* Machine Learning-based detection
* Battery-powered compact design
* Enclosure for real-world deployment

## 📸 Project Preview

![Setup](images/setup.png)

## 👨‍💻 Author

Mohammad Sharique Arshad
