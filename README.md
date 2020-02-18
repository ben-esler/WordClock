# WordClock
ESP8266 based clock that spells the time with LEDs, using an RTC for time and a captive portal for settings.

## Table of Contents
- [Libraries](#libraries)
- [Physical Build](#physical-build)
  * [Components](#components)
  * [Hardware](#hardware)
- [Setting Up The Clock](#setting-up-the-clock)
- [Displaying Time](#displaying-time)

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
- Wood
- Clear Resin

## Setting Up The Clock
<img align="right" width="40%" height="auto" src="https://github.com/ben-esler/WordClock/blob/master/HTML%20Testing/example.png">
The user can set the time, add/remove birthdays, and LED brightness.

#### Entering Setup:
Hold down the setup button while plugging in the clock. A new wifi access point named "WordClock Setup" will appear in a devices wifi manager. Connecting to it will bring the user to the clock's setup webpage.

#### Setting Time:
Time can be entered to be manually set or synced to the time of the device that is currntly connected to the clock.

#### Adding/Removing Birthdays:
There can be up to 10 birthdays stored on the clock.

#### LED Brightness:
The brightness of the LEDs range from the min/max brightness and are adjusted based off the room's ambient brightness.  
The clock will need to be calibrated for the ambient brightness. 
- When the room is dark press the 'Capture Dim Room'
- When the room is well lit press the 'Capture Bright Room'
- Then set the prefered min/max brightness values

#### Exiting Setup:
The Setup will exit when one of the following happens:  
- No one connects after 5 minutes
- User clicks End Setup button
- Last user disconnects from the Access Point

## Displaying Time
The clock will update the LEDS every 5 minutes to spell out the time.
### Transitions:
### Birthdays:
On birthdays the clock will show "Happy Birthday" everytime it changes time.
