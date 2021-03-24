#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
// #define SEA_LEVEL_PRESSURE_HPA (1013.25)

Adafruit_BME280 bme;

void setup() {
  Serial.begin(9600);
  if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
}
void loop() {
  // Brightness (resistor)
  // @see https://www.storange.jp/2012/03/arduinocds.html
  Serial.print("brightness:");
//  Serial.print(1023 - analogRead(0));
  Serial.print(4095 - analogRead(0));
//  Serial.print(analogRead(0));
  Serial.print("\t"); 
  
  // Temperature ˚C
  Serial.print("temperature:");
  Serial.print(bme.readTemperature());
  Serial.print("\t");
  
  // Pressure hPa
  Serial.print("pressure:");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.print("\t");
  
  // Humidity %
  Serial.print("humidity:");
  Serial.print(bme.readHumidity());
  
  Serial.println();
  delay(1000);
}
