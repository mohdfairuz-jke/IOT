#define BLYNK_TEMPLATE_ID   "MASUKKAN_ID"
#define BLYNK_TEMPLATE_NAME "Automation Vent"
#define BLYNK_AUTH_TOKEN    "MASUKKAN_TOKEN"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

// Konfigurasi WiFi
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "NAMA_WIFI";
char pass[] = "PASSWORD_WIFI";

// Konfigurasi Pin
#define DHTPIN 4          // Pin DHT11
#define DHTTYPE DHT11     
#define RELAY_PIN 2       // Pin Relay

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

int manualSwitch = 0; // Simpan status butang Blynk

// Fungsi untuk kawalan manual dari App Blynk
BLYNK_WRITE(V1) {
  manualSwitch = param.asInt();
}

void checkSystem() {
  float t = dht.readTemperature(); // Baca suhu

  if (isnan(t)) {
    Serial.println("Gagal membaca sensor DHT!");
    return;
  }

  // LOGIK AUTOMASI & MANUAL
  // Kipas Hidup JIKA (Suhu > 30) ATAU (Butang Blynk ON)
  if (t > 30.0 || manualSwitch == 1) {
    digitalWrite(RELAY_PIN, HIGH);
    Blynk.virtualWrite(V3, "Running"); // Update status di App
  } else {
    digitalWrite(RELAY_PIN, LOW);
    Blynk.virtualWrite(V3, "Stopped"); // Update status di App
  }

  // Hantar data suhu ke Blynk (V2)
  Blynk.virtualWrite(V2, t);
  
  Serial.print("Suhu: ");
  Serial.print(t);
  Serial.println("°C");
}

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  dht.begin();
  
  Blynk.begin(auth, ssid, pass);

  // Tetapkan timer untuk menjalankan fungsi checkSystem setiap 2 saat
  timer.setInterval(2000L, checkSystem);
}

void loop() {
  Blynk.run();
  timer.run();
}
