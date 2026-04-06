# Blynk IoT Dashboard Configuration Guide

Since all 8 ESP32 modules are using the same **Template ID (TMPL67aY-VULb)**, you only need to set up the Datastreams **once** in the Blynk Web Console.

## 1. Create Datastreams
Go to **Developer Zone > Templates > ESP32 WIFI > Datastreams** and add the following:

| Virtual Pin | Name | Data Type | Min/Max | Description |
| :--- | :--- | :--- | :--- | :--- |
| **V0** | Flow Rate E | Double | 0/100 | Flow Sensor E (Flexxy) |
| **V1** | Float Switch | Integer | 0/1 | 1 = Tank Full, 0 = Tank Empty |
| **V2** | EC Meter | Double | 0/10 | Nutrient Level (ms/cm) |
| **V3** | Valve C | Integer | 0/1 | Water Inlet Control |
| **V4** | Valve D | Integer | 0/1 | Water Outlet Control |
| **V5** | Flow Rate C | Double | 0/100 | Flow Sensor C (Cyberspark) |
| **V6** | Flow Rate D | Double | 0/100 | Flow Sensor D (Cyberspark) |
| **V7** | Valve A | Integer | 0/1 | Fertilizer Inlet Control |
| **V8** | Valve B | Integer | 0/1 | Fertilizer Outlet Control |
| **V9** | Flow Rate A | Double | 0/100 | Flow Sensor A (ALTF4) |
| **V10** | Flow Rate B | Double | 0/100 | Flow Sensor B (ALTF4) |
| **V11** | Soil Moisture | Integer | 0/4095 | Avg Moisture (Syahdiq) |
| **V12** | Daily Rainfall | Double | 0/500 | Total Rain (mm) (Abdul) |
| **V13** | Rain Status | String | - | "RAINING" or "NO RAIN" |
| **V14** | Rain Value | Integer | 0/4095 | Analog Rain Sensor (Aieman) |
| **V15** | Pump Status | Integer | 0/1 | 1 = ON, 0 = OFF |
| **V17** | Rain Lockout | Integer | 0/1 | 1 = LOCK (Rainy Day), 0 = READY |

## 2. Recommended Widget Setup
For the most premium-looking dashboard, we recommend these widgets:

### **Main Control Panel**
- **4 LED Widgets**: Assign to **V3, V4, V7, V8** to see which valves are moving.
- **1 Styled Button**: Assign to **V15** (Set to "Display Only" or just use as a status light).
- **1 LED Widget**: Assign to **V17** (Label: "Rain Lockout"). Color it Red when ON.

### **Sensor Readouts**
- **Gauges**: Best for **V11** (Soil Moisture) and **V2** (EC Meter).
- **Labelled Values**: Great for all **Flow Rates (V0, V5, V6, V9, V10)**.
- **Value Display**: Best for **V12** (Rainfall mm).

### **Notifications (Automations)**
The code is designed to trigger **Blynk Events** automatically. You should go to the "Events" tab in the Template and ensure these are allowed:
1. `valve_opened`: Sent when a schedule starts.
2. `pump_error`: Sent if Dry-Run protection (No Flow) is triggered.

## 3. Important Notes
- **V17** is the most important "Master Switch". If it is logic `1`, the pump will refuse to start even if the schedule hits.
- **V15** is the indicator for the Pump. If V15 is ON, the 120-second timer is currently running.
