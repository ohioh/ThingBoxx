#include "co2.hpp"
/******************************************************************************
  Read basic CO2 and TVOCs

  Marshall Taylor @ SparkFun Electronics
  Nathan Seidle @ SparkFun Electronics

  April 4, 2017

  https://github.com/sparkfun/CCS811_Air_Quality_Breakout
  https://github.com/sparkfun/SparkFun_CCS811_Arduino_Library

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
#include <Wire.h>

#include "SparkFunCCS811.h" //Click here to get the library: http://librarymanager/All#SparkFun_CCS811

#define CCS811_ADDR 0x5A //Default I2C Address
//#define CCS811_ADDR 0x5A //Alternate I2C Address

CCS811 mySensor(CCS811_ADDR);


void setupCO2()
{

  Serial.println("CCS811 Basic Example");

  //Wire.begin(); //Inialize I2C Hardware

  if (mySensor.begin() == false)
  {
    Serial.print("CCS811 error. Please check wiring. Freezing...");
    while (1)
      ;
  }
  Serial.println("CCS811 SETUP done");
}

int loopCO2()
{
  Serial.println("CCS811 LOOP");
  int co2 = 0;
  //setupCO2();
  delay(1000);
  //Check to see if data is ready with .dataAvailable()
  if (mySensor.dataAvailable())
  {
    //If so, have the sensor read and calculate the results.
    //Get them later
    mySensor.readAlgorithmResults();

    Serial.print("CO2[");
    //Returns calculated CO2 reading
    for ( int i = 0; i <= 60; i++) {
      if ( i >= 30 ) {
        Serial.println("Start Messurment");
        co2 = (co2 + mySensor.getCO2()) / 2;
        Serial.println(co2);
        delay(1000);
      } else {
        Serial.println(mySensor.getCO2());
        delay(1000);
      }

    }
    Serial.print(mySensor.getCO2());
    Serial.print("] tVOC[");
    //Returns calculated TVOC reading
    Serial.print(mySensor.getTVOC());
    Serial.print("] millis[");
    //Display the time since program start
    Serial.print(millis());
    Serial.print("]");
    Serial.println();
  } else {
    Serial.println("CO2 not avaible");
  }

  delay(100); //Don't spam the I2C bus
  return (co2);
}