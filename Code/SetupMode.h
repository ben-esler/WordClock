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

void handlerDateTime() {
 Date inDate = stringToDate(webServer.arg("date")); 
 String inTime = webServer.arg("time"); 
 int hour = inTime.substring(0,2).toInt();
 int minute = inTime.substring(3,5).toInt();
 rtc.adjust(DateTime(inDate.year, inDate.month, inDate.day, hour, minute, 0));
 logAndRespond("New Date and Time is " + dateToString(inDate) + " " + inTime);
}

void handlerBirthdayAdd() {
 String birthday = webServer.arg("birthday_new"); 
 if(birthday == ""){
  logAndRespond("No date was set to be added");
 }
 addBirthday(stringToDate(birthday));
 logAndRespond("Added Birthday " + birthday);
}

void handlerBirthdayRemove() {
 uint8_t birthdayIndex = webServer.arg("birthday_index").toInt(); 
 String birthday = webServer.arg("birthday_date"); 
 removeBirthday(birthdayIndex);
 logAndRespond("Remove Birthday " + birthday + " at index " + birthdayIndex);
}

void handlerCaptureDim() {
 //Capture value
 uint16_t sensorReading = 200;
 setConfigVariable(EE_SENSORMIN, sensorMin, sensorReading);
 logAndRespond("Captured Dim Room at " + String(sensorReading));
}

void handlerCaptureBright() {
 //Capture value
 uint16_t sensorReading = 900;
 setConfigVariable(EE_SENSORMAX, sensorMax, sensorReading);
 logAndRespond("Captured Bright Room at " + String(sensorReading));
}

void handlerBrightnessMin() {
 uint16_t brightness = (uint16_t)(webServer.arg("bightness_min").toInt());
 setConfigVariable(EE_BRIGHTNESSMIN, brightnessMin, brightness);
 logAndRespond("Dim Room LED Brightness set to " + (String)brightnessMin + " out of 767");
}

void handlerBrightnessMax() {
 uint16_t brightness = (uint16_t)(webServer.arg("bightness_max").toInt());
 setConfigVariable(EE_BRIGHTNESSMAX, brightnessMax, brightness);
 logAndRespond("Bright Room LED Brightness set to " + (String)brightnessMax + " out of 767");
}

void handlerEndSetup() {
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
  webServer.on("/datetime", handlerDateTime);
  webServer.on("/birthday_add", handlerBirthdayAdd);
  webServer.on("/birthday_remove", handlerBirthdayRemove);
  webServer.on("/capture_dim", handlerCaptureDim);
  webServer.on("/capture_bright", handlerCaptureBright);
  webServer.on("/bightness_min", handlerBrightnessMin);
  webServer.on("/bightness_max", handlerBrightnessMax);
  webServer.on("/end_setup", handlerEndSetup);
  
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
  while(millis()< exitMillis && isSetupDone != true){
    loopSetup();
  }
  if(millis() >= exitMillis){
    Serial.println("    Setup has exceeded 5 minutes");
  }
  exitSetup();
}
