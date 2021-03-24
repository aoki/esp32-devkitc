#include <Wire.h>
#include <WiFi.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <InfluxDbClient.h>

// InfluxDB  server url. Don't use localhost, always server name or ip address.
#define INFLUXDB_URL "host:port"
#define INFLUXDB_DB_NAME "home"
#define HOST_NAME "hostname"
InfluxDBClient client(INFLUXDB_URL, INFLUXDB_DB_NAME);
Point sensor("sensors"); // Measurement

Adafruit_BME280 bme;

const char* ssid     = "ssid";
const char* password = "password";

void setup() {
  Serial.begin(115200);


  // ---------------------------------
  // Setup for WiFi

  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());


  // ---------------------------------
  // Setup for InfluxDB

  sensor.addTag("host", HOST_NAME);

  // Check server connection
  if (client.validateConnection()) {
    Serial.print("Connected to InfluxDB: ");
    Serial.println(client.getServerUrl());
  } else {
    Serial.print("InfluxDB connection failed: ");
    Serial.println(client.getLastErrorMessage());
  }

  // ---------------------------------
  // Setup for BME280

  if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

}


void loop() {
  // ----------------------------------------------------------
  // Brightness (resistor)
  // @see https://www.storange.jp/2012/03/arduinocds.html
  int illuminance = 4095 - analogRead(33);
  Serial.print("brightness:");
  Serial.print(illuminance);
  Serial.print("\t");

  // ----------------------------------------------------------
  // Temperature ˚C
  float temperature = bme.readTemperature();
  Serial.print("temperature:");
  Serial.print(temperature);
  Serial.print("\t");

  // Pressure hPa
  int pressure = bme.readPressure() / 100.0F;
  Serial.print("pressure:");
  Serial.print(pressure);
  Serial.print("\t");

  // Humidity %
  float humidity = bme.readHumidity();
  Serial.print("humidity:");
  Serial.print(humidity);
  Serial.println();

  // ----------------------------------------------------------
  // Write to Influx DB
  sensor.clearFields();
  sensor.addField("pressure", pressure);
  sensor.addField("temperature", temperature);
  sensor.addField("humidity", humidity);
  sensor.addField("illuminance", illuminance);

  // Print what are we exactly writing
  Serial.print("Writeriting: ");
  Serial.println(client.pointToLineProtocol(sensor));

  // Write point
  if (!client.writePoint(sensor)) {
    Serial.print("InfluxDB write failed: ");
    Serial.println(client.getLastErrorMessage());
  }

  Serial.println();
  delay(5000);
}
