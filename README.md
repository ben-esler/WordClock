# WordClock
ESP8266 based clock that spells the time with LEDs

## About

## Table of Contents

- [About](#about)
- [Libraries](#libraries)
- [Physical Build](#physical-build)
  * [Physical Build](#physical-build)
- [Usage](#usage)
  * [Setup Mode](#setup-mode)

## Libraries
## Physical Build
### Hardware

## Usage
### Setup Mode
<img align="right" width="40%" height="auto" src="https://github.com/ben-esler/WordClock/blob/master/HTML%20Testing/example.jpg">
Holding >Button name< while the clock turns on, it will enter setup mode. The ESP8266 will have already loaded the configuration from the EEPROM. It then hosts an Access Point named "WordClock Setup" without a password. After connecting to the access point it will prompt the user to sign in, bringing them to a Captive Portal.

Setup mode is ended if any of the below happens:
