#include <Adafruit_DotStar.h>
#define NUMPIXELS 3
#define DATAPIN    12
#define CLOCKPIN   14
Adafruit_DotStar strip(NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BRG);

float led[11][11];
uint8_t ledValues[11][11][3];

void ledAlphaToValues(){
  for(uint8_t row = 0; row < 11; row++){
    for(uint8_t col = 0; col < 11; col++){
      float ledAlpha = led[row][col];
      uint8_t ledValue[3] = {0};
      if(ledAlpha != 0.0){
        uint16_t ledBrightness = lerp(brightnessMin, brightnessMax, ledAlpha*ambientBrightness);
        ledValue[0] = ceil(ledBrightness/3.0);
        ledValue[1] = ceil((ledBrightness-ledValue[0])/2.0);
        ledValue[2] = ledBrightness - ledValue[0] - ledValue[1];
      }
      for(uint8_t diodeIndex = 0; diodeIndex < 3; diodeIndex++){
        ledValues[row][col][diodeIndex] = ledValue[diodeIndex];
      }
    }
  }  
}

void ledValuesMirrorRows(uint8_t startIndex, bool everyOther){
  uint8_t mirror[11][3];
  for(uint8_t row = startIndex; row < 11; row = everyOther ? row+2 : row++){
    for(uint8_t col = 0; col < 11; col++){
      for(uint8_t diodeIndex = 0; diodeIndex < 3; diodeIndex++){
        mirror[col][diodeIndex] = ledValues[row][10-col][diodeIndex];
      }
    }
    for(uint8_t col = 0; col < 11; col++){
      for(uint8_t diodeIndex = 0; diodeIndex < 3; diodeIndex++){
        ledValues[row][col][diodeIndex] = mirror[col][diodeIndex];
      }
    }
  }  
}

void ledValuesMirrorCols(uint8_t startIndex, bool everyOther){
  uint8_t mirror[11][3];
  for(uint8_t col = startIndex; col < 11; col = everyOther ? col+2 : col++){
    for(uint8_t row = 0; row < 11; row++){
      for(uint8_t diodeIndex = 0; diodeIndex < 3; diodeIndex++){
        mirror[row][diodeIndex] = ledValues[10-row][col][diodeIndex];
      }
    }
    for(uint8_t row = 0; row < 11; row++){
      for(uint8_t diodeIndex = 0; diodeIndex < 3; diodeIndex++){
        ledValues[row][col][diodeIndex] = mirror[row][diodeIndex];
      }
    }
  }  
}

void draw(){
  ledAlphaToValues();
  ledValuesMirrorCols(0, false);
  ledValuesMirrorRows(1, true);
  for(uint8_t col = 0; col < 11; col++){
    for(uint8_t row = 0; row < 11; row++){
      strip.setPixelColor(row+col,ledValues[row][col][0],ledValues[row][col][1],ledValues[row][col][2]);
    }
  }
  strip.show();
}
