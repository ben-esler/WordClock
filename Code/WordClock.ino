#include "RTClib.h"
#include "EEPROM.h"
RTC_DS1307 rtc;
#include "Configuration.h"
#include "DeltaTime.h"
#include "LightSensor.h"
#include "Display.h"
#include "SetupMode.h"



void setup() {
  Serial.begin(57600);
  EEPROM.begin(88); //number of bytes available
  strip.begin();
  strip.show();
  rtc.begin();
  Serial.println("");
  Serial.println("");
  
  loadConfig();
  printConfig();
  
  if(1 == 0){   //Check if setup button is pressed
    //Have leds show setup
    runSetup();
  }
  EEPROM.end();
  oldTime = millis();
  deltaTime = millis();
  for(uint8_t i = 0; i < 100; i++){
    calculateDeltaTime();
    updateAmbientBrightness(100);
    delay(1); // delay in between reads for stability
  }
}

void loop() {
  calculateDeltaTime();
  updateAmbientBrightness(30000); //30000 for 30 seconds for adjustment time
  //printAmbientBrightness(); //used for debug of sensor
  //draw();

}
