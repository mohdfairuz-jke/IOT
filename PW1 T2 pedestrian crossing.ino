/*
 * Project: Smart Pedestrian Crossing
 * Sequence: Green -> Yellow -> Red (2s each)
 * Post-sequence: Buzzer sounds twice
 */

// Definisi Pin GPIO
const int greenLED = 17;
const int yellowLED = 18;
const int redLED = 19;
const int buzzer = 5;

void setup() {
  // Tetapkan semua pin sebagai output
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  // 1. LAMPU HIJAU (2 Saat)
  digitalWrite(greenLED, HIGH);
  digitalWrite(yellowLED, LOW);
  digitalWrite(redLED, LOW);
  delay(2000);

  // 2. LAMPU KUNING (2 Saat)
  digitalWrite(greenLED, LOW);
  digitalWrite(yellowLED, HIGH);
  digitalWrite(redLED, LOW);
  delay(2000);

  // 3. LAMPU MERAH (2 Saat)
  digitalWrite(greenLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(redLED, HIGH);
  delay(2000);

  // Padamkan semua lampu sebelum bunyi buzzer
  digitalWrite(redLED, LOW);

  // 4. BUZZER BERBUNYI DUA KALI
  // Bunyi pertama
  digitalWrite(buzzer, HIGH);
  delay(300); 
  digitalWrite(buzzer, LOW);
  delay(200); // Jeda pendek antara bunyi

  // Bunyi kedua
  digitalWrite(buzzer, HIGH);
  delay(300);
  digitalWrite(buzzer, LOW);

  // Tunggu sebentar sebelum mengulang kitaran semula
  delay(1000);
}
