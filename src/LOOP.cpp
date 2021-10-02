/*##########################################################################################################
    LOOP.cpp
    Link:






   ########################################################################################################
*/
#include "LOOP.hpp"
#include "Variables.hpp"
#include "Settings.hpp"

#include <ESP32_LoRaWAN.h>
#include <Wire.h>
#include <EEPROM.h>

#include <stdlib.h>
#include <stdint.h>

#include "DHT22.hpp"
#include "Display.hpp"
#include "LoRaWan.hpp"
#include "LED.hpp"
#include "SGP30.hpp"
#include "Sleep.hpp"
#include "Signals.hpp"
#include "SETUP.hpp"
#include "REBOOT.hpp"
#include "Tasks.hpp"
#include "EEPROM.hpp"
#include "Battery.hpp"
#include "CJMCU811.hpp"



//U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // OLEDs without Reset of the Display

byte Value1 = acutalMessurment;

///////////////////////////////////////////---Definition---///////////////////////////////////////////////////////////////////



void runLOOP() {
 


  delay(1000);
  delay(50);
  blinkBLUE(3, 150);
  delay(5000);
  blinkORANGE(3, 5000);
  delay(5000);
  blinkRED(20, 1000);
  blinkALERT(20, 1000);
  delay(5000);


  ESP.restart();


}
