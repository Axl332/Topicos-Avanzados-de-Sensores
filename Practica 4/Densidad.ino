#include <Wire.h>
#include <Adafruit_BMP085.h>

Adafruit_BMP085 bmp;

void setup() {
  Serial.begin(9600);

  if (!bmp.begin()) {
    Serial.println("No se encontró BMP180");
    while (1);
  }
}

void loop() {

  float temperatura = bmp.readTemperature();
  float presion = bmp.readPressure();

  // densidad aproximada
  float R = 287.05;

  float densidad = presion / (R * (temperatura + 273.15));

  Serial.print("Temperatura: ");
  Serial.println(temperatura);

  Serial.print("Presion: ");
  Serial.println(presion);

  Serial.print("Densidad: ");
  Serial.println(densidad);

  delay(2000);
}
