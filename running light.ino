/*
 * Project: 3-LED Running Light
 * Interval: 500ms
 * Pins: GPIO 17, 18, 19
 */

// Mendefinisikan pin LED
const int LED1 = 17;
const int LED2 = 18;
const int LED3 = 19;

void setup() {
  // Tetapkan semua pin sebagai OUTPUT
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
}

void loop() {
  // LED 1 Menyala
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  delay(500);

  // LED 2 Menyala
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, LOW);
  delay(500);

  // LED 3 Menyala
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, HIGH);
  delay(500);
}
