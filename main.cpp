#include <Arduino.h>
#include "DHT.h"
#include <Wire.h>
#include <U8g2lib.h>
#include <TinyGPSPlus.h>

// ---------- PINS ----------
#define DHT_PIN 4
#define DHT_TYPE DHT11

#define TRIG_PIN 32
#define ECHO_PIN 33

#define GAS_PIN 34

#define LED_PIN 26
#define BUZZER_PIN 25
#define SOS_BUTTON 27

#define GPS_RX 16
#define GPS_TX 17

// ---------- DHT ----------
DHT dht(DHT_PIN, DHT_TYPE);

// ---------- OLED ----------
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(
  U8G2_R0,
  U8X8_PIN_NONE
);

// ---------- GPS ----------
TinyGPSPlus gps;
HardwareSerial GPS(2);

void setup() {

  Serial.begin(115200);

  // DHT
  dht.begin();

  // Ultrasonic
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIG_PIN, LOW);

  // Gas
  pinMode(GAS_PIN, INPUT);

  // Alerts
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(SOS_BUTTON, INPUT_PULLUP);

  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  // I2C
  Wire.begin(21, 22);

  // OLED
  u8g2.begin();

  // GPS
  GPS.begin(9600, SERIAL_8N1, GPS_RX, GPS_TX);

  Serial.println("================================");
  Serial.println("         DEEP SAFE              ");
  Serial.println("================================");
  Serial.println("System starting...");

  delay(2000);
}

void loop() {

  // ---------- READ GPS ----------
  while (GPS.available()) {
    gps.encode(GPS.read());
  }

  // ---------- TEMPERATURE & HUMIDITY ----------
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // ---------- ULTRASONIC ----------
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  float distance = 0;

  if (duration > 0) {
    distance = duration * 0.0343 / 2;
  }

  // ---------- GAS ----------
  int gasValue = analogRead(GAS_PIN);

  // ---------- SOS ----------
  bool sosPressed = (digitalRead(SOS_BUTTON) == LOW);

  // ---------- DANGER ----------
  bool danger = false;

  if (temperature > 40) {
    danger = true;
  }

  if (humidity > 80) {
    danger = true;
  }

  if (distance > 0 && distance < 50) {
    danger = true;
  }

  if (gasValue > 400) {
    danger = true;
  }

  if (sosPressed) {
    danger = true;
  }

  // ---------- ALERT ----------
  if (danger) {

    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, 2000);

  } else {

    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);
  }

  // ---------- SERIAL ----------
  Serial.println();
  Serial.println("-------------------------");

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  Serial.print("Gas ADC: ");
  Serial.println(gasValue);

  // ---------- GPS SERIAL ----------
  if (gps.location.isValid()) {

    Serial.println("GPS STATUS: FIXED");

    Serial.print("SATELLITES: ");
    Serial.println(gps.satellites.value());

    Serial.print("LATITUDE : ");
    Serial.println(gps.location.lat(), 6);

    Serial.print("LONGITUDE: ");
    Serial.println(gps.location.lng(), 6);

    Serial.print("ALTITUDE : ");
    Serial.print(gps.altitude.meters());
    Serial.println(" m");

  } else {

    Serial.println("GPS STATUS: SEARCHING");
  }

  // ---------- SOS ----------
  if (sosPressed) {
    Serial.println("!!! SOS BUTTON PRESSED !!!");
  }

  // ---------- SYSTEM STATUS ----------
  if (danger) {
    Serial.println("!!! SYSTEM STATUS: DANGER !!!");
  } else {
    Serial.println("SYSTEM STATUS: NORMAL");
  }

  // ---------- OLED ----------
  u8g2.clearBuffer();

  u8g2.setFont(u8g2_font_6x10_tf);

  u8g2.setCursor(0, 10);
  u8g2.print("TEMP: ");
  u8g2.print(temperature, 1);
  u8g2.print(" C");

  u8g2.setCursor(0, 21);
  u8g2.print("HUM : ");
  u8g2.print(humidity, 1);
  u8g2.print(" %");

  u8g2.setCursor(0, 32);
  u8g2.print("DIST: ");
  u8g2.print(distance, 1);
  u8g2.print(" cm");

  u8g2.setCursor(0, 43);
  u8g2.print("GAS : ");
  u8g2.print(gasValue);

  u8g2.setCursor(0, 54);

  if (sosPressed) {
    u8g2.print("SOS: PRESSED");
  }
  else if (danger) {
    u8g2.print("SYSTEM: DANGER");
  }
  else {
    u8g2.print("SYSTEM: NORMAL");
  }

  u8g2.setCursor(0, 64);

  if (gps.location.isValid()) {
    u8g2.print("GPS: FIXED");
  } else {
    u8g2.print("GPS: SEARCHING");
  }

  u8g2.sendBuffer();

  delay(2000);
}
