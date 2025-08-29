#ifndef D3_THINGSPEAK_H
#define D3_THINGSPEAK_H

#include <WiFi.h>
#include <ThingSpeak.h>

extern WiFiClient client;

#define CHANNEL_ID 3051758
#define CHANNEL_API_KEY "5L0QUPMFD56A0P7Q"

void ThingSpeak_setup();
void ThingSpeak_loop();

#endif
