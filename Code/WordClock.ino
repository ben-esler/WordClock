#include "RTClib.h"
#include "EEPROM.h"
RTC_DS1307 rtc;
#include "Configuration.h"
#include "SetupMode.h"

void setup() {
  Serial.begin(57600);
  EEPROM.begin(256); //number of bytes available
  Serial.println("");
  
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    //Have error on LEDS
    while (1);
  }
  loadConfig();
  if(1 == 1){   //Check if setup button is pressed
    Serial.println("Entering Setup Mode:");
    //Have leds show setup
    runSetup();
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
