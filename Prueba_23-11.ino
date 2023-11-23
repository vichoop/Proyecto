#include <Wire.h> // Librería Intervención de LCD
#include <Adafruit_Sensor.h> // Librería Sensores
#include <DHT.h> // Librería DHT (Sensor de Temperatura y Humedad Relativa)
#include "Adafruit_CCS811.h" // Librería CCS811 (Sensor de Dióxido de Carbono)
#include <LiquidCrystal.h> // Librería LCD

#define DHTPIN 10 // El pin digital dónde está conectado el sensor DHT11 es el 2. 
#define DHTTYPE DHT11 // La librería de DHT está creada también para su sensor hermano (DHT22), entonces hay que especificar cuál es.
#define SensorPin A0

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); // Configura los pines de la pantalla LCD
Adafruit_CCS811 ccs;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2); // Inicializa la pantalla LCD con 16 columnas y 2 filas
  dht.begin();
  ccs.begin();
}


void loop() {
  ccs.readData();
  delay(1000);
  int  HS=map(analogRead(SensorPin), 0, 1023, 100, 0);
  float temperature = dht.readTemperature();
  float HA = dht.readHumidity();
  float co2 = ccs.geteCO2();

  // Actualiza la pantalla LCD con los datos
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:");
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
