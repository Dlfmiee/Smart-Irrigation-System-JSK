# Arduino IDE Setup & Requirements

This document outlines everything you need to successfully compile and upload the smart irrigation code to your **7 ESP32 modules**.

## 1. Board Support (ESP32)
You must install the ESP32 board package by Espressif:
1.  Open Arduino IDE.
2.  Go to **File > Preferences**.
3.  In "Additional Boards Manager URLs", paste:
    `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
4.  Go to **Tools > Board > Boards Manager**.
5.  Search for **ESP32** and install the version by **Espressif Systems** (v2.0.0 or higher recommended).

## 2. Required Libraries
Install these libraries via the **Library Manager** (Tools > Manage Libraries):

| Library Name | Author | Purpose |
| :--- | :--- | :--- |
| **Blynk** | Volodymyr Shymanskyy| Cloud connectivity & Mobile App |
| **WiFi** | (Built-in) | ESP32 Network connectivity |
| **Time** | (Built-in) | Real-time scheduling via NTP |
| **HTTPClient** | (Built-in) | Sending data to Google Sheets |
| **WiFiClientSecure** | (Built-in) | Secure HTTPS/SSL for Google Logging |
| **esp_task_wdt** | (Built-in) | Hardware Watchdog (Safety Reset) |

## 3. Deployment Checklist (Which Code Goes Where?)

| Node Name | Identity | Hardware Setup | Blynk Token Required |
| :--- | :--- | :--- | :--- |
| **KEBUN (Master)** | `Pam (DTBuddy)` | ESP32 + Main Pump Relay | Kebun Token |
| **KEBUN (Rain)** | `Tipping_RainSensor` | ESP32 + Tipping Bucket + Probe | Kebun Token |
| **KEBUN (Moisture)**| `MoistureSensor` | ESP32 + 3x Capacitive Sensors | Kebun Token |
| **KEBUN (Tank)** | `TangkiAirAndECMeter`| ESP32 + Float Switch + EC Meter | Kebun Token |
| **KEBUN (Flow E)** | `WaterflowSensorE` | ESP32 + Flow Sensor (Standard) | Kebun Token |
| **VALVE AB** | `ValveWaterFlowAB` | ESP32 + 2x Relays + Flow Sensor | Valve AB Token |
| **VALVE CD** | `ValveWaterFlowCD` | ESP32 + 2x Relays + Flow Sensor | Valve CD Token |
| **TEST MONITOR** | `test` | ESP32 + Flow Sensor (Independent) | Test Token |

## 4. Upload Settings
When uploading, use these settings under the **Tools** menu:
*   **Board**: "DOIT ESP32 DEVKIT V1" 
*   **Upload Speed**: 921600 (Fast) or 115200 (Stable)
*   **Flash Frequency**: 80MHz
*   **Partition Scheme**: Default 4MB with SPIFFS

## 5. System Optimizations
The code is already pre-configured with:
*   **Non-Blocking Logic**: Uses `Blynk.config()` instead of `Blynk.begin()`. This prevents the code from freezing if WiFi is down.
*   **Watchdog (5 min)**: Every node is protected by a hardware timer. If a node freezes for 5 minutes during a critical task, it will automatically reboot.
*   **Timezone**: GMT+8 (Malaysia/Singapore).

## 6. Troubleshooting
- **"Blynk.run() not responding"**: This is often due to a shared Auth Token conflict. Ensure **Valves** have their own unique tokens.
- **Node showing "Offline"**: Normal for sensors! They connect at 7:30 AM/3:30 PM, send data, and then disconnect to save resources.
- **HTTPS Error**: Ensure you are using `WiFiClientSecure` with `setInsecure()` if logging to Google Sheets.
