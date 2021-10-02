/*##########################################################################################################
 * 
 *  Link: 
 * 
 * 
 * 
 * 
 * 
 * 
 * ########################################################################################################
 */
// DHT Temperature & Humidity Sensor
// Unified Sensor Library Example
// Written by Tony DiCola for Adafruit Industries
// Released under an MIT license.
// See guide for details on sensor wiring and usage:
//   https://learn.adafruit.com/dht/overview
// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor


#include "Variables.hpp"

#ifndef DHT22_HPP
#define DHT22_HPP

#pragma once

/*
  class DHT22
  {
  public:
    DHT22(); //default-constructor
    void activateDHT22(){};
    void getTemperatureDHT22(){};
    void getHumidityDHT22(){};

    ~DHT22(); //Destruktor

  private:

  };
*/

void activateDHT22();
void getTemperatureDHT22();
void getHumidityDHT22();
void sendTemperature();
void sendHumidity();

#endif
