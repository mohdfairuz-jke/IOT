#define BLYNK_TEMPLATE_ID   "TMPLxxxxxx"
#define BLYNK_TEMPLATE_NAME "SmartHomeSystem"
#define BLYNK_AUTH_TOKEN    "YourAuthToken"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

// Maklumat WiFi
char ssid[] = "NamaWiFiAnda";
char pass[] = "PasswordWiFiAnda";

// Konfigurasi DHT
#define DHTPIN 14          // Pin data DHT11 disambung ke GPIO 14
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

BlynkTimer timer; // Pemasa untuk hantar data secara berkala

// Fungsi untuk membaca sensor dan menghantar ke Blynk
void sendSensorData() {
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // Celcius

  // Semak jika bacaan gagal
  if (isnan(h) || isnan(t)) {
    Serial.println("Gagal membaca dari sensor DHT!");
    return;
  }

  // Hantar data ke Virtual Pin Blynk
  Blynk.virtualWrite(V3, t); // Suhu ke Gauge V3
  Blynk.virtualWrite(V4, h); // Kelembapan ke Gauge V4
  
  Serial.print("Suhu: "); Serial.print(t); Serial.println(" °C");
  Serial.print("Kelembapan: "); Serial.print(h); Serial.println(" %");
}

void setup() {
  Serial.begin(115200);
  
  dht.begin();
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Setkan timer untuk menjalankan fungsi sendSensorData setiap 2000ms (2 saat)
  timer.setInterval(2000L, sendSensorData);
}

void loop() {
  Blynk.run();
  timer.run(); // Menjalankan pemasa Blynk
}
