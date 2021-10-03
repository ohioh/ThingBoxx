/*=========================================================================
    SSD1306 Displays
    -----------------------------------------------------------------------
    The driver is used in multiple displays (128x64, 128x32, etc.).
    Select the appropriate display below to create an appropriately
    sized framebuffer, etc.

    Supply Current: 

    SSD1306_128_64  128x64 pixel display

  # 0,96 Zoll I2C OLED Display 3,3 Volt
  # https://github.com/olikraus/u8g2
  # https://www.best-microcontroller-projects.com/ssd1306.html
  # 
  # Needed Libraries:
  # Adafruit GFX, Adafruit SSD1306, u8g,SSD1306Ascii 
  # https://funduino.de/nr-42-oled-display-ssd1306-128x64-128x32
  # https://learn.adafruit.com/adafruit-gfx-graphics-library?view=all
  # -----------------------------------------------------------------------*/
//
//   #define SSD1306_128_32
//   #define SSD1306_96_16
/*=========================================================================*/

#include <Arduino.h>
#include <stdlib.h>
#include <stdint.h>
#include <string>

//Display
#include "EEPROM.hpp"
#include "Variables.hpp"
#include "Display.hpp"
#include <U8x8lib.h>

#define SSD1306_128_64
/*
//#include <U8x8lib.h>
//#ifdef U8X8_HAVE_HW_S
//#include <SPI.h>
//#endif

#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
*/
//U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // OLEDs without Reset of the Display
// End of constructor list

#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"

#define I2C_ADDRESS 0x3C

SSD1306AsciiWire oled;

void setupDISPLAY()
{
  Wire.begin();
  Wire.setClock(400000L);
  oled.begin(&Adafruit128x64, I2C_ADDRESS);
}

void loopDISPLAY()
{
  oled.setFont(System5x7); // Auswahl der Schriftart
  oled.clear();            //Löschen der aktuellen Displayanzeige
  oled.println("Viel");    //Text in der ersten Zeile. "Println" sorgt dabei für einen Zeilensprung.
  oled.print("Erfolg!!!"); // Text in der zweiten Zeile. Da es keine dritte Zeile gibt, wird hier kein Zeilenumsprung benötigt.
  delay(2000);
}
