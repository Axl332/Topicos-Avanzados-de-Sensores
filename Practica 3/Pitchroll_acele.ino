/*
 * PROYECTO: Pitch y roll usando solo acelerometro
 * PARTICIPANTES: 

* - Diego Guillermo Guardado Viramontes
* - Axel Perea Pinedo
* - Valeria Carrillo Hernández
 */

#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

int16_t ax, ay, az;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  mpu.initialize();

  if (mpu.testConnection()) {
    Serial.println("MPU6050 listo");
  } else {
    Serial.println("Error al inicializar");
  }
}

void loop() {
  // Leer solo acelerómetro (gyro no se usa)
  mpu.getAcceleration(&ax, &ay, &az);

  // Normalizar a g (±2g → 16384 LSB/g)
  float axf = ax / 16384.0;
  float ayf = ay / 16384.0;
  float azf = az / 16384.0;

  // Calcular pitch y roll con atan2 (resultado en radianes → convertir a grados)
  float pitch = atan2(axf, sqrt(ayf * ayf + azf * azf)) * 180.0 / PI;
  float roll  = atan2(ayf, sqrt(axf * axf + azf * azf)) * 180.0 / PI;

  Serial.print(" °  |  Pitch: ");  Serial.println(roll, 2);
  Serial.print("Roll: "); Serial.print(pitch, 2);


  delay(100);
}