#include "RTClib.h"
#include "EEPROM.h"
RTC_DS1307 rtc;
const int lightSensorPin = 0;
#include "Configuration.h"
#include "SetupMode.h"

void setup() {
  Serial.begin(57600);
  EEPROM.begin(88); //number of bytes available
  Serial.println("");
  Serial.println("");
  
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    //Have error on LEDS
    while (1);
  }
  loadConfig();
  printConfig();
  
  if(1 == 1){   //Check if setup button is pressed
    //Have leds show setup
    runSetup();
  }
  EEPROM.end();
}

void loop() {
  // put your main code here, to run repeatedly:

}
