// Name:
// Reg.Num:

const int echoPin = 2;     // Echo Pin of Ultrasonic Sensor
const int pingPin = 4;     // Trigger Pin of Ultrasonic Sensor

void setup() {
  Serial.begin(9600);      	// Starting Serial Communication
  pinMode(pingPin, OUTPUT); 	// initialising pin 4 as output
  pinMode(echoPin, INPUT);  	// initialising pin 2 as input
}

void loop() {
  long duration, inches, cm; 

  // Menghantar signal trigger
  digitalWrite(pingPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(pingPin, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(pingPin, LOW);
  
  // Membaca tempoh pantulan ultrasound (gelombang bunyi)
  duration = pulseIn(echoPin, HIGH); 
  
  // Mengubah waktu menjadi jarak
  inches = microsecondsToInches(duration); 
  cm = microsecondsToCentimeters(duration); 
  
  // Menampilkan hasil ke Serial Monitor
  Serial.print(inches);
  Serial.print(" in, "); 
  Serial.print(cm); 
  Serial.println(" cm"); 
  
  delay(100);
}

// Fungsi pertukaran ke Inci
long microsecondsToInches(long microseconds) {
  // Ada spasi antara 'return' dan variable
  return microseconds / 74 / 2;     
  // from datasheet for the PING, there are 73.746 microseconds per inch
}

// Fungsi pertukaran ke Centimeter
long microsecondsToCentimeters(long microseconds) {
  // Ada space antara 'return' dan variable
  return microseconds / 29 / 2;      
//The speed of sound is 29 microseconds per centimeter.
}
