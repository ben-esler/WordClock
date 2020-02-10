#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include "GenerateResponse.h"

const byte DNS_PORT = 53;
IPAddress apIP(172, 217, 28, 1);
DNSServer dnsServer;
ESP8266WebServer webServer(80);

bool isSetupDone = false;

void logAndRespond(String printLog = "") {
 Serial.println("    " + printLog);
 webServer.send(200, "text/html", generateResponse(printLog));
}

void setDateTime() {
 String inDate = webServer.arg("date"); 
 String inTime = webServer.arg("time"); 
 int year = inDate.substring(0,4).toInt();
 int month = inDate.substring(5,7).toInt();
 int day = inDate.substring(8,10).toInt();
 int hour = inTime.substring(0,2).toInt();
 int minute = inTime.substring(3,5).toInt();
 rtc.adjust(DateTime(year, month, day, hour, minute, 0));
 logAndRespond("New Date and Time is " + inDate + " " + inTime);
}

void birthdayAdd() {
 String birthday_new = webServer.arg("birthday_new"); 
 if(birthday_new == ""){
  logAndRespond("No date was set to be added");
  return;
 }
 //Do stuff here
 //Write to EEPROM
 logAndRespond("Added Birthday " + birthday_new);
}

void birthdayRemove() {
 String birthday_index = webServer.arg("birthday_index"); 
 String birthday_date = webServer.arg("birthday_date"); 
 //Do stuff here
 //Write to EEPROM
 logAndRespond("Remove Birthday " + birthday_date + " at index " + birthday_index);
}

void captureDim() {
 //Do stuff here
 //Write to EEPROM
 logAndRespond("Captured Dim Room at " + String(4864));
}

void captureBright() {
 //Do stuff here
 //Write to EEPROM
 logAndRespond("Captured Bright Room at " + String(4864));
}

void brightnessMin() {
 String birthday_removed = webServer.arg("bightness_min"); 
 //Do stuff here
 //Write to EEPROM
 logAndRespond("Dim Room LED Brightness set to " + birthday_removed + " out of 225");
}

void brightnessMax() {
 String birthday_removed = webServer.arg("bightness_max"); 
 //Do stuff here
 //Write to EEPROM
 logAndRespond("Bright Room LED Brightness set to " + birthday_removed + " out of 225");
}

void endSetup() {
 isSetupDone = true;
 Serial.println("    User has finished setup");
}

void enterSetup() {
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP("WordClock Setup");

  // if DNSServer is started with "*" for domain name, it will reply with
  // provided IP to all DNS request
  dnsServer.start(DNS_PORT, "*", apIP);

  // replay to all requests with same HTML
  webServer.onNotFound([]() {
    webServer.send(200, "text/html", generateResponse());
  });
  webServer.on("/datetime", setDateTime);
  webServer.on("/birthday_add", birthdayAdd);
  webServer.on("/birthday_remove", birthdayRemove);
  webServer.on("/capture_dim", captureDim);
  webServer.on("/capture_bright", captureBright);
  webServer.on("/bightness_min", brightnessMin);
  webServer.on("/bightness_max", brightnessMax);
  webServer.on("/end_setup", endSetup);
  
  webServer.begin();
  Serial.println("    Webserver Started");
}

void loopSetup() {
  dnsServer.processNextRequest();
  webServer.handleClient();
}

void exitSetup() {
  webServer.stop();
  WiFi.mode(WIFI_OFF);
  Serial.println("    Webserver Stopped");
}

void runSetup(){
  enterSetup();
  int exitMillis = millis() + 300000; //5 minutes
  delay(1000);
  while(millis()< exitMillis && isSetupDone != true){
    loopSetup();
  }
  if(millis() >= exitMillis){
    Serial.println("    Setup has exceeded 5 minutes");
  }
  exitSetup();
}
