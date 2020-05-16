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
  
  if(1 == 1){   //Check if setup button is pressed
    digitalWrite(2,  true);
    drawSetup();
    runSetup();
    drawClear();
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
  clockUpdate();
  draw();
  
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
