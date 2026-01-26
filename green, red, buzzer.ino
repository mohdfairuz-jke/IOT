/* * Project: Sequential LED and Buzzer Control
 * Green LED: GPIO 1 (5 seconds)
 * Red LED: GPIO 3 (3 seconds)
 * Buzzer: GPIO 5 (2 seconds)
 */

const int greenLED = 1; 
const int redLED = 3;
const int buzzer = 5;

void setup() {
  // Menetapkan semua pin sebagai OUTPUT
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  // 1. Hidupkan Green LED selama 5 saat
  digitalWrite(greenLED, HIGH);
  digitalWrite(redLED, LOW);
  digitalWrite(buzzer, LOW);
  delay(5000); 

  // 2. Hidupkan Red LED selama 3 saat
  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, HIGH);
  digitalWrite(buzzer, LOW);
  delay(3000);

  // 3. Hidupkan Buzzer selama 2 saat
  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, LOW);
  digitalWrite(buzzer, HIGH);
  delay(2000);

  // Padamkan semua sebelum memulakan semula kitaran (opsyenal)
  digitalWrite(buzzer, LOW);
  delay(500); 
}
