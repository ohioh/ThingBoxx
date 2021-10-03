/*##########################################################################################################
    SETUP.cpp
    Link:






   ########################################################################################################
*/

#include "Settings.hpp"
#include "Variables.hpp"

#include <Arduino.h>
#include <stdlib.h>
#include <stdint.h>
#include <EEPROM.h>//https://github.com/espressif/arduino-esp32/tree/master/libraries/EEPROM

#include "Battery.hpp"
#include "CJMCU811.hpp"
#include "EEPROM.hpp"
#include "DHT22.hpp"
#include "Display.hpp"
#include "LED.hpp"
#include "LoRaWan.hpp"
#include "Sleep.hpp"
#include "SGP30.hpp"
#include "SETUP.hpp"
#include "Tasks.hpp"


// define the number of bytes you want to access
#define EEPROM_SIZE 25


void runSETUP()
{
  //Initialize
  Serial.begin(115200);
  delay(50);
  chipid = ESP.getEfuseMac(); //The chip ID is essentially its MAC address(length: 6 bytes).

  //set used pins
  setLEDPins();
 
  delay(1000);
  int i;
  uint8_t c, r, d;
  pre();
  u8x8.print("ThinkBoxx");
  u8x8.setCursor(0,2);
  u8x8.print("OHIOH e.V.");
  delay(2000);
  u8x8.setCursor(0,3);
  u8x8.print("Covid-Ampel");
  u8x8.print((int)u8x8.getCols());
  u8x8.print(" protect");
  u8x8.print((int)u8x8.getRows());
  
  delay(2000);
  
  delay(1000);

}
