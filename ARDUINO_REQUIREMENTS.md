# Arduino IDE Setup & Requirements

This document outlines everything you need to successfully compile and upload the smart irrigation code to your **8 ESP32 modules**.

## 1. Board Support (ESP32)
You must install the ESP32 board package by Espressif:
1.  Open Arduino IDE.
2.  Go to **File > Preferences**.
3.  In "Additional Boards Manager URLs", paste:
    `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
4.  Go to **Tools > Board > Boards Manager**.
5.  Search for **ESP32** and install the version by **Espressif Systems**.

## 2. Required Libraries
Install these libraries via the **Library Manager** (Tools > Manage Libraries):

| Library Name | Author | Purpose |
| :--- | :--- | :--- |
| **Blynk** | Volodymyr Shymanskyy| Cloud connectivity & Mobile App |
| **WiFi** | (Built-in) | ESP32 Network connectivity |
| **Time** | (Built-in) | Real-time scheduling via NTP |
| **HTTPClient** | (Built-in) | Sending data to Google Sheets |
| **WiFiClientSecure** | (Built-in) | Secure HTTPS/SSL for Google |
| **esp_task_wdt** | (Built-in) | Hardware Watchdog (Auto-Reboot) |

## 3. Deployment Checklist (Which Code Goes Where?)

| Node No. | File Name | Target Hardware |
| :--- | :--- | :--- |
| 1 | **Flexxy (Flow E)** | ESP32 + Flow Sensor E |
| 2 | **Eclipse (Tank/EC)** | ESP32 + Float Switch + EC Meter |
| 3 | **Cyberspark (Vaulve CD)**| ESP32 + 2x Relays (Water) |
| 4 | **ALTF4 (Valve AB)** | ESP32 + 2x Relays (Fertilizer) |
| 5 | **Syahdiq (Moisture)** | ESP32 + 3x Soil Sensors |
| 6 | **Abdul (Rain Gauge)** | ESP32 + Tipping Bucket Gauge |
| 7 | **Aieman (Rain Sensor)** | ESP32 + Analog Rain Sensor |
| 8 | **DT Buddy (Pump)** | ESP32 + Main Pump Relay |

## 4. Upload Settings
When uploading, use these settings under the **Tools** menu:
*   **Board**: "DOIT ESP32 DEVKIT V1" 
*   **Upload Speed**: 921600 (Fast) or 115200 (Stable)
*   **Flash Frequency**: 80MHz
*   **Partition Scheme**: Default 4MB with SPIFFS

## 5. Pre-Configured Credentials
The code is already pre-loaded with these settings:
*   **WiFi SSID**: `SurauAl-Irfan`
*   **WiFi Password**: `datangsurau`
*   **Timezone**: GMT+8 (Malaysia)

## 6. Troubleshooting
- **"BlynkSimpleEsp32.h: No such file"**: Install the **Blynk** library in the Library Manager.
- **Connection Failed**: Hold the **BOOT** button on the ESP32 while it says "Connecting..." until the percentage progress appears.
- **Node disconnected**: Ensure your Surau WiFi signal is strong enough at the installation site.
