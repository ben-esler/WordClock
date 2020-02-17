# WordClock
ESP8266 based clock that spells the time with LEDs

## About

## Table of Contents

- [About](#about)
- [Libraries](#libraries)
- [Physical Build](#physical-build)
  * [Components](#components)
  * [Hardware](#hardware)
- [Running The Clock](#running-the-clock)
  * [Setup Mode](#setup-mode)
  * [Displaying Time](#displaying-time)

## Libraries
- [RTClib](https://github.com/adafruit/RTClib)
- [EEPROM](https://www.arduino.cc/en/Reference/EEPROM)
- [ESP8266WiFi](https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/readme.html)
- [ESP8266WebServer](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WebServer)
- [DNSServer](https://github.com/esp8266/Arduino/tree/master/libraries/DNSServer)
- [Adafruit DotStar](https://github.com/adafruit/Adafruit_DotStar)
## Physical Build
### Components
- [Adafruit Feather HUZZAH with ESP8266](https://www.adafruit.com/product/2821)
- [Adafruit DS1307](https://www.adafruit.com/product/3296)
- [Adafruit DotStar LED Strip - Addressable Warm White - 30 LED/m - ~3000K - 4 meters](https://www.adafruit.com/product/2435?length=4)
- [4-channel I2C-safe Bi-directional Logic Level Converter - BSS138K](https://www.adafruit.com/product/757)
- [Photo Transistor Light Sensor](https://www.adafruit.com/product/2831)
- [button]()
- [resistor]()
- [5v Power Supply]()
### Hardware

## Running The Clock
### Setup Mode:
<img align="right" width="40%" height="auto" src="https://github.com/ben-esler/WordClock/blob/master/HTML%20Testing/example.jpg">
During setup the user can set the time, add/remove birthdays, and set led brightness.

#### Entering Setup:
Hold down the setup button while plugging in the clock. A new wifi access point named "WordClock Setup" will appear in your devices wifi manager. Connecting to it will bring the user to the clock's setup webpage.

#### Setting Time:
#### Adding/Removing Birthdays:
#### LED Brightness:
#### Exiting Setup:
To exit the setup when one of the below happens:  
- No one connects after 5 minutes
- User clicks End Setup button
- Last user disconnects from Access Point

### Displaying Time
#### Transitions:
#### Birthdays:
