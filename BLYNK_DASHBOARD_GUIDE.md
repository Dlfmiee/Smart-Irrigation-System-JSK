# 📱 Blynk IoT Master Dashboard Guide

This guide provides the exact configuration needed to build a professional-grade monitoring and control center for your Smart Irrigation System. 

> [!IMPORTANT]
> **Project Credentials**: Ensure all 8 ESP32 modules use the same **Template ID (TMPL67aY-VULb)** and **Template Name (ESP32 WIFI)**, but **DIFFERENT** Auth Tokens (as assigned in the code) to prevent connection conflicts.

---

## 1. Handling Multiple Devices
Since **Syahdiq**, **Abdul**, and **Aieman** now have their own unique identities, they will appear as **separate devices** in your Blynk App.

### How to put them all on ONE Dashboard:
1.  Open your **Blynk Mobile App**.
2.  Switch to **Developer Mode** (wrench icon).
3.  Add a widget (e.g., Gauge for Moisture).
4.  In the widget settings, tap **"Datastream"**.
5.  **THE KEY STEP**: At the top of the Datastream selector, tap on the **Device Name**.
6.  Select the specific device (e.g., "Syahdiq") and then pick the V7 moisture datastream.
7.  Repeat this for each device until your "Master Dashboard" is complete!

---

## 2. Datastream Definitions
Go to **Blynk Console > Templates > ESP32 WIFI > Datastreams**. Configure exactly as follows:

| Pin | Name | Data Type | Min/Max | Description |
| :--- | :--- | :--- | :--- | :--- |
| **V0** | Flow Rate | Double | 0/5 | Water throughput (L/sec) |
| **V1** | Tank Status | Integer | 0/1 | 1=Full, 0=Low |
| **V2** | Nutrient (EC) | Double | 0/10 | Nutritional conductivity (mS/cm) |
| **V3** | Valve C | Integer | 0/1 | Cyberspark (Water Inlet) |
| **V4** | Valve D | Integer | 0/1 | Cyberspark (Water Outlet) |
| **V5** | Valve A | Integer | 0/1 | ALTF4 (Fertilizer Inlet) |
| **V6** | Valve B | Integer | 0/1 | ALTF4 (Fertilizer Outlet) |
| **V7** | Humidity (%) | Integer | 0/100 | Soil moisture percentage |
| **V8** | Rainfall | Double | 0/500 | Daily cumulative total (mm) |
| **V9** | Rain Raw | Integer | 0/4095 | Analog moisture level on sensor |
| **V10** | Weather | String | - | "RAINING" or "NO RAIN" |
| **V11** | Pump | Integer | 0/1 | On/Off Status |
| **V12** | Lockout | Integer | 0/1 | Safety pause (Red = Locked) |
| **V13** | Mode | Integer | 0/2 | 0:Auto, 1:Man-ON, 2:Man-OFF |

---

## 2. Mobile App Widget Configuration
For a stunning, high-end look, use the following widget settings in the **Blynk Mobile App**:

### **A. Master Safety & Mode (Top Priority)**
*   **LED (V12)**: Name: "SYSTEM LOCKOUT". 
    *   *Color*: **Vibrant Red (#FF3B30)**. 
    *   *Logic*: Glows when irrigation is paused by rain/wet soil.
*   **Segmented Switch (V13)**: Name: "MASTER PUMP CONTROL".
    *   *Segments*:
        1. **AUTO** (Value 0) - Default smart logic.
        2. **MAN ON** (Value 1) - Manual Force Start.
        3. **MAN OFF** (Value 2) - Manual Force Stop/Kill Switch.
    *   *Color*: **Ocean Blue (#007AFF)**.

### **B. Live Status Indicators**
*   **LED (V11)**: Name: "PUMP ACTIVE".
    *   *Color*: **Mint Green (#4CD964)**.
*   **Labeled Value (V1)**: Name: "TANK WATER LEVEL".
    *   *Logic*: Use Map settings to show "FULL" for 1 and "LOW" for 0.
    *   *Color*: **Cyan (#5AC8FA)**.

### **C. Environmental Intelligence (Analytical)**
*   **Gauge (V7)**: Name: "SOIL MOISTURE".
    *   *Unit*: **%**.
    *   *Gradient*: Red (0%) -> Yellow (50%) -> Blue (100%).
*   **Labeled Value (V8)**: Name: "DAILY RAINFALL".
    *   *Unit*: **mm**.
    *   *Icon*: "Cloud" or "Droplet".
*   **Gauge (V2)**: Name: "NUTRIENT LEVEL (EC)".
    *   *Unit*: **mS/cm** (Type this in manually).
    *   *Color*: **Gold (#FFD60A)**.

### **D. Manual Valve Overrides**
*   **4x Buttons (V3, V4, V5, V6)**:
    *   *Mode*: Switch (or Push for testing).
    *   *Water Valves (V3, V4)*: **Blue (#007AFF)**.
    *   *Fertilizer Valves (V5, V6)*: **Purple (#AF52DE)**.

---

## 3. Premium Design Aesthetics
1.  **Dark Mode**: Always use "Dark Theme" in Blynk for the most premium feel.
2.  **Grouping**: Place Status LEDs at the very top, followed by the Mode Switch, then Gauges, and manual buttons at the bottom.
3.  **SuperChart**: Add a SuperChart using **V0 (Flow Rate)** and **V7 (Moisture)** to track your system's performance over 24 hours.

---
*Generated for the Smart-Irrigation-System-JSK Project.*
