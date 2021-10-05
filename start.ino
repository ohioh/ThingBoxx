#include <heltec.h>
#include <Arduino.h>
#include <stdlib.h>
//#include <ESP32_LoRaWAN.h>
#include "Adafruit_CCS811.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "loop.hpp"
#include "setup.hpp"
//#include "display.hpp"
#include "dht22.hpp"
//#include "co2.hpp"

#define SCREEN_WIDTH 128    // OLED display width, in pixels
#define SCREEN_HEIGHT 64    // OLED display height, in pixels
#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Adafruit_CCS811 ccs;



void setup()
{
  Serial.begin(115200);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //initialize with the I2C addr 0x3C (128x64)
  delay(500);
  display.clearDisplay();
  display.setCursor(2, 5);
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.println("Thing");
  display.setCursor(55, 35);
  display.setTextSize(3);
  display.print("BOXX");
  display.display();
  delay(5000);

  display.clearDisplay();
  display.setCursor(25, 15);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("CO2 Ampel");
  display.setCursor(25, 35);
  display.setTextSize(1);
  display.print("Initializing");
  display.display();
  delay(1000);
  Serial.println("CCS811 starting...");

  if (!ccs.begin())
  {
    Serial.println("Failed to start CCS811 sensor! Please check wiring.");
    while (1);
  }

  // Wait for the sensor to be ready
  while (!ccs.available());
}

void loop()
{
  if (ccs.available())
  {
    if (!ccs.readData())
    {
      Serial.print("CO2: ");
      Serial.print(ccs.geteCO2());
      Serial.print("ppm, TVOC: ");
      Serial.println(ccs.getTVOC());

      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(0, 0);
      display.print("CO2:");

      display.setTextSize(5);
      display.setCursor(5, 20);
      display.print(ccs.geteCO2());

      display.setTextSize(1);
      display.setCursor(110, 57);
      display.print("PPM");


      /*display.setTextSize(2);
        display.setCursor(0, 45);
        display.print("TVOC:");
        display.print(ccs.getTVOC());

      */
      display.display();
    }
    else
    {
      Serial.println("ERROR!");
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(0, 5);
      display.print("ERROR!");
      while (1);
    }
  }
  delay(1000);
}

