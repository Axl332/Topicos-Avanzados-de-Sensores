/*
 * PROYECTO: Tabla_psicometrica
 * PARTICIPANTES: 

* - Diego Guillermo Guardado Viramontes
* - Axel Perea Pinedo
* - Valeria Carrillo Hernández
 */

#include <Wire.h>
#include <Adafruit_AHTX0.h>
#include <Adafruit_BMP280.h>

// Instanciar los sensores I2C
Adafruit_AHTX0 aht;
Adafruit_BMP280 bmp; 

// Configuración del LM35 (Analógico)
const int pinLM35 = A0; 

void setup() {
  Serial.begin(9600);
  while (!Serial) { delay(10); } // Esperar a que se abra el monitor serie

  Serial.println("--- Inicializando Sistema Psicométrico Multifuncional ---");

  // 1. Inicializar AHT20
  if (!aht.begin()) {
    Serial.println("¡Error! No se pudo encontrar el sensor AHT20. Revisa conexiones.");
    while (1) delay(10);
  }
  Serial.println("Sensor AHT20... ¡Listo!");

  // 2. Inicializar BMP280
  // Nota: Si no inicia, prueba cambiando a: bmp.begin(0x76) que es común en estos módulos combo
  if (!bmp.begin(0x76)) { 
    Serial.println("¡Error! No se pudo encontrar el sensor BMP280. Intentando con dirección por defecto...");
    if (!bmp.begin()) {
      Serial.println("¡Error crítico! No se detectó el BMP280. Revisa soldaduras o direcciones I2C.");
      while (1) delay(10);
    }
  }
  Serial.println("Sensor BMP280... ¡Listo!");
  
  // Configuración de parámetros  para el BMP280 
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Modo de operación. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Presión oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtrado. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Tiempo de espera. */

  // Encabezado de la tabla para Excel
  Serial.println("\nTiempo(s)\tT_AHT20(C)\tT_BMP280(C)\tT_LM35(C)\tHR_AHT20(%)\tPresion(hPa)");
}

void loop() {
  // Variables para almacenar lecturas
  sensors_event_t humidity, temp_aht;
  aht.getEvent(&humidity, &temp_aht); // Lectura del AHT20

  // 1. Temperatura y Humedad del AHT20
  float t_aht = temp_aht.temperature;
  float hr = humidity.relative_humidity;

  // 2. Temperatura y Presión del BMP280
  float t_bmp = bmp.readTemperature();
  float presion = bmp.readPressure() / 100.0F; // Convertir Pascales a hectopascales (hPa)

  // 3. Temperatura del LM35
  int lecturaAnalogica = analogRead(pinLM35);
  float voltaje = (lecturaAnalogica * 5.0) / 1023.0; 
  float t_lm35 = voltaje * 100.0; 

  // Obtener tiempo de ejecución
  unsigned long tiempo = millis() / 1000;

  // Imprimir fila de datos separada por Tabuladores
  Serial.print(tiempo);
  Serial.print("\t");
  Serial.print(t_aht, 2);
  Serial.print("\t\t");
  Serial.print(t_bmp, 2);
  Serial.print("\t\t");
  Serial.print(t_lm35, 2);
  Serial.print("\t\t");
  Serial.print(hr, 1);
  Serial.print("\t\t");
  Serial.print(presion, 2);
  Serial.println();

  delay(1000); // Muestreo cada 2 segundos
}