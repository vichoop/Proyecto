#include <Adafruit_Sensor.h>
#include "Adafruit_CCS811.h"
#include <DHT.h>
#include <LiquidCrystal.h>
#include <Wire.h>

#define DHTPIN_T1 2
#define DHTPIN_T2 3
#define DHTPIN_T3 4
#define DHTTYPE DHT11
#define HUMEDAD_S_T1 A8
#define HUMEDAD_S_T2 A9
#define HUMEDAD_S_T3 A10
#define BUTTON_PIN 5

DHT dht_T1(DHTPIN_T1, DHTTYPE);
DHT dht_T2(DHTPIN_T2, DHTTYPE);
DHT dht_T3(DHTPIN_T3, DHTTYPE);
Adafruit_CCS811 ccs_T1;
Adafruit_CCS811 ccs_T2;
Adafruit_CCS811 ccs_T3;

LiquidCrystal lcd(8, 9, 10, 11, 12, 13, 14);

int currentTerrarium = 1;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);

  if (!ccs_T1.begin() || !ccs_T2.begin() || !ccs_T3.begin()) {
    Serial.println("Error al medir Dióxido de Carbono");
    while (1);
  }
  if (!dht_T1.begin(1000) || !dht_T2.begin(1000) || !dht_T3.begin(1000)) {
    Serial.println("Error al medir Temperatura y Humedad Ambiental");
    while (1);
  }
  pinMode(BUTTON_PIN, INPUT);
}

void loop() {
  int buttonState = digitalRead(BUTTON_PIN);

  if (buttonState == HIGH) {
    delay(100); // Debounce
    if (buttonState == HIGH) {
      currentTerrarium = (currentTerrarium % 3) + 1;
    }
  }

  float temperature, humidity, HS, co2;

  switch (currentTerrarium) {
    case 1:
      temperature = dht_T1.readTemperature();
      humidity = dht_T1.readHumidity();
      HS = map(analogRead(HUMEDAD_S_T1), 0, 1023, 0, 100); // Assuming HS represents a percentage
      co2 = ccs_T1.geteCO2();
      break;
    case 2:
      temperature = dht_T2.readTemperature();
      humidity = dht_T2.readHumidity();
      HS = map(analogRead(HUMEDAD_S_T2), 0, 1023, 0, 100);
      co2 = ccs_T2.geteCO2();
      break;
    case 3:
      temperature = dht_T3.readTemperature();
      humidity = dht_T3.readHumidity();
      HS = map(analogRead(HUMEDAD_S_T3), 0, 1023, 0, 100);
      co2 = ccs_T3.geteCO2();
      break;
  }

  // Update the LCD screen with the data for the specific terrarium
  lcd.clear();
  lcd.print("Terrario ");
  lcd.print(currentTerrarium);
  lcd.setCursor(0, 1);
  lcd.print("T: ");
  lcd.print((char)223);
  lcd.print(temperature);
  lcd.print("C  HA: ");
  lcd.print(humidity);
  lcd.print("%");
  lcd.print("  HS: ");
  lcd.print(HS);
  lcd.print("% CO2: ");
  lcd.print(co2);

  delay(1000);
}
