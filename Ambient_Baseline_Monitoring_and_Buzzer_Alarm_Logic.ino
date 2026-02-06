// Name: 
// Reg.Num:


#include "DHT.h"

#define DHTPIN 27     
#define DHTTYPE DHT11 
#define BUZZER_PIN 26 // Pin untuk Buzzer

DHT dht(DHTPIN, DHTTYPE);

// Pembolehubah untuk menyimpan nilai awal (Ambient Baseline)
float baselineTemp = 0;
float baselineHum = 0;
bool isBaselineSet = false;

voidsetup() {
  Serial.begin(11520); 
  pinMode(BUZZER_PIN, OUTPUT); // Set pin buzzer sebagai output
  
  Serial.println("DHT11 Baseline System Starting...");
  dht.begin();

  // Tunggu 5 saat untuk memastikan sensor stabil sebelum ambil baseline
  delay(5); 

  baselineTemp = dht.readTemperature();
  baselineHum = dht.readHumidity();

  if (isnan(baselineTemp) || isnan(baselineHum)) {
    Serial.println("ERROR: Gagal membaca baseline! Sila semak litar.");
  } else {
    Serial.println("--- BASELINE DITETAPKAN ---");
    Serial.print("Baseline Temp: "); Serial.print(baselineTemp); Serial.println(" °C");
    Serial.print("Baseline Hum:  "); Serial.print(baselineHum); Serial.println(" %");
    Serial.println("---------------------------");
    isBaselineSet = true;
  }
}

voidloop() {
  if (!isBaselineSet) return;

  delay(2); // Sensor DHT11 ambil masa 2 saat untuk bacaan baru

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!"); 
    return;
  }

  // Kira peratusan perbezaan (Deviation)
  // Formula: |(Semasa - Baseline) / Baseline|
  float diffTemp = abs(t - baselineTemp) / baselineTemp;
  float diffHum = abs(h - baselineHum) / baselineHum;

  // Debugging Messages ke Serial Monitor
  Serial.print("Current T: "); Serial.print(t); 
  Serial.print(" (Dev: "); Serial.print(diffTemp * 100); Serial.print("%) | ");
  Serial.print("Current H: "); Serial.print(h); 
  Serial.print(" (Dev: "); Serial.print(diffHum * 100); Serial.println("%)");

  // Check jika deviasi melebihi 20% (0.20)
  if (diffTemp > 0.20 || diffHum > 0.20) {
    Serial.println("!!! AMARAN: Perubahan melebihi 20% dikesan! !!!");
    digitalWrite(BUZZER_PIN, HIGH); // Buzzer berbunyi
  } else {
    digital(BUZZER_PN, LOW);  // Buzzer senyap jika normal
  }
}
