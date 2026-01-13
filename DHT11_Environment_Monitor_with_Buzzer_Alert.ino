/* * Practical Work: DHT11 Environment Monitor with Buzzer Alert
 * Trigger: Buzzer activates if Temp OR Humidity deviates by > 20% from Ambient
 */

#include "DHT.h"

#define DHTPIN 27      // DHT11 connected to GPIO 27
#define DHTTYPE DHT11  // Sensor type DHT 11
#define BUZZER_PIN 14  // Buzzer connected to GPIO 14 (example)

DHT dht(DHTPIN, DHTTYPE);

float ambientTemp;
float ambientHumid;
bool isBaselineSet = false;

void setup() {
  Serial.begin(115200);
  pinMode(BUZZER_PIN, OUTPUT);
  dht.begin();

  Serial.println("--- System Initialized ---");
  Serial.println("Stabilizing sensor for 5 seconds...");
  delay(5000); // Wait for sensor to stabilize

  // Capture ambient values
  ambientTemp = dht.readTemperature();
  ambientHumid = dht.readHumidity();

  if (isnan(ambientTemp) || isnan(ambientHumid)) {
    Serial.println("Failed to read from DHT sensor! Check wiring.");
  } else {
    isBaselineSet = true;
    Serial.println("=== AMBIENT BASELINE SET ===");
    Serial.print("Ambient Temp: "); Serial.print(ambientTemp); Serial.println(" C");
    Serial.print("Ambient Humidity: "); Serial.print(ambientHumid); Serial.println(" %");
    Serial.println("Monitoring for > 20% deviation...");
    Serial.println("--------------------------------");
  }
}

void loop() {
  if (!isBaselineSet) return;

  // Read current values
  float currentTemp = dht.readTemperature();
  float currentHumid = dht.readHumidity();

  if (isnan(currentTemp) || isnan(currentHumid)) return;

  // Calculate 20% deviation limits
  float tempThreshold = ambientTemp * 0.20;
  float humidThreshold = ambientHumid * 0.20;

  // Check conditions (Absolute difference > 20% of ambient)
  bool tempAlert = abs(currentTemp - ambientTemp) > tempThreshold;
  bool humidAlert = abs(currentHumid - ambientHumid) > humidThreshold;

  // Debugging Message
  Serial.print("Temp: "); Serial.print(currentTemp); Serial.print(" C | ");
  Serial.print("Humid: "); Serial.print(currentHumid); Serial.print(" %");

  if (tempAlert || humidAlert) {
    Serial.println(" -> [ ALERT: DEVIATION DETECTED! ]");
    
    // Buzzer sequence
    digitalWrite(BUZZER_PIN, HIGH);
    delay(100);
    digitalWrite(BUZZER_PIN, LOW);
    delay(100);
  } else {
    Serial.println(" -> [ Status: Normal ]");
    digitalWrite(BUZZER_PIN, LOW);
  }

  delay(2000); // DHT11 update interval
}
