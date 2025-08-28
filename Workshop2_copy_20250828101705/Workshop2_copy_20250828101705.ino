#include <WiFi.h>
// #include "DHT.h"
#include "ThingSpeak.h"
#include <SPI.h>
#include <Adafruit_BME680.h>
#include <Adafruit_Sensor.h>

// Setting WiFi 
const char* ssid = "CapstoneWifi2";
const char* password = "RuleNumber9";

// Setting ThingSpeak
unsigned long myChannelNumber = 3051754;
const char * myWriteAPIKey = "5B7F31T5R7TPH4MC";


WiFiClient client;

// Create a sensor object
Adafruit_BME680 bme; // I2C
//Adafruit_BME680 bme(BME_CS); // hardware SPI
//Adafruit_BME680 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK);

void setup() {
  Serial.begin(115200);
  //dht.begin();

  while (!Serial);
  Serial.println(F("BME680 async test"));

  if (!bme.begin()) {
    Serial.println(F("Could not find a valid BME680 sensor, check wiring!"));
    while (1);
  }

  // Set up oversampling and filter initialization
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("WiFi setting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");

  ThingSpeak.begin(client);
}

void loop() {
  
  unsigned long endTime = bme.beginReading();
  if (endTime == 0) {
    Serial.println(F("Failed to begin reading :("));
    return;
  }
  Serial.print(F("Reading started at "));
  Serial.print(millis());
  Serial.print(F(" and will finish at "));
  Serial.println(endTime);

  Serial.println(F("You can do other work during BME680 measurement."));
  delay(50); // This represents parallel work.
  // There's no need to delay() until millis() >= endTime: bme.endReading()
  // takes care of that. It's okay for parallel work to take longer than
  // BME680's measurement time.

  // Obtain measurement results from BME680. Note that this operation isn't
  // instantaneous even if milli() >= endTime due to I2C/SPI latency.
  if (!bme.endReading()) {
    Serial.println(F("Failed to complete reading :("));
    return;
  }
  Serial.print(F("Reading completed at "));
  Serial.println(millis());

  Serial.print(F("Temperature = "));
  Serial.print(bme.temperature);
  Serial.println(F(" *C"));

  Serial.print(F("Pressure = "));
  Serial.print(bme.pressure / 100.0);
  Serial.println(F(" hPa"));

  Serial.print(F("Humidity = "));
  Serial.print(bme.humidity);
  Serial.println(F(" %"));

  Serial.print(F("Gas = "));
  Serial.print(bme.gas_resistance / 1000.0);
  Serial.println(F(" KOhms"));

  Serial.print(F("Approx. Altitude = "));
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(F(" m"));

  Serial.println();

  // Upload to ThingSpeak (Using Field1, Field2, so on of Channel)
  ThingSpeak.setField(1, bme.temperature);
  ThingSpeak.setField(2, bme.pressure);
  ThingSpeak.setField(3, bme.humidity);
  ThingSpeak.setField(4, bme.gas_resistance);
  ThingSpeak.setField(5, bme.readAltitude(SEALEVELPRESSURE_HPA));

  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if (x == 200) {
    Serial.println("ThingSpeak Upload Successfully!");
  } else {
    Serial.println("Failure Upload. HTTP Error code: " + String(x));
  }

  delay(600000); 
}
