#include <Wire.h> // Librería Intervención de LCD
#include <Adafruit_Sensor.h> // Librería Sensores
#include <DHT.h> // Librería DHT (Sensor de Temperatura y Humedad Relativa)
#include "Adafruit_CCS811.h" // Librería CCS811 (Sensor de Dióxido de Carbono)
#include <LiquidCrystal.h> // Librería LCD

#define DHTPIN 10 // Definición del Pin Digital del sensor DHT11.
#define DHTTYPE DHT11 // La librería de DHT está creada también para su sensor hermano (DHT22), entonces hay que especificar cuál es.
#define SueloPin_T3 A0 // Definición del Pin Análogo del sensor de Humedad del Suelo.

DHT dht_T4(DHTPIN, DHTTYPE); // Ejecución de la librería del DHT y nombre del sensor: 'dht_T3'.
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); // Ejecución de la libraría del LCD y Configuración Pines Pantalla LCD (rs, en, d4, d5, d6, d7).
Adafruit_CCS811 ccs_T4; // Ejecución de la librería del CCS811 y nombre del sensor 'ccs_T3'.

void setup() {
  Serial.begin(9600);

  // Inicio Integración Excel
  
  Serial.println("CLEARDATA"); 
  Serial.println("CLEARSHEET"); 
  Serial.println("LABEL,Fecha,Hora,Temperatura,Humedad Ambiental,Humedad Relativa,Dióxido de Carbono"); // Creación Encabezados Hoja de Cálculo
  Serial.println("RESETTIMER");

  // Fin Integración Excel
  
  lcd.begin(16, 2); // Inicialización Pantalla LCD
  dht.begin(); // Inicialización Sensor DHT11
  ccs.begin(); // Inicialización Sensor CCS811
}


void loop() {
  ccs.readData(); // Orden al sensor CCS811 para que reciba datos.
  
  float Temperatura = dht_T4.readTemperature(); // Clasificación de Variable de Temperatura (en C°).
  float HA = dht_T4.readHumidity(); // Clasificación de Variable de Humedad Ambiental (en %).
  int  HS=map(analogRead(SueloPin_T4), 0, 1023, 100, 0); // Clasificación de Variable de Humedad del Suelo (en %).
  float co2 = ccs_T4.geteCO2(); // Clasificación de Variable de Dióxido de Carbono (en ppm).

  // Inicio Integración Excel

  Serial.print("DATA,DATE,TIME,"); // Exportación de lo recopilado

  // Fin Integración Excel

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
