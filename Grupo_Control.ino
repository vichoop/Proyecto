#include <Adafruit_Sensor.h> // Librería Sensores
#include "Adafruit_CCS811.h" // Librería CCS811 (Sensor de Dióxido de Carbono)
#include <DHT.h> // Librería DHT (Sensor de Temperatura y Humedad Relativa)
#include <LiquidCrystal.h> // Librería LCD
#include <Wire.h> // Librería Intervención de LCD

#define DHTPIN 2 // El pin digital dónde está conectado el sensor DHT11 es el 2. 
#define DHTTYPE DHT11 // La librería de DHT está creada también para su sensor hermano (DHT22), entonces hay que especificar cuál es.
#define SensorPin A0

DHT dht(DHTPIN, DHTTYPE);
Adafruit_CCS811 ccs;

LiquidCrystal lcd(8, 9, 10, 11, 12, 13); // Configura los pines de la pantalla LCD

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2); // Inicializa la pantalla LCD con 16 columnas y 2 filas

  if (!ccs.begin()) {
    Serial.println("Error al iniciar el sensor CCS811. Verifica la conexión.");
    while (1);
  }
}

void loop() {
  int  HS=map(analogRead(SensorPin), 0, 1023, 0, 100);
  float temperature, HA, co2;

  temperature = dht.readTemperature();
  HA = dht.readHumidity();
  co2 = ccs.geteCO2();

  // Actualiza la pantalla LCD con los datos
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T: ");
  lcd.print((char)223);
  lcd.print(temperature, 1);
  lcd.print("C  HA: ");
  lcd.print(HA, 1);
  lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("HS: ");
  lcd.print(HS, 1);
  lcd.print("% CO2: ");
  lcd.print(co2, 1);
  lcd.print(ppm);
  
  delay(1000); // Puedes ajustar la frecuencia de actualización
}
