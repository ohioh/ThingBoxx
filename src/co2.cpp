#include "co2.hpp"
/******************************************************************************
  Read basic CO2 and TVOCs

  Marshall Taylor @ SparkFun Electronics
  Nathan Seidle @ SparkFun Electronics

  April 4, 2017

  https://github.com/sparkfun/CCS811_Air_Quality_Breakout
  https://github.com/sparkfun/SparkFun_CCS811_Arduino_Library
  https://joy-it.net/files/files/Produkte/SEN-CCS811V1/SEN-CCS811V1-Anleitung-2.11.2020.pdf

  Read the TVOC and CO2 values from the SparkFun CSS811 breakout board

  A new sensor requires at 48-burn in. Once burned in a sensor requires
  20 minutes of run in before readings are considered good.

  Hardware Connections (Breakoutboard to Arduino):
  3.3V to 3.3V pin
  GND to GND pin
  SDA to A4
  SCL to A5

******************************************************************************/
#include <Arduino.h>
#include <Adafruit_CCS811.h>
#include "Variables.hpp"


Adafruit_CCS811 ccs;

int count = 1;

int messurmentCo2 = 400;

TaskHandle_t getCo2AverageHandle;
RTC_DATA_ATTR int AverageC02Value = 400;

void setupCO2()
{

  Serial.print("Messurment done: ");
  Serial.println(messurmentDone);

  //Start CCS811:
  Serial.println("CCS811 starting...");

  //TODO : Not working to set the Drive Mode
  //ccs.setDriveMode(1);
  if (!ccs.begin())
  {
    Serial.println("Failed to start CCS811 sensor! Please check wiring.");
  }
  else
  {
    /**************************************************************************/
    /*!
        (es werden keine Messungen durchgeführt)
        Modus 1 IAQ Messung jede Sekunde
        Modus 2 IAQ Messung alle 10 Sekunden
        Modus 3 IAQ Messung alle 60 Sekunden
        Modus 4 IAQ Messung alle 250 ms
        (es wird nicht eCO2 und TVOC berechnet)
    */
    /**************************************************************************/
    Serial.println("CCS811 started");
  }
}

void getCO2Average(void *pvParameters)
{
  for (;;)    {
    Serial.print("getCO2Average-Task runs on Core: ");
    Serial.print(xPortGetCoreID());
    Serial.print(" with  ");
    if (ccs.available()) {
      if (!ccs.readData()) {
        Serial.print(" CO2: ");
        AverageC02Value = ((AverageC02Value + ccs.geteCO2())/2);
        Serial.print(AverageC02Value);
        Serial.print(" ppm, TVOC: ");
        Serial.println(ccs.getTVOC());
      }
      else {
        Serial.println("ERROR!");
        while (1);
      }
    }
    yield();
    delay (1000);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void loopCO2()
{
  xTaskCreatePinnedToCore(
    getCO2Average,        // Function that should be called
    "getCO2 Average",     // Name of the task (for debugging)
    100000,                // Stack size (bytes)
    NULL,                 // Parameter to pass
    1,                    // Task priority
    &getCo2AverageHandle, // Task handle
    1);                   //CORE

}
