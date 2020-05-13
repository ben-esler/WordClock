#include <Adafruit_DotStar.h>
#define NUMPIXELS 121
#define DATAPIN   12
#define CLOCKPIN  14
Adafruit_DotStar strip(NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BRG);

uint16_t transitionTime = 0;
float ledAlphas[121];
uint8_t ledValues[121][3];


void transitionFill(uint16_t duration, boolean fadeIn){
  if(transitionTime < duration){
    float transitionAlpha = (float)transitionTime/(float)duration;
    for(int8_t i = 0; i < ledQueLastIndex; i++){
      if(fadeIn){
        ledAlphas[ledQue[i]] = easeIn(transitionAlpha, 4);
      }
      else{
        ledAlphas[ledQue[i]] = 1-easeOut(transitionAlpha, 4);
      }
    }
    transitionTime += deltaTime;
  }
  else{
    transitionTime = 0;
    transitioning = 0;
  }
}

void transitionSpell(uint16_t duration, boolean fadeIn){
  if(transitionTime < duration){
    float transitionAlpha = (float)transitionTime/(float)duration;
    float softness = 5;
    for(int8_t i = 0; i < ledQueLastIndex; i++){
      float value = 1-unlerp(transitionAlpha*ledQueLastIndex-lerp(softness*2,0,transitionAlpha),transitionAlpha*ledQueLastIndex+softness,i);
      if(fadeIn){
        ledAlphas[ledQue[i]] = easeIn(value, 4);
      }
      else{
        ledAlphas[ledQue[i]] = 1-easeIn(value, 4);
      }
    }
    transitionTime += deltaTime;
  }
  else{
    transitionTime = 0;
    transitioning = 0;
  }
}

void ledAlphaToValues(){
  for(int8_t i = 0; i < ledQueLastIndex; i++){
    float ledAlpha = ledAlphas[ledQue[i]];
    uint8_t ledValue[3] = {0};
    if(ledAlpha != 0.0){
      uint16_t ledBrightness = ledAlpha*lerp(brightnessMin, brightnessMax, ambientBrightness);
      ledValue[0] = ceil(ledBrightness/3.0);
      ledValue[1] = ceil((ledBrightness-ledValue[0])/2.0);
      ledValue[2] = ledBrightness - ledValue[0] - ledValue[1];
    }
    for(uint8_t diodeIndex = 0; diodeIndex < 3; diodeIndex++){
      ledValues[ledQue[i]][diodeIndex] = ledValue[diodeIndex];
    }
  }
}

void draw(){
  if(transitioning == 1){
    transitionSpell(400*ledQueLastIndex, true);
  }
  if(transitioning == -1){
    transitionFill(5000, false);
  }
  ledAlphaToValues();
  for(int8_t i = 0; i < ledQueLastIndex; i++){
    uint8_t led = ledQue[i];
    strip.setPixelColor(led, ledValues[led][0], ledValues[led][1], ledValues[led][2]);
  }
  strip.show();
}
