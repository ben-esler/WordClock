//EEPROM Locations
//uint16_t is 2 bytes
#define EE_SENSORMIN 0      
#define EE_SENSORMAX 2
#define EE_BRIGHTNESSMIN 4
#define EE_BRIGHTNESSMAX 6
#define EE_BIRTHDAYS 8

//Photosensor
uint16_t sensorMin; //0
uint16_t sensorMax; //1024
//3 white diodes with a range of 0-255 per pixel
uint16_t brightnessMin; //0
uint16_t brightnessMax; //767
//When setting the value of the pixels increase across all diodes
//212 (70,70,70)
//213 (71,70,70)
//214 (71,71,70)
//215 (71,71,71)
//216 (72,71,71)
//217 (72,72,71)

struct Date {
  uint16_t year;
  uint8_t month;
  uint8_t day;
};

//Date birthdays[0];

void loadConfigVariable(uint16_t& variable, int eeAddr, uint16_t fallbackValue){
  EEPROM.get(eeAddr, variable);
}

void setConfigVariable(uint16_t& variable, int eeAddr, uint16_t value){
  variable = value;
  EEPROM.put(eeAddr, variable);  
  EEPROM.commit();
}

void loadBirthdays(){
  //load from EEPROM
}

void addBirthday(){
  //Set Birthdays
  //Save to EEPROM
}

void removeBirthday(){
  //Set Birthdays
  //Save to EEPROM
}
void loadConfig(){
  loadConfigVariable(sensorMin, EE_SENSORMIN, 0);
  loadConfigVariable(sensorMax, EE_SENSORMAX, 1024);
  loadConfigVariable(brightnessMin, EE_BRIGHTNESSMIN, 200);
  loadConfigVariable(brightnessMax, EE_BRIGHTNESSMAX, 600);
  loadBirthdays();
}
