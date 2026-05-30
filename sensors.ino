#include <Adafruit_Sensor.h>
#include "DHT.h"
#include <MQ135.h>
#include <LiquidCrystal.h>

#define DHT22_PIN 9
#define MQ135_PIN 0
#define HW484_PIN 2

const int sensorMin = 0;     // sensor minimum
const int sensorMax = 1024;  // sensor maximum

DHT dht22(DHT22_PIN, DHT22);
LiquidCrystal lcd(12, 11, 5, 4, 3, HW484_PIN);

void setup() {
  Serial.begin(9600);
  dht22.begin();
  lcd.begin(16, 2);
}

void loop() {
  // DHT22 readings
  delay(2000);
  float humi = dht22.readHumidity();
  float tempC = dht22.readTemperature();
  float tempF = dht22.readTemperature(true);

  if (isnan(humi) || isnan(tempC) || isnan(tempF)) {
    Serial.println("Failed to read from DHT22 sensor!");
  } else {
    Serial.print("DHT22# Humidity: ");
    Serial.print(humi);
    Serial.print("%");
    Serial.print("  |  ");
    Serial.print("Temperature: ");
    Serial.print(tempC);
    Serial.print("°C ~ ");
    Serial.print(tempF);
    Serial.println("°F");
  }

  // MQ135 readings
  int sensorValue = analogRead(MQ135_PIN);
  Serial.print("AirQua=");
  Serial.print(sensorValue, DEC);
  Serial.println(" PPM");
  lcd.setCursor(0, 0);
  lcd.print("ArQ=");
  lcd.print(sensorValue, DEC);
  lcd.print("   PPM");
  lcd.println("       ");
  lcd.print("  ");

  // HW484 readings
  int hw484_sensorReading = analogRead(HW484_PIN);
  int range = map(hw484_sensorReading, sensorMin, sensorMax, 0, 3);

  switch (range) {
    case 0:    // A fire closer than 1.5 feet away.
      Serial.println("* Close  Fire *");
      break;
    case 1:    // A fire between 1-3 feet away.
      Serial.println("*  Distant Fire *");
      break;
    case 2:    // No fire detected.
      Serial.println("No  Fire");
      break;
  }

  delay(100);
}