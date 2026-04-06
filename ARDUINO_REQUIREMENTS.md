# Arduino IDE Setup & Requirements

This document outlines everything you need to successfully compile and upload the smart irrigation code to your 8 ESP32 modules.

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
| **Blynk** | Volodymyr Shymanskyy | Cloud connectivity and Dashboard |
| **WiFi** | (Built-in) | Network connectivity |
| **Time** | (Built-in) | NTP Time synchronization |

## 3. Upload Settings
When uploading to your ESP32 boards, use these settings under the **Tools** menu:
*   **Board**: "DOIT ESP32 DEVKIT V1" (or your specific ESP32 model)
*   **Upload Speed**: 921600 (or 115200 if you have connection issues)
*   **Flash Frequency**: 80MHz
*   **Core Debug Level**: None

## 4. Common Credentials (Pre-Configured)
All your files are already updated with these settings:
*   **WiFi SSID**: `SurauAl-Irfan`
*   **WiFi Password**: `datangsurau`
*   **Blynk Token**: `MbA2y5hlAv4SpJ7-a-y9CDhSH9d2zfyd`
*   **Timezone**: GMT+8 (Malaysia)

## 5. Troubleshooting
*   **"BlynkSimpleEsp32.h: No such file"**: You haven't installed the Blynk library yet.
*   **Connection Failed**: Ensure your ESP32 is in "Boot Mode" by holding the **BOOT** button while the IDE says "Connecting...".
*   **Time mismatch**: Ensure your WiFi has internet access so the ESP32 can fetch the current time from `pool.ntp.org`.
