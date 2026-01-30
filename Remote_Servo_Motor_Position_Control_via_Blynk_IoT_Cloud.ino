/* Fill in information from Blynk Device Info */
#define BLYNK_TEMPLATE_ID   "TMPLxxxxxx"
#define BLYNK_TEMPLATE_NAME "ServoControl"
#define BLYNK_AUTH_TOKEN    "YourAuthToken"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h> // Library khusus untuk ESP32

// Maklumat WiFi
char ssid[] = "NamaWiFiAnda";
char pass[] = "PasswordWiFiAnda";

Servo myServo; 
int servoPin = 13; // Signal disambung ke GPIO 13

// Fungsi ini dipanggil setiap kali widget Slider di Blynk (V1) digerakkan
BLYNK_WRITE(V1) {
  int angle = param.asInt(); // Ambil nilai slider (0-180)
  myServo.write(angle);      // Gerakkan motor ke sudut tersebut
  
  // Papar maklumat di Serial Monitor untuk debug
  Serial.print("Slider Value: ");
  Serial.println(angle);
}

void setup() {
  Serial.begin(115200);
  
  // Konfigurasi Servo
  ESP32PWM::allocateTimer(0);
  myServo.setPeriodHertz(50);    // Frekuensi standard servo 50Hz
  myServo.attach(servoPin, 500, 2400); // Attach pin dengan julat pulsa (min, max)

  // Sambungan ke Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run(); // Menjalankan proses latar belakang Blynk
}
