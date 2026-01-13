#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "YOUR_TEMPLATE_NAME"
#define BLYNK_AUTH_TOKEN "YOUR_AUTH_TOKEN"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Wi-Fi Credentials
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";

// Function to receive data from Blynk App
BLYNK_WRITE(V0) {
  int value = param.asInt(); // Get value from Virtual Pin V0
  digitalWrite(2, value);    // Change LED status (On/Off)
}

void setup() {
  pinMode(2, OUTPUT);
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();
}
