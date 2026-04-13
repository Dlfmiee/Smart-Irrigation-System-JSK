# System Process Flow: Smart Irrigation JSK 🌿💧

This document explains the technical architecture of the system—how the decentralized ESP32 nodes interact, how safety logic is enforced, and how your data reaches the cloud.

---

## 1. The Distributed Network
The system is **decentralized** and **Blynk-Synchronized**. Nodes communicate with each other by "shouting" status updates to the shared **KEBUN** Master Dashboard or by directly fetching data via the Blynk API.

```mermaid
graph TD
    subgraph Sensing_Layer (Cloud-Shared)
      A[Rain Sensor] -->|V12 Lockout| KEBUN[Master Cloud]
      B[Rain Gauge] -->|Rainfall mm| KEBUN
      C[Soil Sensors] -->|Moisture Avg| KEBUN
      D[Tank Float] -->|V1 Status| KEBUN
    end

    subgraph Control_Layer (Independent Bridge)
      KEBUN <--> P[Master Pump Controller]
      V1[Valve AB Controller] -->|Bridge Sync| P
      V2[Valve CD Controller] -->|Bridge Sync| P
    end

    subgraph Analytics_Layer (HTTPS)
      KEBUN & V1 & V2 -->|HTTPS Post| GS[Google Sheets Log]
    end
```

---

## 2. Daily Irrigation Cycles
The system follows a strict schedule using Internet Time (NTP).

### **Phase A: Fertilizer (Node: ALTF4 / Valve AB)**
- **Time**: 08:00 AM (30 Minutes)
- **Sequence**:
  1. **Valve A** opens (7s delay) -> **Valve B** opens.
  2. The controller "shouts" to the Master Pump via **Blynk Bridge**.
  3. Master Pump detects the signal and starts pumping.
- **Safety**: Locked out if Soil > 80% or Rain Detected.

### **Phase B: Watering (Node: Cyberspark / Valve CD)**
- **Time**: 04:00 PM (16:00) (30 Minutes)
- **Sequence**:
  1. **Valve C** opens (7s delay) -> **Valve D** opens.
  2. The controller "shouts" to the Master Pump via **Blynk Bridge**.
  3. Master Pump starts pumping.
- **Safety**: Locked out if Rain Lockout (V12) is Active.

---

## 3. High-End Safety Architecture
Safety is the #1 priority to prevent plumbing damage or pump burnout.

| Feature | Logic | Result |
| :--- | :--- | :--- |
| **Non-Blocking Reconnect**| Independent Reconnection Timer (15s Check). | Continues irrigation logic even if WiFi/Blynk fluctuates. |
| **Windowed Watchdog** | TWDT Monitoring with 300,000ms timeout. | Automatically reboots any node that freezes during a task. |
| **Safety Lockout (V12)** | Triggered by Tipping Bucket (mm) or Probe. | Instantly pauses all active and future pump cycles. |
| **Bridge Failsafe** | Nodes use HTTP API as a backup to Blynk Bridge. | Ensures the Pump always "hears" when a Valve is open. |
| **Midnight Reset** | Auto-reset cycle at 00:00. | Resets daily rainfall totals to 0 for the next day's calculations. |

---

## 4. Manual UI Control (Blynk V13)
The system includes a **Master Pump Switch** on Virtual Pin **V13** with three operational modes:

| Value | Mode | Description |
| :--- | :--- | :--- |
| **0** | **AUTO** | Default. Pump follows scheduling and valve status. |
| **1** | **MANUAL ON** | Force Start. Pump runs regardless of valve status (Rain safety still applies). |
| **2** | **FORCE OFF** | Hard Stop. Pump will NOT run under any circumstances. |

---

## 5. Metadata & Data Pipeline
Every 15-30 minutes, the nodes report status to your Google Sheets:
1.  **Direct HTTPS**: Every node uses `WiFiClientSecure` to send data to your Google Apps Script.
2.  **Consolidated Logging**: Since multiple nodes share the **KEBUN** token, data is automatically merged in the Blynk Cloud before being logged.
3.  **Flow E Monitoring**: A dedicated waterflow sensor tracks total throughput to aid in detecting long-term leaks or pipe blockages.

---
*Generated for the Smart-Irrigation-System-JSK Project.*
