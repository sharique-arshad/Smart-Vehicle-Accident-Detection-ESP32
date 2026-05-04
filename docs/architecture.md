# 🧠 System Architecture – Smart Helmet Accident Detection System

## 📌 Overview

The system is designed as a real-time embedded IoT architecture that integrates multiple sensors, a microcontroller (ESP32), and cloud communication to detect accidents and send alerts.

---

## 🏗️ High-Level Architecture

```text
Sensors → ESP32 Processing → Decision Logic → Alert System → IoT Cloud → User
```

---

## 🔌 Hardware Layer

### Components:

* MPU6050 (Accelerometer + Gyroscope)
* SW420 Vibration Sensor
* Neo-6M GPS Module
* SSD1306 OLED Display
* Buzzer + LED
* Push Button
* ESP32 (Main Controller)

### Function:

* Collects real-time motion and environmental data
* Provides physical alert outputs (LED + buzzer)
* Displays local system status on OLED

---

## ⚙️ Processing Layer (ESP32)

The ESP32 acts as the central processing unit:

### Responsibilities:

* Reads sensor data via I2C, UART, and GPIO
* Computes:

  * Acceleration (g-force)
  * Tilt angles (AngleX, AngleY)
* Executes accident detection logic
* Handles real-time display updates
* Manages WiFi communication with cloud

---

## 🧠 Decision Layer (Accident Detection Logic)

The system uses rule-based sensor fusion:

### Conditions:

* High acceleration (> 2.2g)
* High tilt angle (> 60°)
* Vibration detected

### Decision Rule:

```text
Accident = (High Acceleration + Vibration)
        OR (High Tilt + Vibration)
```

### Purpose:

* Reduce false positives
* Ensure reliable detection

---

## 🚨 Alert Layer

### Local Alerts:

* 🔴 LED blinking
* 🔊 Buzzer siren (active buzzer)

### Remote Alerts:

* IoT push notification via Blynk
* Includes GPS-based Google Maps link

---

## 📡 Communication Layer

### Protocols Used:

* WiFi (ESP32 built-in)
* I2C → MPU6050 + OLED
* UART → GPS module
* Digital GPIO → Vibration, LED, Buzzer

---

## ☁️ Cloud Layer (IoT)

### Platform:

* Blynk IoT

### Features:

* Real-time data monitoring (AX, AY, Angle, Vibration)
* Push notifications
* Remote visibility via mobile app/web dashboard

---

## 🖥️ User Interface Layer

### 1. OLED Display:

* Shows:

  * Acceleration values
  * Tilt angles
  * Vibration status
  * GPS status
  * Accident alerts

### 2. Mobile App:

* Receives notifications
* Displays live sensor data

---

## 🔄 Data Flow

```text
Sensors → ESP32 → Data Processing → Decision Logic
        ↓
   OLED Display (local feedback)
        ↓
   Alert Trigger (LED + Buzzer)
        ↓
   Send Data → Blynk Cloud
        ↓
   User Notification (Mobile App)
```

---

## ⚠️ Fault Tolerance

* System operates without GPS (alerts still triggered)
* OLED ensures local visibility without internet
* Button allows manual reset of alerts

---

## 🚀 Future Improvements

* GSM (SIM800L) for offline alerts
* Battery-powered standalone system
* Machine Learning-based detection
* Compact PCB + enclosure

---

## 🧩 Architecture Type

* Embedded Real-Time System
* Event-driven architecture
* Sensor fusion-based decision system

---

