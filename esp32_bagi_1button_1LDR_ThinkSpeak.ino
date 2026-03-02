#include <WiFi.h>
#include <HTTPClient.h>

// Konfigurasi WiFi
const char* ssid = "NAMA_WIFI_ANDA";
const char* password = "PASSWORD_WIFI_ANDA";

// Konfigurasi ThingSpeak
String apiKey = "ILMTN11TAXIA02SX";
const char* serverName = "http://api.thingspeak.com/update";

// Pin Hardware
const int ldrPin = 34;    // Pin Analog untuk LDR
const int buttonPin = 4;  // Pin Digital untuk Button

unsigned long lastTime = 0;
unsigned long timerDelay = 15000; // ThingSpeak Free perlu 15 saat setiap update

void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP); // Button dengan internal pull-up

  WiFi.begin(ssid, password);
  Serial.println("Menyambung ke WiFi...");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi disambungkan!");
}

void loop() {
  // Hanya hantar data setiap 15 saat
  if ((millis() - lastTime) > timerDelay) {
    if(WiFi.status() == WL_CONNECTED){
      
      HTTPClient http;

      // 1. Baca nilai LDR (Analog 0 - 4095)
      int ldrValue = analogRead(ldrPin);
      
      // 2. Baca nilai Button (Tukar logik: Tekan=1, Lepas=0)
      int buttonState = (digitalRead(buttonPin) == LOW) ? 1 : 0;

      // 3. Bina URL API (Seperti yang kita cerakinkan tadi)
      String url = String(serverName) + "?api_key=" + apiKey + "&field1=" + String(buttonState) + "&field2=" + String(ldrValue);
      
      Serial.print("Menghantar data: ");
      Serial.println(url);

      // 4. Mulakan HTTP GET
      http.begin(url.c_str());
      int httpResponseCode = http.GET();
      
      if (httpResponseCode > 0) {
        Serial.print("Respons HTTP: ");
        Serial.println(httpResponseCode);
      }
      else {
        Serial.print("Ralat: ");
        Serial.println(httpResponseCode);
      }
      
      // Tutup sambungan (Connection: close)
      http.end();
    }
    else {
      Serial.println("WiFi Terputus!");
    }
    lastTime = millis();
  }
}
