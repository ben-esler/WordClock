/*
long ledMatrix[11][11];


void updateDisplay(long input[11][11]){
  long output[11][11] = {0.0};
  for(int row = 0; row < 11; col++){
    for(int col = 0; col < 11; col++){
      if(input[row][col] != 0.0){
        output[row][col] = map(input[row][col] * ambientLight, 0.0, 1.0, (long)brightnessMin, (long)brightnessMin);
      }
    }
  }
  //multiply each led(0-1) by ambientLight
  //remap each leds 0-1 to min/max bright
  //set that was initially 0 back to zero
  //mirror odd row strips
  //push to leds  
}
*/
