/* * Practical Work 3: Controlling 4 LEDs with Blynk & ESP32
 * Make sure to install Blynk Library (by Volodymyr Shymanskyy)
 */

// 1. Masukkan maklumat dari Blynk Console (PENTING!)
#define BLYNK_TEMPLATE_ID "MASUKKAN_TEMPLATE_ID_ANDA"
#define BLYNK_TEMPLATE_NAME "MASUKKAN_TEMPLATE_NAME_ANDA"
#define BLYNK_AUTH_TOKEN "MASUKKAN_AUTH_TOKEN_ANDA"

// 2. Library yang diperlukan
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// 3. Maklumat Wi-Fi
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "NAMA_WIFI_ANDA";     // Letakkan nama WiFi anda
char pass[] = "PASSWORD_WIFI_ANDA"; // Letakkan password WiFi anda

// 4. Definisi Pin LED
const int led1 = 2;
const int led2 = 4;
const int led3 = 5;
const int led4 = 18;

// --- Fungsi Kawalan dari Blynk Apps ---

// Kawal LED 1 melalui Virtual Pin V0
BLYNK_WRITE(V0) {
  int value1 = param.asInt();
  digitalWrite(led1, value1);
  Serial.print("LED 1 Status: ");
  Serial.println(value1);
}

// Kawal LED 2 melalui Virtual Pin V1
BLYNK_WRITE(V1) {
  int value2 = param.asInt();
  digitalWrite(led2, value2);
  Serial.print("LED 2 Status: ");
  Serial.println(value2);
}

// Kawal LED 3 melalui Virtual Pin V2
BLYNK_WRITE(V2) {
  int value3 = param.asInt();
  digitalWrite(led3, value3);
  Serial.print("LED 3 Status: ");
  Serial.println(value3);
}

// Kawal LED 4 melalui Virtual Pin V3
BLYNK_WRITE(V3) {
  int value4 = param.asInt();
  digitalWrite(led4, value4);
  Serial.print("LED 4 Status: ");
  Serial.println(value4);
}

void setup() {
  // Mulakan Serial Monitor
  Serial.begin(115200);

  // Set pin sebagai OUTPUT
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);

  // Sambungkan ke Blynk
  Blynk.begin(auth, ssid, pass);
  Serial.println("Connecting to Blynk...");
}

void loop() {
  Blynk.run(); // Jalankan fungsi Blynk secara berterusan
}
