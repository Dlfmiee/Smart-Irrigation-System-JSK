# 🌊 Smart Irrigation System (JSK Project)

A decentralized, intelligent irrigation and fertilization system powered by 8 independent ESP32 nodes and the Blynk IoT Cloud.

## 🚀 System Architecture
The system is built on a **distributed "Safety First" architecture**. Unlike traditional master-slave systems, each node in this network is smart enough to act on its own while staying synchronized via the Blynk Cloud.

### 🛰️ The 8 Operation Nodes:
1.  **DT Buddy (Pam)**: The Master Pump Controller (Manual Override + 30m Safety Cap).
2.  **Aieman (Rain Sensor)**: High-speed storm detection (5s timing).
3.  **Syahdiq (Moisture Sensor)**: Multi-point soil humidity monitoring (0–100% scale).
4.  **Abdul (Tipping Bucket)**: Accumulative daily rainfall measurement (mm).
5.  **Flexxy (Waterflow E)**: Real-time flow monitoring and Dry-Run protection.
6.  **Eclipse (Tank & EC)**: Nutrient level (mS/cm) and high-precision float monitoring.
7.  **Cyberspark (Valve C/D)**: Water inlet/outlet management (4 PM Session).
8.  **ALTF4 (Valve A/B)**: Fertilizer inlet/outlet management (8 AM Session).

---

## 📅 Scheduled Operations
The system runs two primary automated sessions per day:

*   **08:00 AM (Fertilizing)**: Node **ALTF4** opens valves A & B for **30 minutes**.
*   **04:00 PM (Watering)**: Node **Cyberspark** opens valves C & D for **30 minutes**.

---

## 🛡️ Integrated Safety Logic
*   **Global Rain Lockout (V12)**: Sensing nodes (Aieman, Syahdiq, Abdul) use the **Blynk REST API Bridge** to instantly signal a system-wide lockout if a hazard (rain/saturated soil) is detected.
*   **Dry-Run Protection**: The Pump (`DTBuddy`) monitors the flow rate from `Flexxy`. If no water is detected 15 seconds after starting, the pump immediately shuts down to protect the hardware.
*   **3-State Master Switch (V13)**: Gives the owner total control between **AUTO**, **FORCE ON**, and **FORCE OFF** modes.
*   **Hardware Watchdog**: All nodes feature a 30-second self-reboot timer if the code hangs.

---

## ⚙️ Configuration
*   **WIFI SSID**: `WiFi JSK`
*   **WIFI Pass**: `vhwau35565`
*   **Timezone**: GMT+8 (Malaysia)
*   **Time Sync**: Automatically synchronized via NTP.

---

## 📂 Documentation
- **[Dashboard Guide](file:///c:/Users/Fahmi/Desktop/Smart-Irrigation-System-JSK/BLYNK_DASHBOARD_GUIDE.md)**: How to set up the mobile app.
- **[Process Flow](file:///c:/Users/Fahmi/Desktop/Smart-Irrigation-System-JSK/PROCESS_FLOW.md)**: Deep dive into the logic and timing.
- **[Arduino Requirements](file:///c:/Users/Fahmi/Desktop/Smart-Irrigation-System-JSK/ARDUINO_REQUIREMENTS.md)**: Libraries and hardware pins.

---
*Created and maintained for the Smart-Irrigation-System-JSK Project.*