#ifndef BME688_H
#define BME688_H

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h>
#include "D3_thingSpeak.h"
#include "ThingSpeak.h"
#include "get_Avrg.h"

#define SEALEVELPRESSURE_HPA (1013.25)

extern Adafruit_BME680 bme; // I2C

void BME688_setup();
void BME688_loop();

#endif