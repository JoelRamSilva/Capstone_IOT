#include "BME688.h"

Adafruit_BME680 bme;

void BME688_setup() {
  delay(3000);
  Serial.begin(115200);
  // If your board is a native-USB device (e.g., Leonardo, Micro, SAMD):
  // while (!Serial) { delay(10); }

  Serial.println(F("BME680/688 test"));

  if (!bme.begin()) {
    Serial.println(F("Could not find a valid BME680/688 sensor, check wiring!"));
    while (1) { delay(10); }
  }

  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320°C for 150 ms
}

void BME688_loop() {
  if (!bme.performReading()) {
    Serial.println(F("Failed to perform reading :("));
    delay(500);
    return;
  }
  int i;
  for(i = 0; i < 10; i++){
    if (! bme.performReading()) {
      Serial.println("Failed to perform reading :(");
      continue;
    }

    Serial.print(F("Temperature = "));
    Serial.print(bme.temperature);
    Serial.println(F(" °C"));

    float tempValue = bme.temperature;
    getAvr(tempValue, 1);
  }

  for(i = 0; i < 10; i++){
    if (! bme.performReading()) {
      Serial.println("Failed to perform reading :(");
      continue;
    }

    Serial.print(F("Humidity = "));
    Serial.print(bme.humidity);
    Serial.println(F(" %"));

    float humidValue = bme.humidity;
    getAvr(humidValue, 2);
  }

  for(i = 0; i < 10; i++){
    if (! bme.performReading()) {
      Serial.println("Failed to perform reading :(");
      continue;
    }

    Serial.print(F("Pressure = "));
    Serial.print(bme.pressure / 100.0);
    Serial.println(F(" hPa"));

    float pressValue = bme.pressure / 100.0;
    getAvr(pressValue, 3);
  }

//============EXTRA DATA IF NEEDED===============
  // // Simple dew-point approximation
  // float dewPoint = bme.temperature - ((100.0 - bme.humidity) / 5.0);
  // Serial.print(F("Dew Point ≈ "));
  // Serial.print(dewPoint);
  // Serial.println(F(" °C"));

  // Serial.print(F("Gas = "));
  // Serial.print(bme.gas_resistance / 1000.0); // Ohms -> kOhms
  // Serial.println(F(" kΩ"));

  // Serial.print(F("Approx. Altitude = "));
  // Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  // Serial.println(F(" m"));

  Serial.println();
}