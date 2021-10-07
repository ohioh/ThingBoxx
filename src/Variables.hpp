/*##########################################################################################################
 *  Variables.hpp
 *  Link: 
 * 
 * 
 * 
 * 
 * 
 * 
 * ########################################################################################################
 */
#ifndef VARIABLES_HPP
#define VARIABLES_HPP

#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <cstddef>

extern int RED_PIN;
extern int GREEN_PIN;
extern int BLUE_PIN;
extern int ALERT_PIN;

extern int red_times;
extern int orange_times;
extern int green_times;
extern int blue_times;
extern int alert_times;
extern int white_times;

extern int red_ms;
extern int orange_ms;
extern int green_ms;
extern int blue_ms;
extern int alert_ms;
extern int white_ms;


//EEPROM-Adressen
extern int Battery_Address;
extern int BatteryValue;
extern int CO2_Address;
extern int DEVICE_STATE_ADDRESS;
extern int DEVICE_STATE;
extern int temp;
extern int humidity;
extern int Co2;

//LORAWAN-Variables

// -> void decToBinary(int input):
extern const size_t arraySize ;
extern uint32_t binValue;
extern uint16_t binSensorData;
extern const size_t arraySize ;
extern unsigned int invertedBinaryNum[];
extern unsigned int binaryNum[];

// -> void zennerParserPrepair():
extern uint16_t binPlatformData; //for integer values till to 65535

// -> void prepareTxFrame(uint8_t port):



#endif