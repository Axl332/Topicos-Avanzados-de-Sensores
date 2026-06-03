/*
 * PROYECTO: Sistema de Adquisición de Datos, Alcoholímetro
 * PARTICIPANTES: 

* - Diego Guillermo Guardado Viramontes
* - Axel Perea Pinedo
* - Valeria Carrillo Hernández
 */


const int pinSensorMQ = A0;  // Pin analógico conectado al AO del sensor
const int pinLED = 2;        // Pin digital de LED externo
unsigned long numeroMuestra = 0; // Contador de muestras

// UMBRAL DE DETECCIÓN 
// Si el voltaje supera este valor, se asume aliento alcohólico.
const float umbralAlcohol = 0.70; 

void setup() {
  Serial.begin(9600);
  
  // Configurar el pin del LED como salida
  pinMode(pinLED, OUTPUT);
  
  // Encabezado para el Monitor Serie
  Serial.println("Muestra\tVoltaje(V)\tEstado");
  Serial.println("-------------------------------------");
  
  // Tiempo de espera para la estabilización inicial del sensor
  delay(3000); 
}

void loop() {
  numeroMuestra++;

  // 1. Leer el valor analógico y convertirlo a voltaje
  int valorCrudo = analogRead(pinSensorMQ);
  float voltaje = valorCrudo * (5.0 / 1023.0);

  // 2. Estructura de control para el alcoholímetro
  String estado = "Normal";
  
  if (voltaje >= umbralAlcohol) {
    digitalWrite(pinLED, HIGH);  // Enciende el LED si detecta alcohol
    estado = "ALERTA: Alcohol Detectado";
  } else {
    digitalWrite(pinLED, LOW);   // Mantiene el LED apagado si el aire está limpio
    estado = "Normal";
  }

  // 3. Imprimir datos en formato de lista
  Serial.print(numeroMuestra);
  Serial.print("\t");
  Serial.print(voltaje, 2);
  Serial.print("\t\t");
  Serial.println(estado);

  // Muestreo cada 250 milisegundos (4 muestras por segundo)
  delay(250); 
}