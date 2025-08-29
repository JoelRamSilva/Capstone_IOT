#ifndef INA219_H
#define INA219_H

#include <Wire.h>
#include <Adafruit_INA219.h>
#include "get_Avrg.h"

extern Adafruit_INA219 ina219;

void INA219_setup();
void INA219_loop();

#endif