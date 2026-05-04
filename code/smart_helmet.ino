#define BLYNK_TEMPLATE_ID "TMPL3UP_EAijb"
#define BLYNK_TEMPLATE_NAME "Smart Helmet"
#define BLYNK_AUTH_TOKEN "LKF0plA-GR7LJNrpi913duFAvnJoR7oc"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include <MPU6050.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "iPhone XIV";
char pass[] = "aaa1234y";

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

MPU6050 mpu;
TinyGPSPlus gps;
HardwareSerial gpsSerial(2);

#define SW420_PIN 34
#define BUZZER_PIN 25
#define LED_PIN 26
#define BUTTON_PIN 27

float ax, ay, az;
bool accident = false;
bool alertSent = false;
unsigned long startTime = 0;
unsigned long systemStartTime = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED Failed"));
  }
  
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.display();

  mpu.initialize();
  gpsSerial.begin(9600, SERIAL_8N1, 16, 17);

  pinMode(SW420_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  systemStartTime = millis();
}

void loop() {
  Blynk.run();

  if (millis() - systemStartTime < 3000) return;

  // --- Read Sensors ---
  int16_t x, y, z;
  mpu.getAcceleration(&x, &y, &z);
  ax = x / 16384.0;
  ay = y / 16384.0;
  az = z / 16384.0;

  float angleX = atan2(ay, az) * 180 / PI;
  float angleY = atan2(-ax, sqrt(ay * ay + az * az)) * 180 / PI;

  while (gpsSerial.available()) {
    gps.encode(gpsSerial.read());
  }

  bool vib = digitalRead(SW420_PIN);

  // --- Accident Detection Logic ---
  bool highAcc = (abs(ax) > 2.2 || abs(ay) > 2.2 || abs(az) > 2.2);
  bool highTilt = (abs(angleX) > 60 || abs(angleY) > 60);

  if (!accident) {
    if ((highAcc && vib) || (highTilt && vib)) {
      accident = true;
      startTime = millis();
    }
  }

  // --- Manual Reset ---
  if (digitalRead(BUTTON_PIN) == LOW) {
    accident = false;
    alertSent = false;
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_PIN, LOW);
  }

  // --- Update Blynk ---
  Blynk.virtualWrite(V0, ax);
  Blynk.virtualWrite(V1, ay);
  Blynk.virtualWrite(V2, angleX);
  Blynk.virtualWrite(V3, angleY);
  Blynk.virtualWrite(V4, vib);

  // --- OLED Display Management ---
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);

  if (!accident) {
    // NORMAL DASHBOARD
    display.println("--- SYSTEM DATA ---");
    display.print("AX:"); display.print(ax, 1);
    display.print(" AY:"); display.println(ay, 1);
    display.print("AngX:"); display.print(angleX, 0);
    display.print(" AngY:"); display.println(angleY, 0);
    display.print("Vib: "); display.println(vib ? "YES!" : "NO");
    display.println("-------------------");
    
    if (gps.location.isValid()) {
      display.print("Lat: "); display.println(gps.location.lat(), 4);
      display.print("Lon: "); display.println(gps.location.lng(), 4);
    } else {
      display.println("GPS: Searching...");
    }
  } 
  else {
    // ACCIDENT ALERT
    int timeLeft = 10 - ((millis() - startTime) / 1000);
    
    display.setTextSize(2);
    display.println(" ACCIDENT!");
    display.setTextSize(1);
    display.println("\nSending Alert in:");
    display.setTextSize(2);
    display.print("    "); display.println(timeLeft);

    // Beep pattern
    digitalWrite(BUZZER_PIN, (millis() % 200 < 100)); 
    digitalWrite(LED_PIN, (millis() % 200 < 100));

    if (!alertSent && timeLeft <= 0) {
      if (gps.location.isValid()) {
        float lat = gps.location.lat();
        float lon = gps.location.lng();
        String msg = "Accident! https://maps.google.com/?q=" + String(lat,6) + "," + String(lon,6);
        Blynk.logEvent("accident_alert", msg);
        alertSent = true;
      }
      accident = false; // Reset after sending
    }
  }

  display.display();
}
