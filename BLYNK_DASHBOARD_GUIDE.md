# Blynk IoT Dashboard Configuration Guide

Since all 8 ESP32 modules are using the same **Template ID (TMPL67aY-VULb)**, you only need to set up the Datastreams **once** in the Blynk Web Console.

## 1. Create Datastreams
Go to **Developer Zone > Templates > ESP32 WIFI > Datastreams** and add the following:

| Virtual Pin | Name | Data Type | Min/Max | Description |
| :--- | :--- | :--- | :--- | :--- |
| **V0** | Flow Rate E | Double | 0/100 | Flow Sensor E (Flexxy) |
| **V1** | Float Switch | Integer | 0/1 | 1 = Tank Full, 0 = Tank Empty (Eclipse) |
| **V2** | EC Meter | Double | 0/10 | Nutrient Level (ms/cm) (Eclipse) |
| **V3** | Valve C | Integer | 0/1 | Water Inlet Control (Cyberspark) |
| **V4** | Valve D | Integer | 0/1 | Water Outlet Control (Cyberspark) |
| **V5** | Valve A | Integer | 0/1 | Fertilizer Inlet Control (ALTF4) |
| **V6** | Valve B | Integer | 0/1 | Fertilizer Outlet Control (ALTF4) |
| **V7** | Soil Moisture | Integer | 0/100 | Avg Moisture (%) (Syahdiq) |
| **V8** | Daily Rainfall | Double | 0/500 | Daily Total Rain (mm) (Abdul) |
| **V9** | Rain Value | Integer | 0/4095 | Analog Rain Sensor (Aieman) |
| **V10** | Rain Status | String | - | "RAINING" or "NO RAIN" (Aieman) |
| **V11** | Pump Status | Integer | 0/1 | 1 = ON, 0 = OFF (DT Buddy) |
| **V12** | Rain Lockout | Integer | 0/1 | 1 = LOCK (Rainy Day), 0 = READY |
| **V13** | Pump Mode | Integer | 0/2 | 0:AUTO, 1:ON, 2:OFF (DT Buddy) |

## 2. Premium Widget Setup
For a professional, high-end dashboard, we recommend the following layout using the **Blynk Mobile App**:

### **A. Status Overview (Top Row)**
- **LED (V12)**: Name: "SYSTEM STATUS". 
  - *Color*: **RED** (#FF4B2B) when Lockout is ON.
  - *Logic*: Shows if irrigation is paused due to rain.
- **LED (V11)**: Name: "PUMP".
  - *Color*: **CYAN** (#00D2FF) when Pump is running.
- **Labeled Value (V1)**: Name: "TANK LEVEL". 
  - *Display*: Shows "FULL" or "LOW".

### **B. Live Controls (Middle Row)**
- **1x Segmented Switch (V13)**: Name: "MASTER PUMP". 
  - *Values*: 0 (AUTO), 1 (ON), 2 (OFF).
  - *Logic*: Manual override switch.
- **4x Styled Buttons (V3, V4, V5, V6)**: 
  - Use "Push" mode for manual testing.
  - *Colors*: 
    - **Valve A & B (Fertilizer)**: **PURPLE** (#8E2DE2).
    - **Valve C & D (Water)**: **BLUE** (#4facfe).

### **C. Environment Data (Bottom Row)**
- **Gauge (V7)**: Name: "SOIL MOISTURE".
  - *Range*: 0 to 100.
  - *Unit*: %.
  - *Gradient*: Green (Wet) to Red (Dry).
- **Gauge (V2)**: Name: "EC LEVEL".
  - *Range*: 0 to 5.0.
  - *Color*: **GOLD** (#FDC830).
- **Chart (V8, V0)**: 
  - Add a "SuperChart" to track **Daily Rainfall (V8)** and **Flow Rate E (V0)** over time.

## 3. Design Tips for a Stunning App
1.  **Use Dark Mode**: Go to App Settings and enable **Dark Theme**.
2.  **Add Labels**: Use "Headline" widgets to separate "CONTROLS" from "SENSORS".
3.  **Color Unity**: Keep all water-related widgets Blue and fertilizer-related widgets Purple.
4.  **Icons**: Use the "Droplet" icon for valves and "Cloud" icon for rain lockout.

## 4. Important Operational Notes
- **V12 (Rain Lockout)**: This is the global master switch. If you see this LED turned RED, the pump will **NOT** turn on. It will reset automatically at midnight.
- **V11 (Pump Status)**: If the pump turns off suddenly after 15 seconds, check your **Flow Rate E (V0)**. This is the Dry-Run protection triggered by the code.

---
*Created for the Smart-Irrigation-System-JSK Project.*
