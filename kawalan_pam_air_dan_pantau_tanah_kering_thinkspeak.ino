#include <WiFi.h>
#include "ThingSpeak.h"

// Maklumat WiFi
const char* ssid = "NAMA_WIFI_ANDA";
const char* password = "PASSWORD_WIFI_ANDA";

// Maklumat ThingSpeak
unsigned long myChannelNumber = XXXXXXX; // Masukkan ID Channel anda
const char * myWriteAPIKey = "TULIS_API_KEY_ANDA";
const char * myReadAPIKey = "BACA_API_KEY_ANDA";

// Pin Sambungan
#define SOIL_PIN 34   // Pin Analog untuk sensor kelembapan tanah
#define RELAY_PIN 26  // Pin Digital untuk Relay Pam Air

// Tetapan Ambang (Threshold)
int thresholdKering = 2000; // Tukar nilai ini mengikut kesesuaian sensor anda (0-4095)

WiFiClient  client;

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); // Pastikan pam mati pada permulaan

  // Sambung ke WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi disambungkan.");
  
  ThingSpeak.begin(client);
}

void loop() {
  // 1. Baca data sensor kelembapan tanah
  int sensorValue = analogRead(SOIL_PIN);
  Serial.print("Nilai Kelembapan: ");
  Serial.println(sensorValue);

  // 2. Baca status kawalan manual dari ThingSpeak (Field 2)
  // Kita baca data terakhir yang dihantar ke Field 2
  int manualControl = ThingSpeak.readIntField(myChannelNumber, 2, myReadAPIKey);

  // 3. Logik Kawalan Pam
  if (manualControl == 1) {
    // Jika di dashboard kita set Field 2 kepada 1, pam akan dipaksa HIDUP
    digitalWrite(RELAY_PIN, HIGH);
    Serial.println("Pam: HIDUP (Kawalan Manual)");
  } 
  else {
    // Jika Field 2 adalah 0, ia akan ikut logik sensor (Auto)
    if (sensorValue > thresholdKering) { 
      digitalWrite(RELAY_PIN, HIGH);
      Serial.println("Pam: HIDUP (Tanah Kering)");
    } else {
      digitalWrite(RELAY_PIN, LOW);
      Serial.println("Pam: MATI (Tanah Lembap)");
    }
  }

  // 4. Hantar data ke ThingSpeak (Memantau)
  ThingSpeak.setField(1, sensorValue);
  
  // Tulis ke ThingSpeak
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

  if(x == 200){
    Serial.println("Data berjaya dihantar ke ThingSpeak.");
  } else {
    Serial.println("Masalah menghantar data. Kod ralat HTTP: " + String(x));
  }

  // ThingSpeak versi percuma perlu delay 15-20 saat
  delay(20000); 
}
