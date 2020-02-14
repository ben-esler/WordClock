//EEPROM Locations
//uint16_t is 2 bytes
#define EE_SENSORMIN 0      
#define EE_SENSORMAX 2
#define EE_BRIGHTNESSMIN 4
#define EE_BRIGHTNESSMAX 6
#define EE_BIRTHDAYS 8

//Photosensor
uint16_t sensorMin = 0;
uint16_t sensorMax = 1024;
//3 white diodes with a range of 0-255 per pixel
uint16_t brightnessMin = 0;
uint16_t brightnessMax = 767;
//Bithday dates will have Happy Birthday on LED clock on day of
//Only 10 datesnare really needed
struct Date {
  uint16_t year;
  uint8_t month;
  uint8_t day;
};
//Currently using values for testing
Date birthdays[10] = {{1992, 04, 23},
                      {1993, 04, 2},
                      {2010, 04, 12},
                      {1989, 7, 15},
                      {1790, 04, 12},
                      {2011, 12, 2},
                      {3512, 12, 22}};
                      
Date stringToDate(String inDate){
  Date outDate;
  outDate.year = inDate.substring(0,4).toInt();
  outDate.month = inDate.substring(5,7).toInt();
  outDate.day = inDate.substring(8,10).toInt();
  return outDate;
}

String dateToString(Date inDate){
  String outDate = (String)inDate.year + "-";
  if (inDate.month < 10){outDate += "0";}
  outDate += (String)inDate.month + "-";
  if (inDate.day < 10){outDate += "0";}
  outDate +=(String)inDate.day;
  return outDate;
}

void setConfigVariable(int eeAddr, uint16_t& variable, uint16_t value){
  variable = value;
  EEPROM.put(eeAddr, variable);  
  EEPROM.commit();
}

void addBirthday(Date birthday){
  //Set Birthdays
  //Save to EEPROM
}

void removeBirthday(int birthdayIndex){
  //Set Birthdays
  //Save to EEPROM
}
void loadConfig(){
  EEPROM.get(EE_SENSORMIN, sensorMin);
  EEPROM.get(EE_SENSORMAX, sensorMax);
  EEPROM.get(EE_BRIGHTNESSMIN, brightnessMin);
  EEPROM.get(EE_BRIGHTNESSMAX, brightnessMax);
  //EEPROM.get(EE_BRITHDAYS, birthdays);
}
