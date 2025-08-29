#ifndef PMSA003I_H
#define PMSA003I_H

#include "Adafruit_PM25AQI.h"
#include "get_Avrg.h"

extern Adafruit_PM25AQI aqi;

void PMSA003I_SetUp();
void PMSA003I_loop();

#endif