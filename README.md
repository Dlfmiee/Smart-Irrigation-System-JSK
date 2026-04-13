# 🌊 Smart Irrigation System (JSK Project)

An intelligent, decentralized irrigation and fertilization system powered by 7 ESP32 nodes synchronized via the Blynk IoT Cloud.

## 🚀 System Architecture
The system is built on a **3-Device Blynk Structure** (plus an independent Water Flow Monitor). Each node is smart enough to handle its own schedules while staying connected via a unified cloud dashboard.

### 🛰️ The Master Identities:
1.  **KEBUN (The Hive)**: Consolidates data from the Master Pump, Rain, Moisture, Tank, and Flow sensor nodes.
2.  **VALVE AB (The Fertilizer)**: Manages the 08:00 AM nutrient distribution session.
3.  **VALVE CD (The Watering)**: Manages the 04:00 PM hydration session.
4.  **MONITOR (Independent)**: A standalone high-speed waterflow tracker for 7-day observation.

---

## 📅 Scheduled Operations
The system runs two primary automated sessions per day:

*   **08:00 AM (Fertilizing)**: Node **ALTF4** opens valves A & B for **30 minutes**.
*   **04:00 PM (Watering)**: Node **Cyberspark** opens valves C & D for **30 minutes**.
*   **Reporting**: Sensor nodes wake up at 07:30 AM and 03:30 PM to sync data to the cloud.

---

## 🛡️ "Safety First" Engineering
*   **Global Rain Lockout (V12)**: System-wide safety flag. If rainfall is detected, scheduled irrigation is automatically bypassed.
*   **Hard-Reset Watchdog**: Every ESP32 is protected with a 5-minute hardware watchdog. If a device freezes while connecting to WiFi, it will automatically reboot to restore operations.
*   **Non-Blocking Logic**: Optimized code allows nodes to count pulses and manage status even if the Blynk server is temporarily unreachable.
*   **3-State Control (V13)**: Manual override (AUTO / FORCE ON / FORCE OFF) from the mobile app.

---

## ⚙️ Core Configuration
*   **WIFI SSID**: `WiFi JSK`
*   **WIFI Pass**: `vhwau35565`
*   **Template ID**: `TMPL6AgU8jm-x`
*   **Timezone**: GMT+8 (Malaysia)
*   **Sync Logic**: 15s Reconnection attempts.

---

## 📂 Project Documentation
- **[Dashboard Guide](file:///c:/Users/Fahmi/Desktop/Smart-Irrigation-System-JSK/BLYNK_DASHBOARD_GUIDE.md)**: Datastream and widget setup.
- **[Process Flow](file:///c:/Users/Fahmi/Desktop/Smart-Irrigation-System-JSK/PROCESS_FLOW.md)**: The technical logic and communication maps.
- **[Arduino Requirements](file:///c:/Users/Fahmi/Desktop/Smart-Irrigation-System-JSK/ARDUINO_REQUIREMENTS.md)**: Libraries, pins, and flash settings.

---
*Created and maintained for the Smart-Irrigation-System-JSK Project.*