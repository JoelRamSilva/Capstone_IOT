#ifndef GET_AVRG_H
#define GET_AVRG_H



#include "INA219.h"
#include "PMSA003I.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h>
#include "BME688.h"
#include "D3_thingSpeak.h"

extern Adafruit_BME680 bme;

void getAvr(float tempData, int fieldID);


#endif