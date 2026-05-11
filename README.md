# 🔥 SOLEIL – Smart Ladle Tilt Monitoring & Safety System

## 📌 Overview

SOLEIL is an IoT-based industrial safety system designed to monitor ladle tilt and prevent hazardous conditions in steel plant environments. It uses real-time sensor data and automated relay control to ensure safe operation.

---

## ⚙️ Features

* 📐 Real-time tilt monitoring using MPU6050
* 🔔 Automatic warning & critical alerts
* ⚡ Relay-based safety shutdown system
* 🌐 IoT dashboard using Blynk
* 📱 Mobile notifications for unsafe conditions

---

## 🛠️ Hardware Used

* ESP32 NodeMCU
* MPU6050 (Gyroscope + Accelerometer)
* Relay Module
* DHT11 (optional)
* Buzzer & LED

---

## 🧠 Working Principle

The MPU6050 continuously measures the tilt angle of the ladle system.
If the tilt exceeds predefined thresholds:

* ⚠️ Warning level → alert triggered
* 🚨 Critical level → relay activates (system shutdown)

All data is sent to the Blynk IoT dashboard for remote monitoring.

---

## 📊 IoT Dashboard

* Tilt Position (Live)
* Temperature Monitoring
* Motor ON/OFF Status
* Mobile Notifications

---

## 📸 Project Images

https://github.com/iamnarenkarthick/SOLEIL-IoT-Safety-System/blob/main/images/hardware_setup.jpg

---

## 🔌 Circuit Diagram

https://github.com/iamnarenkarthick/SOLEIL-IoT-Safety-System/blob/main/circuit/wiring_diagram.png

---

## 💻 Code

Available in `/code` folder

---

## 🚀 Future Improvements

* High-temperature industrial sensors
* PLC integration
* Predictive safety using AI

---

## 👨‍💻 Author

Naren Karthick P
