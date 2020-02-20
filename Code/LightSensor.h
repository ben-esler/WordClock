const int sensorPin = A0;

const uint8_t sensorNumReadings = 50;
uint16_t sensorReadings[sensorNumReadings] = {0};
uint8_t sensorReadIndex = 0;
uint32_t sensorTotal = 0;
float ambientBrightness = 0.0;

uint16_t sensorSample(uint8_t numberOfSamples){
  uint32_t total = 0; //numberOfSamples * maxSensorValue = 255 * 1,024 = 261,120 > uint16_t so its a uint32_t
  for(uint8_t i = 0; i < numberOfSamples; i++){
    total += analogRead(sensorPin);
    delay(1); // delay in between reads for stability
  }
  return total/numberOfSamples;
}

void updateAmbientBrightness(uint32_t transitionTime){
  sensorTotal = sensorTotal - sensorReadings[sensorReadIndex]; //subtract old reading
  sensorReadings[sensorReadIndex] = analogRead(sensorPin);
  sensorTotal = sensorTotal + sensorReadings[sensorReadIndex]; //add new reading
  sensorReadIndex++;
  
  // if we're at the end of the readings go back to the start
  if (sensorReadIndex >= sensorNumReadings) {
    sensorReadIndex = 0;
  }
  float target = constrain(sensorTotal / sensorNumReadings, sensorMin, sensorMax);
  target = map(target, sensorMin, sensorMax, 0, 1024)/1024.0;
  changeFloatOverDelta(ambientBrightness, target, transitionTime);
}

void printAmbientBrightness(){
  //Current: 282  Buffered: 226 Clamp: 226  Remap: 214  Float: 0.2090 Smooth: 0.2097  Brightness: 262  DeltaTime: 19ms
  uint16_t sensorAverage = sensorTotal / sensorNumReadings;
  uint16_t sensorAverageClamp = constrain(sensorAverage, sensorMin, sensorMax);
  uint16_t sensorAverageRemap = map(sensorAverageClamp, sensorMin, sensorMax, 0, 1024);
  Serial.print("Current: ");
  Serial.print(sensorReadings[sensorReadIndex]);
  Serial.print("\tBuffered: ");
  Serial.print(sensorAverage);
  Serial.print("\tClamp: ");
  Serial.print(sensorAverageClamp);
  Serial.print("\tRemap: ");
  Serial.print(sensorAverageRemap);
  Serial.print("\tFloat: ");
  Serial.print((float)sensorAverageRemap/1024.0,4);
  Serial.print("\tSmooth: ");
  Serial.print(ambientBrightness,4);
  Serial.print("\tBrightness: ");
  Serial.print((uint16_t)lerp(brightnessMin, brightnessMax, ambientBrightness));
  Serial.print("\t DeltaTime: ");
  Serial.print(deltaTime);
  Serial.println("ms");
}
