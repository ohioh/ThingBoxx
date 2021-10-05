#include <heltec.h>
#include <Arduino.h>
#include <stdlib.h>
//#include <ESP32_LoRaWAN.h>
#include "Adafruit_CCS811.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "LOOP.hpp"
#include "SETUP.hpp"
#include "Variables.hpp"
#include "LED.hpp"
#include "DHT22.hpp"

#define SCREEN_WIDTH 128    // OLED display width, in pixels
#define SCREEN_HEIGHT 64    // OLED display height, in pixels
#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Adafruit_CCS811 ccs;


//Work Variables
int count = 0;
int temp = 0;
int humidity = 0;
int Co2 = 0;

void setup()
{
  Serial.begin(115200);
  setupDHT22();
  setLEDPins();
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
  display.setCursor(15, 15);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.println("CO2-AMPEL");
  display.setCursor(25, 35);
  display.setTextSize(1);
  display.print("Initializing...");
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
  temp = loopTemperature() ;
  humidity = loopHumidity();
  if (ccs.available())
  {
    if (count == 1) {
      Serial.println("Set new Baseline [1]");
      uint16_t Baseline = ccs.getBaseline();
      ccs.setBaseline(Baseline);

    } else if (count == 60) {
      Serial.println("Set new Baseline [60]");
      uint16_t Baseline = ccs.getBaseline();
      ccs.setBaseline(Baseline);
      count = 0;
    }
    count++;

    ccs.setEnvironmentalData(humidity, temp);
    if (!ccs.readData())
    {

      // ---------------------------
      display.clearDisplay();

      display.setTextSize(1);
      display.setCursor(0, 0);
      display.print("Temperatur");

      display.setTextSize(5);
      display.setCursor(20, 20);
      display.print(temp);

      display.setTextSize(5);
      display.setCursor(87, 20);
      display.print("C");
      display.display();
      delay(2000);

      // ---------------------------
      display.clearDisplay();

      display.setTextSize(1);
      display.setCursor(0, 0);
      display.print("Luftfeuchtigkeit");

      display.setTextSize(5);
      display.setCursor(20, 20);
      display.print(humidity);

      display.setTextSize(5);
      display.setCursor(85, 20);
      display.print("%");
      display.display();
      delay(2000);
       
      // ---------------------------
      Serial.print("CO2: ");
      Co2 = ccs.geteCO2();
      Serial.print(Co2);
      Serial.print("ppm, TVOC: ");
      Serial.println(ccs.getTVOC());

      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(0, 0);
      display.print("CO2:");

      display.setTextSize(5);
      display.setCursor(5, 20);
      display.print(Co2);

      display.setTextSize(1);
      display.setCursor(110, 57);
      display.print("PPM");

      display.display();
      delay(2000);
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
  Serial.println("Set LEDS");
  mainCO22Signal(Co2);
  delay(1000);
}