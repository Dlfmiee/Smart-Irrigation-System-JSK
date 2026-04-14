// ============================================================
//  GROUP TIRA — ESP A (Valve Controller)
//  Hardware : ESP32
//  Role     : Controls Valve A & B + logs to Google Sheets
//  Blynk    : V0 = Maintenance Switch | V1 = Status Label
// ============================================================

#define BLYNK_TEMPLATE_ID   "TMPL6Ja9YOoVa"
#define BLYNK_TEMPLATE_NAME "ESP32"
#define BLYNK_AUTH_TOKEN    "s8j2QVb4NHXgUuL1ut1N7kFm0352dQm4"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <HTTPClient.h>
#include <ESP32Time.h>

// ── WiFi Credentials ──────────────────────────────────────
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Student KML";       // <-- TUKAR jika WiFi berbeza
char pass[] = "wifi@kml";          // <-- TUKAR jika password berbeza

// ── Google Sheets Script ID (Sheet A) ─────────────────────
// Dapatkan dari: Extensions > Apps Script > Deploy > Manage Deployments
const String SCRIPT_ID_A = "AKfycbyXWDTxn0RqHoWPMjYE5rtzB5AEdH_1-PaYhcRWd790eE47dO2xqt5PwjdcZINxyJG8";

// ── Pin Definition ────────────────────────────────────────
const int relayA = 18;   // Valve A (Normally Open wiring)
const int relayB = 19;   // Valve B (Normally Closed wiring)
const int ledRed = 4;    // LED Merah = Mod Maintenance aktif

// ── Objects ───────────────────────────────────────────────
ESP32Time rtc;
BlynkTimer timer;

// ── Send Data to Google Sheets ────────────────────────────
void sendToSheetA(String sA, String sB, String mode) {
  if (WiFi.status() != WL_CONNECTED) return;

  HTTPClient http;
  String url = "https://script.google.com/macros/s/" + SCRIPT_ID_A +
               "/exec?statusA=" + sA + "&statusB=" + sB + "&mode=" + mode;
  http.begin(url.c_str());
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
  int code = http.GET();
  http.end();
  Serial.println("[Sheets A] HTTP Code: " + String(code));
}

// ── Daily Log at 12:00 ────────────────────────────────────
void checkDailyLog() {
  if (rtc.getHour(true) == 12 && rtc.getMinute() == 0) {
    // relayA: HIGH = OPEN  (NO wiring)
    // relayB: HIGH = CLOSED (NC wiring — inverted logic)
    String stA = (digitalRead(relayA) == HIGH) ? "OPEN"   : "CLOSED";
    String stB = (digitalRead(relayB) == HIGH) ? "CLOSED" : "OPEN";
    sendToSheetA(stA, stB, "DAILY_LOG");
    Serial.println("[Daily Log] A=" + stA + " B=" + stB);
  }
}

// ── Blynk V0: Maintenance Toggle ─────────────────────────
BLYNK_WRITE(V0) {
  int mode = param.asInt();

  if (mode == 1) {
    // MOD MAINTENANCE: Tutup A, Buka B
    digitalWrite(relayA, LOW);
    digitalWrite(relayB, LOW);
    digitalWrite(ledRed, HIGH);
    Blynk.virtualWrite(V1, "MODE: MAINTENANCE (B ACTIVE)");
    sendToSheetA("CLOSED", "OPEN", "MAINTENANCE_START");
    Serial.println("[V0] Maintenance ON");
  } else {
    // MOD NORMAL: Buka A, Tutup B
    digitalWrite(relayA, HIGH);
    digitalWrite(relayB, HIGH);
    digitalWrite(ledRed, LOW);
    Blynk.virtualWrite(V1, "MODE: NORMAL (A ACTIVE)");
    sendToSheetA("OPEN", "CLOSED", "MAINTENANCE_END");
    Serial.println("[V0] Normal Mode");
  }
}

void setup() {
  Serial.begin(115200);

  // Set pin modes
  pinMode(relayA, OUTPUT);
  pinMode(relayB, OUTPUT);
  pinMode(ledRed, OUTPUT);

  // Default state: Normal Mode
  digitalWrite(relayA, HIGH);
  digitalWrite(relayB, HIGH);
  digitalWrite(ledRed, LOW);

  // Connect to Blynk
  Blynk.begin(auth, ssid, pass);

  // Sync NTP time (UTC+8)
  configTime(28800, 0, "pool.ntp.org");

  // Timer: Check daily log every minute
  timer.setInterval(60000L, checkDailyLog);

  Serial.println("[ESP A] Valve Controller Ready.");
}

void loop() {
  Blynk.run();
  timer.run();
}
