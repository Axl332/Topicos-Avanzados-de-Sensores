/*
 * PROYECTO: Pitch y roll usando solo giroscopio
 * PARTICIPANTES: 

* - Diego Guillermo Guardado Viramontes
* - Axel Perea Pinedo
* - Valeria Carrillo Hernández
 */

#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

int16_t gx, gy, gz;

float pitch = 0.0;
float roll  = 0.0;

unsigned long tiempoAnterior = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  mpu.initialize();

  if (mpu.testConnection()) {
    Serial.println("MPU6050 listo");
  } else {
    Serial.println("Error al inicializar");
  }

  tiempoAnterior = millis();
}

void loop() {
  // Leer solo giroscopio
  mpu.getRotation(&gx, &gy, &gz);

  // Normalizar a °/s (±250°/s → 131 LSB/°/s)
  float gxf = gx / 131.0;
  float gyf = gy / 131.0;

  // Calcular delta de tiempo en segundos
  unsigned long tiempoActual = millis();
  float dt = (tiempoActual - tiempoAnterior) / 1000.0;
  tiempoAnterior = tiempoActual;

  // Integrar velocidad angular para obtener ángulo
  pitch += gxf * dt;
  roll  += gyf * dt;

  Serial.print("Pitch: "); Serial.print(pitch, 2);
  Serial.print(" °  |  Roll: "); Serial.println(roll, 2);

  delay(10);
}