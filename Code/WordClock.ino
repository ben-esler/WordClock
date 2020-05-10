#include "RTClib.h"
#include "EEPROM.h"
RTC_DS1307 rtc;
#include "Configuration.h"
#include "DeltaTime.h"
#include "LightSensor.h"
#include "Clock.h"
#include "Display.h"
#include "SetupMode.h"


int16_t boardLedTime = 0;
boolean boardLedOn = 0;
int16_t timeSinceUpdate = 0;
boolean isUpdating = 1;

  
void setup() {
  pinMode(2, OUTPUT);
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
  draw();

  if(isUpdating){
    if(transitioning == 0){
      updateLedQue();
      transitioning = 1;
      isUpdating = 0;
    }
  }
  else{
    if(timeSinceUpdate < 8000){
      timeSinceUpdate += deltaTime;
    }
    else{
      timeSinceUpdate = 0;
      transitioning = -1;
      isUpdating = 1;
    }
  }
  
  //Blink onboard led
  if(boardLedTime < 1000){
    boardLedTime += deltaTime;
  }
  else{
    digitalWrite(2,  !boardLedOn);
    boardLedOn = !boardLedOn;
    boardLedTime = 0;
  }
}
