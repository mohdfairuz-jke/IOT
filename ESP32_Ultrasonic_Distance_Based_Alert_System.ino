// Name: 
// Reg.Num:

// Pin Definitions
const int trigPin = 4;
const int echoPin = 2;
const int led1 = 12;
const int led2 = 14;
const int led3 = 27;
const int buzzer = 26;

// Distance Thresholds (Adjust these values as needed)
const int minThreshold = 10;  // Below 10cm
const int midThreshold = 30;  // Between 10cm and 30cm
const int maxThreshold = 60;  // Above 30cm up to 60cm

void setup() {
  Serial.begin(115200); // ESP32 typically uses 115200 baud
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(buzzer, OUTPUT);
  
  Serial.println("System Initialized...");
}

void loop() {
  long duration, cm;

  // Triggering the sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  cm = duration * 0.034 / 2; // Standard formula for CM

  // Debugging Messages
  Serial.print("Current Distance: ");
  Serial.print(cm);
  Serial.println(" cm");

  if (cm <= minThreshold) {
    // --- Minimum Distance: Fast Blinking ---
    Serial.println("Status: CRITICAL - Minimum Distance!");
    controlSignals(HIGH, 100, 1000); // 100ms interval, 1kHz tone
  } 
  else if (cm > minThreshold && cm <= midThreshold) {
    // --- Middle Distance: Slow Blinking ---
    Serial.println("Status: WARNING - Middle Distance");
    controlSignals(HIGH, 500, 500);  // 500ms interval, 500Hz tone
  } 
  else if (cm > midThreshold && cm <= maxThreshold) {
    // --- Maximum Distance: Idle/Steady ---
    Serial.println("Status: SAFE - Maximum Distance");
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    tone(buzzer, 200, 50); // Short beep
    delay(1000);
  } 
  else {
    // Out of range
    Serial.println("Status: IDLE - No Object Detected");
    allOff();
    delay(500);
  }
}

// Function to handle Blinking and Tones
void controlSignals(int state, int interval, int freq) {
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  tone(buzzer, freq);
  delay(interval);
  
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  noTone(buzzer);
  delay(interval);
}

void allOff() {
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  noTone(buzzer);
}


