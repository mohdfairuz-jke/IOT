//Name:
//Reg.Num:
const int echoPin = 2;     // Echo Pin of Ultrasonic Sensor 
const int pingPin = 3;     // Trigger Pin of Ultrasonic Sensor 

void setup()
{
Serial.begin(9600);       // Starting Serial Communication 
pinMode(pingPin,OUTPUT);  // initialising pin 3 as output 
pinMode(echoPin, INPUT);  // initialising pin 2 as input
}

voidloop()
{
long duration, inches, cm; 
digitalWrite(pingPin,LOW); 
delayMicroseconds(2); 
digitalWrite(pingPin,HIGH); 
delayMicroseconds(10); 
digitalWrite(pingPin,LOW);
  
duration=pulseIn(echoPin,HIGH);           //using pulse in functin onto determine total time, read reflected sound wave
  
inches = microsecondsToInches(duration);  // convert the time into a distances
cm=microsecondsToCentimeters(duration);   // convert the time into a distances 
  
Serial.print(inches);
Serial.print("in,"); 
Serial.print(cm); 
Serial.print("cm"); 
Serial.println(); 
delay(100);
}
longmicrosecondsToInches(longmicroseconds) //method function to conert into inches
{
returnmicroseconds/74/2;  // from datasheet for the PING, there are 73.746 microseconds per inch
}
longmicrosecondsToCentimeters(longmicroseconds)   //method function to covert into centimeters
{
returnmicroseconds/29/2;  //The speed of sound is 29 microseconds per centimeter. 
}
