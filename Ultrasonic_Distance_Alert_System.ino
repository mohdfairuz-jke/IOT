/*
 * Practical Work: Ultrasonic Distance Alert System
 * LEDs: GPIO 19, 21, 22 | Buzzer: GPIO 23
 * Ultrasonic: Trig 5, Echo 18
 */

const int trigPin = 5;
const int echoPin = 18;
const int led1 = 19;
const int led2 = 21;
const int led3 = 22;
const int buzzer = 23;

long duration;
int distance;

void setup() {
  Serial.begin(115200);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(buzzer, OUTPUT);
  
  Serial.println("System Initialized. Starting Distance Measurement...");
}

void loop() {
  // 1. Measure Distance
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; // Convert to cm

  // 2. Debugging Message
  Serial.print("Current Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // 3. Logic for Table 1
  if (distance > 0 && distance <= 10) {
    // --- Minimum Distance (0-10cm) ---
    Serial.println("Status: MINIMUM DISTANCE - Fast Alert!");
    blinkSystem(100, 2000); // Fast blink, high pitch
  } 
  else if (distance > 10 && distance <= 30) {
    // --- Middle Distance (11-30cm) ---
    Serial.println("Status: MIDDLE DISTANCE - Slow Alert");
    blinkSystem(500, 1000); // Slow blink, medium pitch
  } 
  else if (distance > 30) {
    // --- Maximum Distance (>30cm) ---
    Serial.println("Status: MAXIMUM DISTANCE - System Idle/Beep");
    // All LEDs ON, Single Beep
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    tone(buzzer, 500, 100); 
    delay(1000);
  }
