#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include "GenerateResponse.h"
#include "styleSheet.min.h"

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

void handlerHome() {
 logAndRespond();
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
 uint16_t sensorReading = analogRead(lightSensorPin);
 setConfigVariable(EE_SENSORMIN, sensorMin, sensorReading);
 logAndRespond("Captured Dim Room at " + String(sensorReading));
}

void handlerCaptureBright() {
 uint16_t sensorReading = analogRead(lightSensorPin);
 setConfigVariable(EE_SENSORMAX, sensorMax, sensorReading);
 logAndRespond("Captured Bright Room at " + String(sensorReading));
}

void handlerBrightness() {
 uint16_t newMin = (uint16_t)(webServer.arg("brightness_min").toInt());
 uint16_t newMax = (uint16_t)(webServer.arg("brightness_max").toInt());
 setConfigVariable(EE_BRIGHTNESSMIN, brightnessMin, newMin);
 setConfigVariable(EE_BRIGHTNESSMAX, brightnessMax, newMax);
 logAndRespond("LED Brightness Min is " + (String)newMin + " and Max is " + (String)newMax);
}

void handlerStyleSheet() {
 webServer.send(200, "text/css", styleSheet);
}

void handlerEndSetup() {
 isSetupDone = true;
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
    Serial.print("    Page Not Found: ");
    Serial.print(webServer.uri());
    handlerHome();
  });
  webServer.on("/", handlerHome);
  webServer.on("/styleSheet.min.css", handlerStyleSheet);
  webServer.on("/datetime", handlerDateTime);
  webServer.on("/birthday_add", handlerBirthdayAdd);
  webServer.on("/birthday_remove", handlerBirthdayRemove);
  webServer.on("/capture_dim", handlerCaptureDim);
  webServer.on("/capture_bright", handlerCaptureBright);
  webServer.on("/brightness", handlerBrightness);
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
  Serial.println("Entering Setup Mode:");
  enterSetup();
  int exitMillis = millis() + 300000; //5 minutes
  bool hadConnection = false;
  int numConnections = 0;
  while((millis()< exitMillis && hadConnection == false || hadConnection && numConnections > 0) && isSetupDone != true){ 
    loopSetup();
    numConnections = WiFi.softAPgetStationNum();
    if (hadConnection == false && numConnections > 0){
      Serial.println("    A user has connected");
      hadConnection = true;
    }
  }
  if(isSetupDone){
    Serial.println("    User has finished setup");
  }
  else if(hadConnection){
    Serial.println("    Last user has disconnected");
  }
  else if(millis() >= exitMillis){
    Serial.println("    Setup has exceeded 5 minutes");
  }
  exitSetup();
}
