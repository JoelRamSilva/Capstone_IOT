// #define BME_SCK 13
// #define BME_MISO 12
// #define BME_MOSI 11
// #define BME_CS 10

// Adafruit_BME680 bme; // I2C
// //Adafruit_BME680 bme(BME_CS); // hardware SPI
// //Adafruit_BME680 bme(BME_CS, BME_MOSI, BME_MISO,  BME_SCK);
// void BME688_setup(){
//   PMSA003I_SetUp();
//   while (!Serial);
//   Serial.println(F("BME680 async test"));

//   if (!bme.begin()) {
//     Serial.println(F("Could not find a valid BME680 sensor, check wiring!"));
//     while (1);
//   }

//   // Set up oversampling and filter initialization
//   bme.setTemperatureOversampling(BME680_OS_8X);
//   bme.setHumidityOversampling(BME680_OS_2X);
//   bme.setPressureOversampling(BME680_OS_4X);
//   bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
//   bme.setGasHeater(320, 150); // 320*C for 150 ms
// }

// void BME_loop(){
//   unsigned long endTime = bme.beginReading();
//   if (endTime == 0) {
//     Serial.println(F("Failed to begin reading :("));
//     return;
//   }
//   Serial.print(F("Reading started at "));
//   Serial.print(millis());
//   Serial.print(F(" and will finish at "));
//   Serial.println(endTime);

//   Serial.println(F("You can do other work during BME680 measurement."));
//   delay(50); // This represents parallel work.
//   // There's no need to delay() until millis() >= endTime: bme.endReading()
//   // takes care of that. It's okay for parallel work to take longer than
//   // BME680's measurement time.

//   // Obtain measurement results from BME680. Note that this operation isn't
//   // instantaneous even if milli() >= endTime due to I2C/SPI latency.
//   if (!bme.endReading()) {
//     Serial.println(F("Failed to complete reading :("));
//     return;
//   }
//   Serial.print(F("Reading completed at "));
//   Serial.println(millis());

//   Serial.print(F("Temperature = "));
//   Serial.print(bme.temperature);
//   Serial.println(F(" *C"));

//   Serial.print(F("Pressure = "));
//   Serial.print(bme.pressure / 100.0);
//   Serial.println(F(" hPa"));

//   Serial.print(F("Humidity = "));
//   Serial.print(bme.humidity);
//   Serial.println(F(" %"));

//   Serial.print(F("Gas = "));
//   Serial.print(bme.gas_resistance / 1000.0);
//   Serial.println(F(" KOhms"));

//   Serial.print(F("Approx. Altitude = "));
//   Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
//   Serial.println(F(" m"));

//   Serial.println();

//   // Upload to ThingSpeak (Using Field1, Field2, so on of Channel)
//   // ThingSpeak.setField(1, bme.temperature);
//   // ThingSpeak.setField(2, bme.humidity);
//   // ThingSpeak.setField(3, bme.pressure);
//   // ThingSpeak.setField(4, bme.gas_resistance);
//   // ThingSpeak.setField(5, );
//   // ThingSpeak.setField(6, );
//   // ThingSpeak.setField(7, bme.gas_resistance);

//   int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
//   if (x == 200) {
//     Serial.println("ThingSpeak Upload Successfully!");
//   } else {
//     Serial.println("Failure Upload. HTTP Error code: " + String(x));
//   }

//   delay(600000); 
// }

#include "Zanshin_BME680.h"  // Include the BME680 Sensor library
/**************************************************************************************************
** Declare all program constants                                                                 **
**************************************************************************************************/
const uint32_t SERIAL_SPEED = 115200;  ///< Set the baud rate for Serial I/O

/*! The pin used for slave-select can be freely chosen from the digital pins available. This is
    the default pin used on an Arduino Micro */
const uint8_t SPI_CS_PIN = 14;
/**************************************************************************************************
** Declare global variables and instantiate classes                                              **
**************************************************************************************************/
BME680_Class BME680;  ///< Create an instance of the BME680

float altitude(const int32_t press, const float seaLevel = 1013.25);  ///< Forward declaration
float altitude(const int32_t press, const float seaLevel) {
  /*!
  @brief     This converts a pressure measurement into a height in meters
  @details   The corrected sea-level pressure can be passed into the function if it is known,
             otherwise the standard atmospheric pressure of 1013.25hPa is used
             (see https://en.wikipedia.org/wiki/Atmospheric_pressure for details)
  @param[in] press    Pressure reading from BME680
  @param[in] seaLevel Sea-Level pressure in millibars
  @return    floating point altitude in meters.
  */
  static float Altitude;
  Altitude =
      44330.0 * (1.0 - pow(((float)press / 100.0) / seaLevel, 0.1903));  // Convert into meters
  return (Altitude);
}  // of method altitude()
void setup() {
  /*!
  @brief    Arduino method called once at startup to initialize the system
  @details  This is an Arduino IDE method which is called first upon boot or restart. It is only
            called one time and then control goes to the main "loop()" method, from which control
            never returns
  @return   void
  */
  Serial.begin(SERIAL_SPEED);  // Start serial port at Baud rate
#ifdef __AVR_ATmega32U4__      // If this is a 32U4 processor, then wait 3 seconds to initialize USB
  delay(3000);
#endif
  Serial.println(F("Starting Hardware SPIDemo example program for BME680"));
  Serial.print(F("- Initializing BME680 sensor\n"));

  while (!BME680.begin(SPI_CS_PIN))  // Start using hardware SPI protocol
  {
    Serial.println(F("-  Unable to find BME680. Waiting 3 seconds."));
    delay(3000);
  }  // of loop until device is located
  Serial.println(F("- Setting 16x oversampling for all sensors"));
  BME680.setOversampling(TemperatureSensor, Oversample16);
  BME680.setOversampling(HumiditySensor, Oversample16);
  BME680.setOversampling(PressureSensor, Oversample16);
  Serial.println(F("- Setting IIR filter to maximum value of 16 samples"));
  BME680.setIIRFilter(IIR16);
  Serial.print(F("- Setting gas measurement to 320\xC2\xB0\x43 for 150ms\n"));  // "�C" symbol
  BME680.setGas(320, 150);  // 320�c for 150 milliseconds
}  // of method setup()
void loop() {
  /*!
  @brief    Arduino method for the main program loop
  @details  This is the main program for the Arduino IDE, it is an infinite loop
            The "sprintf()" function is to pretty-print the values, since floating point is not
            supported on the Arduino, split the values into those before and those after the
            decimal point.
  @return   void
  */
  static int32_t  temp, humidity, pressure, gas;  // Temp variables
  static char     buf[16];                        // springtf text buffer
  static float    alt;                            // temp altitude
  static uint16_t loopCounter = 0;                // Display iterations
  if (loopCounter % 25 == 0) {                    // Display header
    Serial.print(F("\nLoop Temp\xC2\xB0\x43 Humid% Press hPa   Alt m  Air m"));  // Show header "�C"
    Serial.print(F("\xE2\x84\xA6\n==== ====== ====== ========= ======= =======\n"));
  }                                                      // if-then time to show headers
  BME680.getSensorData(temp, humidity, pressure, gas);   // Get readings
  sprintf(buf, "%4d %3d.%02d", ++loopCounter % 9999,     // Clamp to 9999,
          (int8_t)(temp / 100), (uint8_t)(temp % 100));  // Temp decidegrees
  Serial.print(buf);
  sprintf(buf, "%3d.%03d", (int8_t)(humidity / 1000),
          (uint16_t)(humidity % 1000));  // Humidity milli-%
  Serial.print(buf);
  sprintf(buf, "%7d.%02d", (int16_t)(pressure / 100),
          (uint8_t)(pressure % 100));  // Pressure Pascals
  Serial.print(buf);
  alt = altitude(pressure);                                                // temp altitude
  sprintf(buf, "%5d.%02d", (int16_t)(alt), ((uint8_t)(alt * 100) % 100));  // Altitude in meters
  Serial.print(buf);
  sprintf(buf, "%5d.%02d\n", (int16_t)(gas / 100), (uint8_t)(gas % 100));  // Resistance milliohms
  Serial.print(buf);
  delay(10000);  // Wait 10s before repeating
}  // of method loop()
