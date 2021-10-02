/*
  ###################################################################################################################################
  # 0,96 Zoll I2C OLED Display 3,3 Volt
  # https://github.com/olikraus/u8g2
  #
  #
  ###################################################################################################################################
*/
#include "Variables.hpp"
#include "Display.hpp"

//Display
#include <Arduino.h>
#include "EEPROM.hpp"
#include <string>

//
//#include <stdlib.h>
//#include <stdint.h>
//#include <U8x8lib.h>
//#ifdef U8X8_HAVE_HW_SPI
//#include <SPI.h>
//#endif

//U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // OLEDs without Reset of the Display
// End of constructor list


using namespace std;
int displayTimeGate;
int stateGate;
////////////////////////////////////////////////////---CONNECT DISPLAY---////////////////////////////////////////////////////////////
//  Variables:
//              transmitTyp 1: OHIOH-Logo
//              transmitTyp 2: temperature
//              transmitTyp 3: humidity 
//              transmitTyp 4: CO2
//              transmitTyp 5:
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////---printBatteryStateTask---/////////////////////////////////////////////////////////////
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
