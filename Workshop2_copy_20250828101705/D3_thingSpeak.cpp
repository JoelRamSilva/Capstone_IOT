#include <D3_thingSpeak.h>

WiFiClient client;

void ThingSpeak_setup() {
  Serial.begin(9600);
  
  ThingSpeak.begin(client);
}

void ThingSpeak_loop() {
  //counter++;

  //ThingSpeak.writeField(CHANNEL_ID, fieldNumb, dataNumb, CHANNEL_API_KEY);

  delay(15000); // 15 seconds
}