//Name:
//Reg.Num:
const int echoPin = 2; // Echo Pin of Ultrasonic Sensor 
constintpingPin=3;     // Trigger Pin of Ultrasonic Sensor 

void setup()
{
Serial.begin(9600);       // Starting Serial Communication 
pinMode(pingPin,OUTPUT);  //initialisingpin3asoutput 
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
duration=pulseIn(echoPin,HIGH);           //usingpulsinfunctiontodeterminetotaltime 
inches = microsecondsToInches(duration);  // calling method
cm=microsecondsToCentimeters(duration);   //callingmethod 
Serial.print(inches);
Serial.print("in,"); 
Serial.print(cm); 
Serial.print("cm"); 
Serial.println(); 
delay(100);
}
longmicrosecondsToInches(longmicroseconds) //methodtocovertmicrosectoinches
{
returnmicroseconds/74/2;
}
longmicrosecondsToCentimeters(longmicroseconds)   //methodtocovertmicrosectocentimeters
{
returnmicroseconds/29/2;
}
