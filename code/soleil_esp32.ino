#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPL3GbtHka_p"
#define BLYNK_TEMPLATE_NAME "SOLEIL DEMO"
#define BLYNK_AUTH_TOKEN "1PuIguWkSdcnFo4uFETDrhxjG-64JWgp"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

// ===== WIFI =====
char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";

// ===== MPU6050 =====
Adafruit_MPU6050 mpu;

// ===== DHT11 =====
#define DHTPIN 15
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// ===== PINS =====
#define RELAY_PIN 26
#define BUZZER_PIN 25
#define LED_PIN 2

// ===== THRESHOLDS =====
float TILT_WARNING = 45.0;
float TILT_CRITICAL = 60.0;

// ===== FLAGS =====
bool warningSent = false;
bool criticalSent = false;

void setup() {
  Serial.begin(115200);

  // Pins
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(RELAY_PIN, HIGH); // Relay OFF (active LOW)
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_PIN, LOW);

  // I2C
  Wire.begin(21, 22);

  // MPU6050 init
  if (!mpu.begin()) {
    Serial.println("MPU6050 not found!");
    while (1);
  }

  // DHT init
  dht.begin();

  // Blynk start
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  Serial.println("SYSTEM READY");
}

void loop() {
  Blynk.run();

  // ===== READ MPU =====
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  float tilt = atan2(a.acceleration.x,
                    sqrt(a.acceleration.y * a.acceleration.y +
                         a.acceleration.z * a.acceleration.z)) * 180 / PI;

  tilt = abs(tilt);

  // ===== READ TEMP =====
  float tempDHT = dht.readTemperature();

  // ===== SEND TO BLYNK =====
  Blynk.virtualWrite(V0, tempDHT); // Temperature
  Blynk.virtualWrite(V1, tilt);    // Tilt

  int motorState = 0;

  // ===== LOGIC =====
  if (tilt > TILT_CRITICAL) {

    digitalWrite(RELAY_PIN, LOW);   // Relay ON
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(LED_PIN, HIGH);
    motorState = 1;

    // CRITICAL ALERT
    if (!criticalSent) {
      Blynk.logEvent("critical_alert", "CRITICAL: Tilt exceeded safe limit!");
      criticalSent = true;
      warningSent = false;
    }

  }
  else if (tilt > TILT_WARNING) {

    digitalWrite(RELAY_PIN, LOW);
    digitalWrite(LED_PIN, HIGH);
    motorState = 1;

    digitalWrite(BUZZER_PIN, HIGH);
    delay(200);
    digitalWrite(BUZZER_PIN, LOW);

    // WARNING ALERT
    if (!warningSent) {
      Blynk.logEvent("warning_alert", "WARNING: Tilt approaching unsafe level!");
      warningSent = true;
      criticalSent = false;
    }

  }
  else {

    digitalWrite(RELAY_PIN, HIGH); // Relay OFF
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_PIN, LOW);
    motorState = 0;

    // Reset alerts
    warningSent = false;
    criticalSent = false;
  }

  // Send motor status
  Blynk.virtualWrite(V2, motorState);

  delay(1000);
}
