/*
 * PROYECTO: Fuerza de un objeto
 * PARTICIPANTES: 

* - Diego Guillermo Guardado Viramontes
* - Axel Perea Pinedo
* - Valeria Carrillo Hernández
 */

#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

int16_t ax, ay, az;

const float MASA_KG       = 0.5;   // Ajusta según tu objeto
const float UMBRAL_INICIO = 1.15;  // g
const float UMBRAL_FIN    = 1.02;  // g
const int   MAX_EJERCICIOS = 10;

int   ejercicioActual = 0;
bool  empujando       = false;
float fuerzaAcum      = 0.0;
int   muestras        = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  mpu.initialize();

  if (mpu.testConnection()) {
    Serial.println("MPU6050 listo");
    Serial.println("Empuja cuando estes listo...");
  } else {
    Serial.println("Error al inicializar");
  }
}

void loop() {
  if (ejercicioActual >= MAX_EJERCICIOS) return;

  mpu.getAcceleration(&ax, &ay, &az);

  float axf = ax / 16384.0;
  float ayf = ay / 16384.0;
  float azf = az / 16384.0;

  float magnitud = sqrt(axf * axf + ayf * ayf + azf * azf);
  float aNet     = (magnitud - 1.0) * 9.81; // m/s²
  float fuerza   = MASA_KG * aNet;           // F = m × a

  // Inicio del empuje
  if (!empujando && magnitud >= UMBRAL_INICIO) {
    empujando  = true;
    fuerzaAcum = 0.0;
    muestras   = 0;
    Serial.print("Ejercicio "); Serial.print(ejercicioActual + 1);
    Serial.println(" iniciado...");
  }

  // Durante el empuje
  if (empujando) {
    fuerzaAcum += fuerza;
    muestras++;
  }

  // Fin del empuje
  if (empujando && magnitud < UMBRAL_FIN) {
    empujando = false;
    float fuerzaProm = fuerzaAcum / muestras;

    Serial.print("Fuerza: ");
    Serial.print(fuerzaProm, 2);
    Serial.println(" N");

    ejercicioActual++;

    if (ejercicioActual >= MAX_EJERCICIOS) {
      Serial.println("--- 10 ejercicios completados ---");
    } else {
      Serial.println("Empuja cuando estes listo...");
    }
  }

  delay(10);
}