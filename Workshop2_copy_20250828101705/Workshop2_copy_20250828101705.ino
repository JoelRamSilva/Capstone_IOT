#include "D3_WiFi.h"
#include "D3_thingSpeak.h"
//#include <SPI.h>
#include "BME688.h"
#include "INA219.h"
#include "PMSA003I.h"
#include "get_Avrg.h"
#include "D3_CO2.h"



void setup() {
  Serial.begin(115200);

  wifi_setup();
  ThingSpeak_setup();

  BME688_setup();
  INA219_setup();
  PMSA003I_SetUp();
  //co2_setup();
  
}

void loop() {

  BME688_loop();
  INA219_loop();
  PMSA003I_loop();
  //co2_loop();

}
