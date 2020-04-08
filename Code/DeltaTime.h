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

// Easing Functions
// power 2 quad, 3 cubic, 4 quart, 5 quint, etc
float linear(float t, float power){
  return t;
}
float easeIn(float t, float power){
  return pow(t, power);
}
float easeOut(float t, float power){
  return 1.0-abs(pow(t-1, power));
}
float easeInOut(float t, float power){
  return t<0.5 ? easeIn(t*2.0,power)/2.0 : easeOut(t*2.0-1.0, power)/2+0.5;
}
