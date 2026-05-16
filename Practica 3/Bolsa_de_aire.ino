/*
 * PROYECTO: Bolsa de aire
 * PARTICIPANTES: 

* - Diego Guillermo Guardado Viramontes
* - Axel Perea Pinedo
* - Valeria Carrillo Hernández
 */


#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

int16_t ax, ay, az;

const int PIN_AIRBAG = 8;
const float UMBRAL_CRITICO = 3.0;  
const unsigned long TIEMPO_ACTIVACION = 3000;

bool airbagActivado = false;
unsigned long tiempoActivacion = 0;

void activarAirbag() {
  if (!airbagActivado) {
    airbagActivado   = true;
    tiempoActivacion = millis();
    digitalWrite(PIN_AIRBAG, HIGH);
    Serial.println("════════════════════════════");
    Serial.println("  ⚠  AIRBAG ACTIVADO  ⚠");
    Serial.println("════════════════════════════");
  }
}

void desactivarAirbag() {
  airbagActivado = false;
  digitalWrite(PIN_AIRBAG, LOW);
  Serial.println("Sistema reiniciado. En espera...");
}

void setup() {
  Serial.begin(115200);
  Wire.begin();
  mpu.initialize();

  pinMode(PIN_AIRBAG, OUTPUT);
  digitalWrite(PIN_AIRBAG, LOW);

  if (mpu.testConnection()) {
    Serial.println("MPU6050 listo");
    Serial.println("Sistema de airbag en espera...");
  } else {
    Serial.println("Error al inicializar MPU6050");
  }
}

void loop() {
  // Si el airbag está activo, esperar y reiniciar
  if (airbagActivado) {
    if (millis() - tiempoActivacion >= TIEMPO_ACTIVACION) {
      desactivarAirbag();
    }
    return;
  }

  // Leer y normalizar acelerómetro
  mpu.getAcceleration(&ax, &ay, &az);
  float axf = ax / 16384.0;
  float ayf = ay / 16384.0;
  float azf = az / 16384.0;

  // Magnitud total
  float magnitud = sqrt(axf * axf + ayf * ayf + azf * azf);

  Serial.print("Magnitud: ");
  Serial.print(magnitud, 3);
  Serial.println(" g");

  // Activación inmediata si supera el umbral
  if (magnitud >= UMBRAL_CRITICO) {
    activarAirbag();
  }

  delay(10);
}