/*
 * PROYECTO: Sistema de Adquisición de Datos
 * PARTICIPANTES: 

* - Diego Guillermo Guardado Viramontes
* - Axel Perea Pinedo
* - Valeria Carrillo Hernández
 */


const int pinSensorMQ = A0;  // Pin analógico conectado al AO del sensor
unsigned long numeroMuestra = 0; // Contador para el número de muestra

void setup() {
  Serial.begin(9600);
  
  // Encabezado para identificar las columnas en el Monitor Serie
  Serial.println("Muestra\tVoltaje(V)");
  Serial.println("-------------------");
  
  // Tiempo de espera para la estabilización inicial del sensor
  delay(3000); 
}

void loop() {
  // 1. Incrementar el contador de muestras
  numeroMuestra++;

  // 2. Leer el valor analógico y convertirlo a voltaje
  int valorCrudo = analogRead(pinSensorMQ);
  float voltaje = valorCrudo * (5.0 / 1023.0);

  // 3. Imprimir en formato de lista 
  Serial.print("\t");
  Serial.println(voltaje, 2); // 2 decimales

  // Muestreo cada 250 milisegundos 
  delay(250); 
}