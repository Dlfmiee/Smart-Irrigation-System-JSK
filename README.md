# Smart Irrigation System JSK 🌿💧

A high-performance, distributed IoT irrigation solution powered by **8 ESP32 microcontrollers** and the **Blynk Cloud**. This system is designed for maximum reliability by separating core tasks into independent hardware nodes that communicate seamlessly over WiFi.

## 🚀 Key Features
- **Distributed Architecture**: 8 independent nodes handle sensing, valves, and pumping to prevent a single point of failure.
- **Smart Rain Lockout**: Automatically pauses irrigation if it's raining, if soil moisture is already high, or if there is excessive rainfall today.
- **Dry-Run Protection**: The pump automatically cuts power if no water flow is detected within 15 seconds.
- **Optimized Vpin Mapping**: Uses a clean sequence of **13 Virtual Pins (V0-V12)** for real-time monitoring and control.
- **Automated Scheduling**: Independent timers for Water (4x daily) and Fertilizer (1x daily).
- **Consolidated IoT Logging**: Automatically groups data from all 8 nodes into a single **Google Sheet** row every 5 minutes for long-term observation and 7-day testing.
- **Hardware Watchdog**: Built-in self-reboot logic on all ESP32 nodes to recover from freezes or WiFi disconnects automatically.
- **Delta Logging (Blynk Qutoa Protection)**: Only transmits sensor updates to Blynk if a significant change occurs, ensuring 100% operation within the 100k free-tier message limit.

## 📂 Project Structure
The repository contains 8 separate Arduino codebases, each intended for a specific ESP32 node:

| Node Name | Device | Responsibility |
| :--- | :--- | :--- |
| **Flexxy** | Waterflow E | Core flow monitoring and dry-run safety. |
| **Eclipse** | Tank & EC | Monitoring nutrient levels and water tank state. |
| **Cyberspark**| Water Valve | Controls high-pressure water inlet/outlet motorized valves. |
| **ALTF4** | Fert Valve | Controls fertilizer injection valves. |
| **Syahdiq** | Soil Monitor | 3-point average soil moisture measurement. |
| **Abdul** | Rain Gauge | Physical tipping bucket gauge for mm measurement. |
| **Aieman** | Rain Sensor | Instant rain detection and cloud-lockout trigger. |
| **DT Buddy** | **Master Pump**| Central pump controller with safety logic. |

## 📊 Data Observation & Efficiency
The system is protected against service limits while providing reliable long-term reports:
- **Google Sheets**: Unlimited history (5-minute intervals).
- **Blynk IoT**: 60-second baseline update (safely fits 100k quota).
- **Smart Delta**: Redundant updates are suppressed unless sensors detect a meaningful change.

## 🛠️ Getting Started
1. **[Arduino Requirements](file:///c:/Users/Fahmi/Desktop/Smart-Irrigation-System-JSK/ARDUINO_REQUIREMENTS.md)**: How to set up your IDE and libraries.
2. **[Blynk Dashboard Guide](file:///c:/Users/Fahmi/Desktop/Smart-Irrigation-System-JSK/BLYNK_DASHBOARD_GUIDE.md)**: How to set up your mobile and web dashboard.

## ⚖️ License
This project was developed specifically for the **Smart-Irrigation-System-JSK** deployment. All rights reserved.