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
  Serial.println("CLEARDATA"); // Limpia datos -- Este comando borra solo los datos registrados
  Serial.println("CLEARSHEET"); //Limpia hoja -- Este comando borra todos los datos de ActiveSheet (¡incluidas las etiquetas!). 
  Serial.println("LABEL,Fecha,Hora,Temperatura,Humedad Ambiental,Humedad Relativa,Dióxido de Carbono");
  Serial.println("RESETTIMER");
  lcd.begin(16, 2); // Inicializa la pantalla LCD con 16 columnas y 2 filas
  dht.begin();
  ccs.begin();
}


void loop() {
  ccs.readData();
  delay(1000);
  float Temperatura = dht.readTemperature(); // Clasificación de Variable de Temperatura (en C°).
  float HA = dht.readHumidity(); // Clasificación de Variable de Humedad Ambiental (en %).
  int  HS=map(analogRead(SensorPin), 0, 1023, 100, 0); // Clasificación de Variable de Humedad del Suelo (en %).
  float co2 = ccs.geteCO2(); // Clasificación de Variable de Dióxido de Carbono (en ppm).

  Serial.print("DATA,DATE,TIME,"); // Primero se escribe DATA, luego DATE significa la fecha del sistema, TIMER son los segundos desdel último envío,Es importante la última coma de esta línea

  // Actualiza la pantalla LCD con los datos
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(Temperatura, 0);
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
  
  delay(300000); // Registra los datos cada 5 minutos
}
