// ============================================================
//  GROUP TIRA — ESP B (Flow Sensor + Diagnostics)
//  Hardware : ESP32
//  Role     : Monitor water flow + pump health diagnosis
//  Blynk    : V0 = Read valve status | V2 = Flow Rate (L/min)
//             V3 = Hourly raw pulse count
// ============================================================

// ⚠️ ESP B MESTI GUNA TOKEN BERBEZA DARI ESP A
//    Daftar device baru di blynk.cloud → salin token baru ke sini
#define BLYNK_TEMPLATE_ID   "TMPL6Ja9YOoVa"
#define BLYNK_TEMPLATE_NAME "ESP32"
#define BLYNK_AUTH_TOKEN    "YOUR_ESP_B_TOKEN_HERE"   // <-- WAJIB TUKAR

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <HTTPClient.h>

// ── WiFi Credentials ──────────────────────────────────────
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "YOUR_WIFI_SSID";   // <-- TUKAR kepada nama WiFi kau
char pass[] = "YOUR_WIFI_PASS";   // <-- TUKAR kepada password WiFi kau

// ── Google Sheets Script ID (Sheet B) ─────────────────────
// ⚠️ INI MESTI BERBEZA dari Script ID Sheet A
// Dapatkan dari: Extensions > Apps Script > Deploy > Manage Deployments
const String SCRIPT_ID_B = "YOUR_SCRIPT_ID_B_HERE";   // <-- WAJIB TUKAR

// ── Pin Definition ────────────────────────────────────────
const int sensorPin = 19;   // Wayar kuning sensor ke Pin 19
const int ledPin    = 2;    // LED status (HIGH = OK)

// ── Flow Variables ────────────────────────────────────────
volatile long pulseCount      = 0;   // Pulsed counted per second window
volatile long totalPulseSheet = 0;   // Cumulative pulses for Sheets (2h)
volatile long hourlyPulse     = 0;   // Cumulative pulses for hourly Blynk report
float flowRate                = 0.0; // L/min
unsigned long lastFlowMillis  = 0;

// ── Valve Status (from ESP A via Blynk Cloud) ─────────────
int lastValveStatus = 0;   // 0 = Normal (A Open), 1 = Maintenance (B Open)

BlynkTimer timer;

// ── ISR: Count pulses from flow sensor ───────────────────
void IRAM_ATTR pulseCounter() {
  pulseCount++;
  totalPulseSheet++;
  hourlyPulse++;
}

// ── Blynk V0: Receive valve status from ESP A ────────────
BLYNK_WRITE(V0) {
  lastValveStatus = param.asInt();
}

// ── Timer 1: Send real-time flow rate to Blynk (every 1s) ─
void sendFlowRate() {
  unsigned long now      = millis();
  unsigned long duration = now - lastFlowMillis;
  if (duration == 0) return;

  // Formula: flowRate (L/min) = (pulses per second / K-factor)
  // K-factor 7.5 sesuai untuk sensor YF-S201
  flowRate       = ((1000.0 / duration) * pulseCount) / 7.5;
  pulseCount     = 0;
  lastFlowMillis = now;

  Blynk.virtualWrite(V2, flowRate);
}

// ── Timer 2: Send hourly raw pulse to Blynk (every 1h) ───
void sendHourlyPulse() {
  Blynk.virtualWrite(V3, hourlyPulse);
  Serial.print("[Hourly] Raw Pulse: ");
  Serial.println(hourlyPulse);
  hourlyPulse = 0;
}

// ── Timer 3: Pump diagnosis + Sheets log (every 2h) ──────
void performDiagnosis() {
  // Tanya Cloud: status valve sekarang (dari ESP A)
  Blynk.syncVirtual(V0);
  delay(200);   // Bagi masa untuk BLYNK_WRITE(V0) dipanggil

  String pumpHealth;

  if (lastValveStatus == 0) {
    // Mod Normal — Valve A Open, pump sepatutnya ada flow
    if (totalPulseSheet > 10) {
      pumpHealth = "PUMP_OK";
      digitalWrite(ledPin, HIGH);
    } else {
      pumpHealth = "PUMP_FAILURE";
      digitalWrite(ledPin, LOW);
    }
  } else {
    // Mod Maintenance — Valve B Open
    pumpHealth = (totalPulseSheet > 10) ? "MAINTENANCE_OK" : "MAINTENANCE_NO_FLOW";
    digitalWrite(ledPin, LOW);
  }

  // Hantar ke Google Sheets B
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = "https://script.google.com/macros/s/" + SCRIPT_ID_B +
                 "/exec?health=" + pumpHealth + "&pulses=" + String(totalPulseSheet);
    http.begin(url.c_str());
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
    int code = http.GET();
    http.end();
    Serial.println("[Sheets B] " + pumpHealth + " | HTTP: " + String(code));
  }

  // Reset cumulative pulse for next 2h window
  totalPulseSheet = 0;
}

void setup() {
  Serial.begin(115200);

  pinMode(ledPin,    OUTPUT);
  pinMode(sensorPin, INPUT_PULLUP);
  digitalWrite(ledPin, LOW);

  // Attach flow sensor interrupt
  attachInterrupt(digitalPinToInterrupt(sensorPin), pulseCounter, FALLING);

  // Connect to Blynk
  Blynk.begin(auth, ssid, pass);
  digitalWrite(ledPin, HIGH);   // LED ON = connected

  lastFlowMillis = millis();

  // ── Timers ─────────────────────────────────────────────
  timer.setInterval(1000L,      sendFlowRate);     // 1 saat  — flow rate ke Blynk V2
  timer.setInterval(3600000L,   sendHourlyPulse);  // 1 jam   — raw pulse ke Blynk V3
  timer.setInterval(7200000L,   performDiagnosis); // 2 jam   — diagnosis + Google Sheets

  Serial.println("[ESP B] Flow Sensor & Diagnostics Ready.");
}

void loop() {
  Blynk.run();
  timer.run();
}
