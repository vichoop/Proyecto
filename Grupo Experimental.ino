#include <Wire.h> // Librería Intervención de LCD
#include <Adafruit_Sensor.h> // Librería Sensores
#include <DHT.h> // Librería DHT (Sensor de Temperatura y Humedad Relativa)
#include "Adafruit_CCS811.h" // Librería CCS811 (Sensor de Dióxido de Carbono)
#include <LiquidCrystal.h> // Librería LCD

#define DHTPIN_T1 10
#define DHTPIN_T2 11
#define DHTPIN_T3 12
#define DHTTYPE DHT11
#define HUMEDAD_T1 A0
#define HUMEDAD_T2 A1
#define HUMEDAD_T3 A2
#define boton 5

DHT dht_T1(DHTPIN_T1, DHTTYPE);
DHT dht_T2(DHTPIN_T2, DHTTYPE);
DHT dht_T3(DHTPIN_T3, DHTTYPE);
Adafruit_CCS811 ccs_T1;
Adafruit_CCS811 ccs_T2;
Adafruit_CCS811 ccs_T3;

LiquidCrystal lcd(8, 9, 4, 5, 6, 7); // Configura los pines de la pantalla LCD

int currentTerrarium = 1;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2); // Inicializa la pantalla LCD con 16 columnas y 2 filas

  dht_T1.begin();
  dht_T2.begin();
  dht_T3.begin();
  ccs_T1.begin();
  ccs_T2.begin();
  ccs_T3.begin();

 pinMode(boton, INPUT);

}

void loop() {
  int buttonState = digitalRead(boton);

  if (buttonState == HIGH) {
    delay(100); // Debounce
    if (buttonState == HIGH) {
      currentTerrarium = (currentTerrarium % 3) + 1;
    }
  }

  ccs_T1.readData();
  ccs_T2.readData();
  ccs_T3.readData();
  delay(1000);

float temperatura, HA, HS, co2;

switch (currentTerrarium) '{
    case 1:
        temperatura = dht_T1.readTemperature();
        HA = dht_1.readHumidity();
        int HS=map(analogRead(HUMEDAD_T1), 0, 1023, 100, 0);
        co2 = ccs_T1.geteCO2();
    case 2:
        temperatura = dht_T2.readTemperature();
        HA = dht_T2.readHumidity();
        int HS=map(analogRead(HUMEDAD_T2), 0, 1023, 100, 0);
        co2 = ccs_T2.geteCO2();
    case 3:
        temperatura = dht_T3.readTemperature();
        HA = dht_T3.readHumidity();
        int HS=map(analogRead(HUMEDAD_T3), 0, 1023, 100, 0);
        co2 = ccs_T3.geteCO2();
    break;
}
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Te:")
  lcd.print(currentTerrarium);
  lcd.print(" T:");
  lcd.print(temperature, 0);
  lcd.print((char)223);
  lcd.print("C HA:");
  lcd.print(HA, 0);
  lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("HS:");
  lcd.print(HS,1);
  lcd.print("% CO2:");
  lcd.print(co2, 0);
  lcd.print("ppm");
  
  delay(1000); // Puedes ajustar la frecuencia de actualización
}
