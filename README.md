# Automatización y Optimización del Sistema de Monitoreo de Temperatura, Humedad y Tasa Fotosintética en Horticultura mediante la Programación de Arduino y Sensores de Datos Ambientales 
¡En el siguiente repositorio de GitHub encontrarás todo lo necesario para replicar nuestro proyecto!
## Librerías Necesarias
```C++ 
 #include <Adafruit_Sensor.h>
```
+ La librería se encuentra en la interfaz de descarga de librerías en Arduino IDE
  - Nombre: Adafruit Unified Sensor
  - Creador(a): Adafruit
```C++ 
 #include "Adafruit_CCS811.h"
```
+ La librería se encuentra en la interfaz de descarga de librerías en Arduino IDE
  - Nombre: Adafruit CCS811 Library
  - Creador(a): Adafruit
> ¡La librería posee dependencias! Asegúrate de instalarlas todas
```C++ 
 #include <DHT.h>
```
+ La librería se encuentra en la interfaz de descarga de librerías en Arduino IDE
  - Nombre: DHT sensor library
  - Creador(a): Adafruit
```C++ 
 #include <LiquidCrystal.h>
```
+ La librería viene instalada predeterminadamente.
  - Nombre: LiquidCrystal
  - Creador(a): Arduino
```C++ 
 #include <Wire.h>
```
+ La librería viene instalada predeterminadamente.
## Sensores Usados
+ Sensor de Temperatura y Humedad Relativa (Ambiental) DHT11
    - Ficha Técnica: [DHT11](https://www.mouser.com/datasheet/2/758/DHT11-Technical-Data-Sheet-Translated-Version-1143054.pdf)
+ Sensor de Humedad del Suelo YL-69
    - Ficha Técnica: [YL-69](https://www.electronicoscaldas.com/datasheet/OBSoil-01_ElecFreaks.pdf)
+ Sensor de Dióxido de Carbono $(CO_2)$ CCS811
    - Ficha Técnica: [CCS811](https://hubot.cl/wp-content/uploads/2018/07/CCS811_Datasheet-DS000459.pdf)
