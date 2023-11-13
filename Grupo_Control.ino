#include <Adafruit_Sensor.h> // Librería Sensores
#include "Adafruit_CCS811.h" // Librería CCS811 (Sensor de Dióxido de Carbono)
#include <DHT.h> // Librería DHT (Sensor de Temperatura y Humedad Relativa)
#include <LiquidCrystal.h> // Librería LCD
#include <Wire.h> // Librería Intervención de LCD

#define DHTPIN 2 // El pin digital dónde está conectado el sensor DHT11 es el 2. 
#define DHTTYPE DHT11 // La librería de DHT está creada también para su sensor hermano (DHT22), entonces hay que especificar cuál es.
#define SensorPin AO

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
  if (!dht.begin(1000)) {
    Serial.println("Error al iniciar el sensor DHT11. Verifica la conexión.");
    while (1);
  }
}

void loop() {
  float temperature, humidity, co2;

  int humedad = analogRead(SensorPin);
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  co2 = ccs.geteCO2();

  // Actualiza la pantalla LCD con los datos
  lcd.clear();
  lcd.print("Terrario 1");
  lcd.setCursor(0, 1); // Cambia a la segunda línea
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print("C  HA: ");
  lcd.print(humidity);
  lcd.print("% CO2: ");
  lcd.print(co2);
  lcd.print(" ppm");
  lcd.print("  HS: ");
  lcd.print(humedad);
  lcd.print("%");


  delay(1000); // Puedes ajustar la frecuencia de actualización
}
