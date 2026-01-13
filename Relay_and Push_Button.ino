const int relayPin = 18;
const int btnPin = 5;

void setup() {
  Serial.begin(115200);
  pinMode(btnPin, INPUT);
  pinMode(relayPin, OUTPUT);
  
  // Pastikan relay MATI semasa permulaan (Active Low)
  digitalWrite(relayPin, HIGH); 
}

void loop() {
  int btn_state = digitalRead(btnPin);

  if(btn_state == HIGH) {
    Serial.println("RLY ACTIVATE");
    digitalWrite(relayPin, LOW);  // Hidupkan relay
  } else {
    Serial.println("RLY DEACTIVATE");
    digitalWrite(relayPin, HIGH); // Matikan relay
  }
  
  delay(50); // Delay kecil untuk 'debouncing' butang
}
