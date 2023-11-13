#include <Adafruit_Sensor.h> // Librería Sensores
#include "Adafruit_CCS811.h" // Librería CCS811 (Sensor de Dióxido de Carbono)
#include <DHT.h> // Librería DHT (Sensor de Temperatura y Humedad Relativa)
#include <LiquidCrystal.h> // Librería LCD
#include <Wire.h> // Librería Intervención de LCD

#define DHTPIN_T1 2 // Se define el pin digital de algunos de los sensores DHT11 es 2.
#define DHTPIN_T2 3 // Se define el pin digital de algunos de los sensores DHT11 es 3.
#define DHTPIN_T3 4 // Se define el pin digital de algunos de los sensores DHT11 es 4.
#define DHTTYPE DHT11 // Se define y especifica el tipo de sensor que es.
#define BUTTON_PIN 5 // Se define el pin digital del botón es 5.

DHT dht_T1(DHTPIN_T1, DHTTYPE);
DHT dht_T2(DHTPIN_T2, DHTTYPE);
DHT dht_T3(DHTPIN_T3, DHTTYPE);
Adafruit_CCS811 ccs_T1;
Adafruit_CCS811 ccs_T2;
Adafruit_CCS811 ccs_T3;

LiquidCrystal lcd(8, 9, 10, 11, 12, 13, 14); // Configura los pines de la pantalla LCD. Parámetros: (rs, rw, e, d4, d5, d6, d7)

int currentTerrarium = 1; // Terrario actual (1, 2, o 3)

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2); // Inicializa la pantalla LCD con 16 columnas y 2 filas

  if (!ccs_T1.begin() || !ccs_T2.begin() || !ccs_T3.begin()) {
    Serial.println("Error al iniciar los sensores CCS811. Verifica la conexión.");
    while (1);
  }
  if (!dht_T1.begin(1000) || !dht_T2.begin(1000) || !dht_T3.begin(1000)) {
    Serial.println("Error al iniciar los sensores DHT11. Verifica la conexión.");
    while (1);
  }
  pinMode(BUTTON_PIN, INPUT);
}

void loop() {
  int buttonState = digitalRead(BUTTON_PIN);

  if (buttonState == HIGH) {
    delay(100); // Debounce
    if (buttonState == HIGH) {
      // Cambia al siguiente terrario
      currentTerrarium = (currentTerrarium % 3) + 1;
    }
  }

  float temperature, humidity, co2;

  switch (currentTerrarium) {
    case 1:
      temperature = dht_T1.readTemperature();
      humidity = dht_T1.readHumidity();
      co2 = ccs_T1.geteCO2();
      break;
    case 2:
      temperature = dht_T2.readTemperature();
      humidity = dht_T2.readHumidity();
      co2 = ccs_T2.geteCO2();
      break;
    case 3:
      temperature = dht_T3.readTemperature();
      humidity = dht_T3.readHumidity();
      co2 = ccs_T3.geteCO2();
      break;
  }

  // Actualiza la pantalla LCD con los datos
  lcd.clear();
  lcd.print("Terrario ");
  lcd.print(currentTerrarium);
  lcd.setCursor(0, 1); // Cambia a la segunda línea
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print("C  Hum: ");
  lcd.print(humidity);
  lcd.print("%");

  delay(1000); // Puedes ajustar la frecuencia de actualización
}
