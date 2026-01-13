/* * Practical Work: ESP32 Smart Relay Control
 * Tested for: 4-Channel Relay Module
 */

#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "YOUR_TEMPLATE_NAME"
#define BLYNK_AUTH_TOKEN "YOUR_AUTH_TOKEN"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// WiFi Credentials
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";

// Relay Pins
const int relay1 = 12;
const int relay2 = 13;
const int relay3 = 14;
const int relay4 = 27;

// Function for Relay 1 (V1)
BLYNK_WRITE(V1) {
  int state = param.asInt();
  // Relays are usually Active Low: HIGH = OFF, LOW = ON
  digitalWrite(relay1, state ? LOW : HIGH); 
  Serial.print("Relay 1 is now: ");
  Serial.println(state ? "ON" : "OFF");
}

// Function for Relay 2 (V2)
BLYNK_WRITE(V2) {
  int state = param.asInt();
  digitalWrite(relay2, state ? LOW : HIGH);
}

// Function for Relay 3 (V3)
BLYNK_WRITE(V3) {
  int state = param.asInt();
  digitalWrite(relay3, state ? LOW : HIGH);
}

// Function for Relay 4 (V4)
BLYNK_WRITE(V4) {
  int state = param.asInt();
  digitalWrite(relay4, state ? LOW : HIGH);
}

void setup() {
  Serial.begin(115200);

  // Set pins as OUTPUT
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);

  // STARTUP SAFETY: Force all relays OFF initially
  // (Active Low relays turn OFF when signal is HIGH)
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);

  Blynk.begin(auth, ssid, pass);
  Serial.println("Relay System Online!");
}

void loop() {
  Blynk.run();
}
