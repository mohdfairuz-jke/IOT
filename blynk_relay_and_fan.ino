/* * Task: Remote Fan Control System
 * Hardware: ESP32 & Relay Module
 */

#define BLYNK_TEMPLATE_ID   "MASUKKAN_TEMPLATE_ID_ANDA"
#define BLYNK_TEMPLATE_NAME "Remote Fan Control"
#define BLYNK_AUTH_TOKEN    "MASUKKAN_AUTH_TOKEN_ANDA"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Tetapan WiFi
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "NAMA_WIFI_ANDA";
char pass[] = "PASSWORD_WIFI_ANDA";

// Definisi Pin Relay
const int relayPin = 2; 

// Fungsi ini akan dipanggil setiap kali butang di App Blynk ditekan
BLYNK_WRITE(V1) {
  int value = param.asInt(); // Ambil nilai 0 atau 1 dari Blynk
  
  if (value == 1) {
    digitalWrite(relayPin, HIGH); // Hidupkan Relay
    Serial.println("Kipas: ON");
  } else {
    digitalWrite(relayPin, LOW);  // Matikan Relay
    Serial.println("Kipas: OFF");
  }
}

void setup() {
  Serial.begin(115200);
  
  pinMode(relayPin, OUTPUT);
  
  // Secara default, pastikan kipas mati semasa mula
  digitalWrite(relayPin, LOW);

  // Mula sambungan Blynk
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();
}
