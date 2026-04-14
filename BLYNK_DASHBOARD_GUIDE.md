# 📱 Blynk IoT Master Dashboard Guide (Updated)

This guide provides the final configuration for your 3-device Smart Irrigation System.

> [!IMPORTANT]
> **Template Info:**  
> **Template ID:** `TMPL6AgU8jm-x`  
> **Template Name:** `ESP32 WIFI`  
> Ensure all devices use this exact Template ID.

---

## 1. Device Hierarchy (3 Devices)
You will see 3 devices in your Blynk console. Add them all to your mobile dashboard:
1.  **KEBUN** (Master Pump & all Sensors)
2.  **VALVE AB** (Fertilizer Valves)
3.  **VALVE CD** (Water Valves)

---

## 2. Datastream Definitions (V0 to V13)
In **Blynk Console > Datastreams**, ensure these settings:

| Pin | Name | Data Type | Min/Max | Unit | History |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **V0** | Flow Rate | Double | 0 / 5 | **L/sec** | **ON** |
| **V1** | Tank Status | Integer | 0 / 1 | - | OFF |
| **V2** | Nutrient (EC) | Double | 0 / 10 | mS/cm | **ON** |
| **V3** | Valve C | Integer | 0 / 1 | - | OFF |
| **V4** | Valve D | Integer | 0 / 1 | - | OFF |
| **V5** | Valve A | Integer | 0 / 1 | - | **ON** |
| **V6** | Valve B | Integer | 0 / 1 | - | **ON** |
| **V7** | Moisture (%) | Integer | 0 / 100| % | **ON** |
| **V8** | Rain (Daily) | Double | 0 / 500| **mm** | **ON** |
| **V9** | Rain Raw | Integer | 0 / 4095| - | OFF |
| **V10** | Weather | String | - | - | OFF |
| **V11** | Pump Status | Integer | 0 / 1 | - | **ON** |
| **V12** | Lockout | Integer | 0 / 1 | - | OFF |
| **V13** | Manual Mode | Integer | 0 / 2 | - | OFF |

---

## 3. Mobile Widget Configuration
For the most premium look, use these settings:

*   **V12 (System Lockout):** LED Widget. Color: **Bright Red (#FF3B30)**.
*   **V13 (Pump Mode):** Segmented Switch. 0:AUTO, 1:MAN ON, 2:MAN OFF. Color: **Blue (#007AFF)**.
*   **V11 (Pump Status):** LED Widget (or Gauge). Color: **Green (#4CD964)**.
*   **V7 (Moisture):** Gauge Widget. Use a Gradient (Red -> Blue). 
*   **V8 (Rainfall):** Labeled Value. Icon: **Droplet**. Unit: **mm**.
*   **V0 (Flow Rate):** SuperChart or Gauge. Unit: **L/sec**.
*   **Valve Performance Chart (SuperChart):** 
    - Add **V5 (Valve A)**, **V6 (Valve B)**, and **V0 (Flow Rate)**.
    - Set V5/V6 to **Step** chart type to see clear ON/OFF blocks.
    - This allows you to verify that water is flowing (V0 > 0) only when valves are open.

---

## 4. Troubleshooting
*   **Sensors showing "Offline":** This is normal! They sync and then disconnect to save power/data. Check the "Last Reported" time.
*   **Valves showing "Offline":** Check WiFi signal strength. They should stay online permanently.
