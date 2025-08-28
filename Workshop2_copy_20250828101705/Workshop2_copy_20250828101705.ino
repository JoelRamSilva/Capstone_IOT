#include <WiFi.h>
#include "DHT.h"
#include "ThingSpeak.h"
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>

// Setting WiFi 
const char* ssid = "CapstoneWifi2";
const char* password = "RuleNumber9";

// Setting ThingSpeak
unsigned long myChannelNumber = YOUR_CHANNEL_NUMBER;
const char * myWriteAPIKey = "YOUR_WRITE_API_KEY";

// Setting DHT Sensor
#define DHTPIN 4        // 센서를 연결한 ESP32 핀 
#define DHTTYPE DHT22   // DHT11 사용 시 DHT11로 변경
DHT dht(DHTPIN, DHTTYPE);

WiFiClient client;

void setup() {
  Serial.begin(115200);
  dht.begin();

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
  // read data from sensor
  float h = dht.readHumidity();
  float t = dht.readTemperature(true); // true → (°F), false → (°C)

  // check sensor error
  if (isnan(h) || isnan(t)) {
    Serial.println("DHT fail to read sensor");
    delay(2000);
    return;
  }

  Serial.print("Temperature (°F): ");
  Serial.println(t);
  Serial.print("Humidity (%): ");
  Serial.println(h);

  // Upload to ThingSpeak (Using Field1, Field2 of Channel)
  ThingSpeak.setField(1, t);
  ThingSpeak.setField(2, h);

  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if (x == 200) {
    Serial.println("ThingSpeak Upload Successfully!");
  } else {
    Serial.println("Failure Upload. HTTP Error code: " + String(x));
  }

  delay(600000);
}
