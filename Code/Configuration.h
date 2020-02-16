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
  Date() : year(0), month(0), day(0) {}
  uint16_t year;
  uint8_t month;
  uint8_t day;
};
Date birthdays[10];
                      
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
  int birthdayIndex = 0;
  while (birthdays[birthdayIndex].year != 0){
    birthdayIndex++;
  }
  birthdays[birthdayIndex] = birthday;
  EEPROM.put(EE_BIRTHDAYS, birthdays); 
  EEPROM.commit();
}

void removeBirthday(int index){
  int birthdayIndex = index;
  while (birthdayIndex < 9){
    if (birthdays[birthdayIndex+1].year != 0){
      birthdays[birthdayIndex] = birthdays[birthdayIndex+1];
    }
    else {
      birthdays[birthdayIndex] = Date();
    }
    birthdayIndex++;
  }
  birthdays[birthdayIndex] = Date();
  EEPROM.put(EE_BIRTHDAYS, birthdays);
  EEPROM.commit();
}

void loadConfig(){
  Serial.println("Loading Config from EEPROM:");
  EEPROM.get(EE_SENSORMIN, sensorMin);
  EEPROM.get(EE_SENSORMAX, sensorMax);
  EEPROM.get(EE_BRIGHTNESSMIN, brightnessMin);
  EEPROM.get(EE_BRIGHTNESSMAX, brightnessMax);
  EEPROM.get(EE_BIRTHDAYS, birthdays);
}

void printConfig(){
  Serial.println("    sensorMin: " + (String)sensorMin);
  Serial.println("    sensorMax: " + (String)sensorMax);
  Serial.println("    brightnessMin: " + (String)brightnessMin);
  Serial.println("    brightnessMax: " + (String)brightnessMax);
  for (int i = 0; i < 10; i++) {
    Serial.println("    birthday[" + (String)i + "]: " + dateToString(birthdays[i]));
  }
  Serial.println("");
}
