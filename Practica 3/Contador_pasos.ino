/*
 * PROYECTO: Contador de pasos
 * PARTICIPANTES: 

* - Diego Guillermo Guardado Viramontes
* - Axel Perea Pinedo
* - Valeria Carrillo Hernández
 */

#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

int16_t ax, ay, az;

int pasos = 0;
bool pasoDetectado = false;

// Umbrales de detección ajustable
const float UMBRAL_ALTO = 1.2;  // g
const float UMBRAL_BAJO = 0.8;  // g

void setup() {
  Serial.begin(115200);
  Wire.begin();
  mpu.initialize();

  if (mpu.testConnection()) {
    Serial.println("MPU6050 listo");
    Serial.println("Pasos: 0");
  } else {
    Serial.println("Error al inicializar");
  }
}

void loop() {
  mpu.getAcceleration(&ax, &ay, &az);

  // Normalizar a g
  float axf = ax / 16384.0;
  float ayf = ay / 16384.0;
  float azf = az / 16384.0;

  // Magnitud total del vector de aceleración
  float magnitud = sqrt(axf * axf + ayf * ayf + azf * azf);

  // Algoritmo de detección por umbral con histéresis
  if (magnitud > UMBRAL_ALTO && !pasoDetectado) {
    pasoDetectado = true;          // Flanco de subida detectado
  }

  if (magnitud < UMBRAL_BAJO && pasoDetectado) {
    pasos++;                       // Flanco de bajada = paso completo
    pasoDetectado = false;
    Serial.print("Pasos: ");
    Serial.println(pasos);
  }

  delay(10);
}