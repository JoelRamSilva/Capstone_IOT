#include "get_Avrg.h"

float tempF; 
float humRH; 
float pressureAlt;
float totalCurrentConsumption;
float voltage;
int counter = 0; 
float total = 0;

void getAvr(float tempData, int fieldID){
    
    total += tempData;
    // Sample data every minute
    delay(60000);
    counter ++;
    if(counter == 10){
      float dataAvrg = total / 10;
      Serial.println(F("dataAvrg: "));
      Serial.print(dataAvrg);
      ThingSpeak.setField(fieldID, dataAvrg);
      ThingSpeak.writeFields(CHANNEL_ID, CHANNEL_API_KEY);
      counter = 0;
      total = 0;
      dataAvrg = 0;
    }
}

