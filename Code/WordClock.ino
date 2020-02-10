#include "RTClib.h"
RTC_DS1307 rtc;

#include "SetupMode.h"

void setup() {
  Serial.begin(57600);
  Serial.println("");
  
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    //Have error on LEDS
    while (1);
  }
  
  if(1 == 1){   //Check if setup button is pressed
    Serial.println("Entering Setup Mode:");
    //Have leds show setup
    runSetup();
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
