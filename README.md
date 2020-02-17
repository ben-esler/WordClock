# WordClock
ESP8266 based clock that spells the time with LEDs

## About

## Table of Contents

- [About](#about)
- [Libraries](#libraries)
- [Physical Build](#physical-build)
  * [Components](#components)
  * [Hardware](#hardware)
- [Usage](#usage)
  * [Setup Mode](#setup-mode)

## Libraries
## Physical Build
### Componenets
- [Adafruit Feather HUZZAH with ESP8266](https://www.adafruit.com/product/2821)
- [Adafruit DS1307](https://www.adafruit.com/product/3296)
- [Adafruit DotStar LED Strip - Addressable Warm White - 30 LED/m - ~3000K](https://www.adafruit.com/product/2435?length=4)
- [4-channel I2C-safe Bi-directional Logic Level Converter - BSS138K](https://www.adafruit.com/product/757)
- [5v Power Supply]()
### Hardware

## Usage
### Setup Mode
<img align="right" width="40%" height="auto" src="https://github.com/ben-esler/WordClock/blob/master/HTML%20Testing/example.jpg">
Holding >Button name< while the clock turns on, it will enter setup mode. The ESP8266 will have already loaded the configuration from the EEPROM. It then hosts an Access Point named "WordClock Setup" without a password. After connecting to the access point it will prompt the user to sign in, bringing them to a Captive Portal.

Setup mode is ended if any of the below happens:
