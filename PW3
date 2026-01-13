const int relayPin = 18;
const int btnPin = 5;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(btnPin,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int btn_state = digitalRead(btnPin);
  if(btn_state == HIGH){
    Serial.println("RLY ACTIVATE");
    pinMode(relayPin, OUTPUT);
    digitalWrite(relayPin, LOW);
    delay(1000);
  }else{
    Serial.println("RLY DEACTIVATE");
    pinMode(relayPin,INPUT);
    delay(1000);
  }
} 
