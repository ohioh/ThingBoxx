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


//EEPROM-Adressen
extern int Battery_Address;
extern int BatteryValue;
extern int CO2_Address;
extern int DEVICE_STATE_ADDRESS;
extern int DEVICE_STATE;

extern int BatteryStatus;
extern int acutalMessurment;
extern uint16_t binPlatformData; //for integer values till to 65535
extern int averageCO2;
extern int averageCO2Store;
extern int globaleVariable; // deklaration
extern int RED_PIN;
extern int GREEN_PIN;
extern int BLUE_PIN;
extern int ALERT_PIN;
extern int Battery_Address;
extern uint16_t ms;
extern int MEASURMENT_BRAKE;
extern bool needMessurment;
extern bool needREBOOT;

//////////////////////////////////////////////---SENSOR-VARIABLES---///////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern int gTEMPERATURE;
extern uint8_t gBinTEMPERATURE;

extern int gHUMIDITY;
extern uint8_t gBinHUMIDITY;

extern int gCO2;
extern int averageCO2;
extern uint8_t gBinCO2;

extern int gVOC;
extern int averageVOC;
extern uint8_t gBinVOC;


extern const size_t arraySize ;
extern unsigned int invertedBinaryNum[];
extern unsigned int binaryNum[];
extern uint32_t binValue;
extern uint16_t binSensorData;

//Hardware status and device communication
extern unsigned int hardwareState;
extern uint16_t binaryHardwareStatus;

// Battery-Power
//extern unsigned int batteryStatus;
extern uint16_t binaryBatteryStatus;

extern unsigned int sensorDataTemperature;
extern uint16_t binaryTemperature;

extern int sensorDataHumidity;
extern uint16_t binaryHumidity;

extern unsigned int sensorDataVOC;
extern uint16_t binaryVOC;

extern unsigned int sensorDataCO2;
extern uint16_t binaryCO2;


//////////////////////////////////////////////---COVID-Control---///////////////////////////////////////////////////////////////////
// Values used for Logic Controll of LED and Send-Decission
extern bool needCheck;

extern int gTEMPERATURETrigger_highLevel;
extern int gTEMPERATURETrigger_riskLevel;
extern int gTEMPERATURETrigger_dangerLevel;
extern int  alertTriggerHum;
extern uint16_t gCO2Trigger_highLevel;
extern uint16_t gCO2Trigger_riskLevel;
extern uint16_t gCO2Trigger_dangerLevel;


#endif
