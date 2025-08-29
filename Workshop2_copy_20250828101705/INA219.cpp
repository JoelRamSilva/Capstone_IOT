
#include <INA219.h>

Adafruit_INA219 ina219;


void INA219_setup(){
  uint32_t currentFrequency;

  Serial.println("Measuring Voltage and Current: ");
  ina219.begin();
}

void INA219_loop(){
  float shuntvoltage = 0;
  float busvoltage = 0;
  float current_mA = 0;
  float loadvoltage = 0;

  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  //current_mA = ina219.getCurrent_mA();
  loadvoltage = busvoltage + (shuntvoltage / 1000);

  // Serial.print("Bus Voltage:   "); Serial.print(busvoltage); Serial.println(" V");
  // Serial.print("Shunt Voltage: "); Serial.print(shuntvoltage); Serial.println(" mV");
  // Serial.print("Load Voltage:  "); Serial.print(loadvoltage); Serial.println(" V");
  // Serial.print("Current:       "); Serial.print(current_mA); Serial.println(" mA");
  // Serial.println("");


int i;
  for(i = 0; i < 10; i++){
    current_mA = ina219.getCurrent_mA();
    Serial.print(F("Current = "));
    Serial.println(current_mA);

    //float tempValue = bme.temperature;
    getAvr(current_mA, 4);
  }

  for(i = 0; i < 10; i++){
    busvoltage = ina219.getBusVoltage_V();
    Serial.print(F("Voltage = "));
    Serial.println(busvoltage);

    //float tempValue = bme.temperature;
    getAvr(busvoltage, 5);
  }
  
}