unsigned long oldTime = 0;
unsigned long deltaTime = 0;

void calculateDeltaTime(){
  unsigned long currentTime = millis();
  deltaTime = currentTime - oldTime;
  oldTime = currentTime;
}


void changeFloatOverDelta(float &current, float target, uint32_t transitionTime){
  current = current+(target-current)*(float(deltaTime)/transitionTime);
}

float lerp(float a, float b, float x)
{
  return a + x * (b - a);
}
