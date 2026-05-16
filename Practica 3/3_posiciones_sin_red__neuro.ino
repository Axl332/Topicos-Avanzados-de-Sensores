/*
 * PROYECTO: 3 posiciones sin red neuronal
 * PARTICIPANTES: 

* - Diego Guillermo Guardado Viramontes
* - Axel Perea Pinedo
* - Valeria Carrillo Hernández
 */

#include <MPU6050.h>
#include <Wire.h>

MPU6050 mpu;

// Variables para datos crudos
int16_t ax, ay, az;
int16_t gx, gy, gz;

// Variables de ángulo filtrado
float pitch = 0.0;
float roll = 0.0;

// Constantes para el Filtro Complementario
const float alfa = 0.98; 
const float dt = 0.100;   // Tiempo de muestreo en segundos (100ms)

// Constantes de calibración del Giroscopio
const float gyroScale = 131.0; 

// Variables de control de tiempo y estado
unsigned long tiempoAnterior = 0;
int posicionAnterior = 0;

// Umbrales de posición
const int UMBRAL_ROLL_DERECHA   = 25;
const int UMBRAL_ROLL_IZQUIERDA = -25;
const int Margen_Tolerancia_Roll = 15;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  
  // Inicializa MPU6050
  mpu.initialize();
  if (!mpu.testConnection()) {
    Serial.println("ERROR: MPU6050 no detectado!");
    while (1);
  }
  
  // Calibración activa
  Serial.println("Calibrando sensor... Mantener plano y quieto.");
  mpu.setXAccelOffset(0); mpu.setYAccelOffset(0); mpu.setZAccelOffset(0);
  mpu.setXGyroOffset(0);  mpu.setYGyroOffset(0);  mpu.setZGyroOffset(0);
  delay(500); 
  
  Serial.println("MPU6050 listo y optimizado.");
  Serial.println("===============================");
}

void loop() {
  unsigned long tiempoActual = millis();
  
  // Lectura estricta cada 100ms
  if (tiempoActual - tiempoAnterior >= 100) {
    tiempoAnterior = tiempoActual;
    
    // Lee acelerómetro y giroscopio
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    
    // Calcular ángulos del acelerómetro
    float accelPitch = atan2((float)ay, sqrt((float)ax*ax + (float)az*az)) * 180.0 / M_PI;
    float accelRoll  = atan2((float)ax, sqrt((float)ay*ay + (float)az*az)) * 180.0 / M_PI;
    
    // Convertir velocidad del giroscopio
    float gyroXRate = (float)gx / gyroScale;
    float gyroYRate = (float)gy / gyroScale;
    
    // Filtro Complementario
    pitch = alfa * (pitch + gyroYRate * dt) + (1.0 - alfa) * accelPitch;
    roll  = alfa * (roll + gyroXRate * dt) + (1.0 - alfa) * accelRoll;
    
    // Impresión de datos en monitor
    Serial.print("Pitch: "); Serial.print(pitch, 1);
    Serial.print("° | Roll: "); Serial.print(roll, 1);
    Serial.print("° | ");
    
    // Clasificación de posición
    int posicionActual = clasificarPosicion(pitch, roll);
    
    // Evalúa si hubo cambio de estado
    if (posicionActual != posicionAnterior) {
      enviarAlerta(posicionActual);
      posicionAnterior = posicionActual;
    } else {
      Serial.println(); 
    }
  }
}

int clasificarPosicion(float p, float r) {

  // POSICIÓN 2: Sensor apuntando hacia ABAJO
  if (p < UMBRAL_PITCH_ABAJO && r > -Margen_Tolerancia_Roll && r < Margen_Tolerancia_Roll) {
    return 2; 
  }
  // POSICIÓN 3: Sensor inclinado hacia DERECHA
  if (r > UMBRAL_ROLL_DERECHA) {
    return 3; 
  }
  // POSICIÓN 4: Sensor inclinado hacia IZQUIERDA
  if (r < UMBRAL_ROLL_IZQUIERDA) {
    return 4; 
  }
  
  return 0; // NEUTRA
}

void enviarAlerta(int posicion) {
  Serial.println("\n╔════════════════════════════════════════╗");
  switch(posicion) {
    case 2: Serial.println("║   ⚠️ POSICIÓN 2: SENSOR HACIA ABAJO    ║"); break;
    case 3: Serial.println("║   ⚠️ POSICIÓN 3: INCLINADO DERECHA     ║"); break;
    case 4: Serial.println("║   ⚠️ POSICIÓN 4: INCLINADO IZQUIERDA   ║"); break;
    default: Serial.println("║   POSICIÓN: NEUTRA (ninguna)           ║"); break;
  }
  Serial.println("╚════════════════════════════════════════╝");
}