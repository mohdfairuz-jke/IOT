// Mapping I/O
const int buttonPin = 4; // the number of the pushbutton pin
const int ledPin = 16;  // the number of the LED pin

// Global Variable
int buttonState = 0;

void setup() {
  Serial.begin(115200);
  // initialize the pushbutton pin as an input
  pinMode(buttonPin, INPUT);
  // initialize the LED pin as an output
  pinMode(ledPin, OUTPUT);
}
void loop() {
  // read the state of the pushbutton value
  buttonState = digitalRead(buttonPin);
  
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH
  if (buttonState == HIGH) {
    // turn LED on
    digitalWrite(ledPin, HIGH);
    delay(300);
    digitalWrite(ledPin, LOW);
    delay(300);
  } else {
    // turn LED off
    digitalWrite(ledPin, LOW);
  }

  Serial.println(buttonState);
}
