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
#include "EEPROM.hpp"
#include "SETUP.hpp"
#include "LED.hpp"
#include "DHT22.hpp"
//#include "Display.hpp"
#include "LoRaWan.hpp"
#include "Sleep.hpp"
#include "SGP30.hpp"
#include "Tasks.hpp"
#include "Battery.hpp"
#include "CJMCU811.hpp"
#include <EEPROM.h>//https://github.com/espressif/arduino-esp32/tree/master/libraries/EEPROM

// define the number of bytes you want to access
#define EEPROM_SIZE 25


#include <stdlib.h>
#include <stdint.h>

#include <U8x8lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // OLEDs without Reset of the Display



void pre(void)
{
  u8x8.setFont(u8x8_font_amstrad_cpc_extended_f);    
  u8x8.clear();

  u8x8.inverse();
  u8x8.print(" U8x8 Library ");
  u8x8.setFont(u8x8_font_chroma48medium8_r);  
  u8x8.noInverse();
  u8x8.setCursor(0,1);
}

void draw_bar(uint8_t c, uint8_t is_inverse)
{  
  uint8_t r;
  u8x8.setInverseFont(is_inverse);
  for( r = 0; r < u8x8.getRows(); r++ )
  {
    u8x8.setCursor(c, r);
    u8x8.print(" ");
  }
}

void draw_ascii_row(uint8_t r, int start)
{
  int a;
  uint8_t c;
  for( c = 0; c < u8x8.getCols(); c++ )
  {
    u8x8.setCursor(c,r);
    a = start + c;
    if ( a <= 255 )
      u8x8.write(a);
  }
}


void runSETUP()
{
  //Initialize
  Serial.begin(115200);
  delay(50);
  chipid = ESP.getEfuseMac(); //The chip ID is essentially its MAC address(length: 6 bytes).

  u8x8.begin();

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
