/*##########################################################################################################
    Variables.cpp
    Link:

    1.SENSOR-VARIABLES
    2.COVID-Control -> used from Signals.cpp -> void startSignalController();



   ########################################################################################################
*/
#include "Variables.hpp"

#include <stdlib.h>
#include <stdint.h>
#include <stdexcept>
#include <Wire.h>
#include <bitset>
#include <cassert>
#include <string>


//EEPROM-Adressen
int Battery_Address = 37;
int BatteryValue = 0;
int CO2_Address = 90;
int DEVICE_STATE_ADDRESS = 25;
int DEVICE_STATE = 0;


int BatteryStatus;
int acutalMessurment;

uint16_t binPlatformData = 0b0000000000000000; //for integer values till to 65535
int averageCO2 = 0;
int averageCO2Store = 0;

int globaleVariable = 42; // definition
int RED_PIN = 32;
int GREEN_PIN = 15;
int BLUE_PIN = 12;
int ALERT_PIN = 4;

uint16_t ms = 500;
int MEASURMENT_BRAKE = 500;
bool needMessurment = true;
bool needREBOOT = false;

//////////////////////////////////////////////---SENSOR-VARIABLES---///////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int gTEMPERATURE = 25;
uint8_t gBinTEMPERATURE = 0;

int gHUMIDITY = 65;
uint8_t gBinHUMIDITY;

int gCO2 = 600;
uint8_t gBinCO2;

int gVOC = 0;
int averageVOC;
uint8_t gBinVOC = 0;


const size_t arraySize = 16;
unsigned int invertedBinaryNum[arraySize] {0};
unsigned int binaryNum[arraySize] {0};

uint32_t binValue = 0;
uint16_t binSensorData = 0b0000000000000000; //for integer values till to 65535

//Hardware status and device communication
unsigned int hardwareState = 0;
uint16_t binaryHardwareStatus = 0b1100110011001100; //52428 and CCCC

// Battery-Power
//unsigned int batteryStatus = 95;
uint16_t binaryBatteryStatus = 0b1100110011001100; //52428 and CCCC

unsigned int sensorDataTemperature = 0;
uint16_t binaryTemperature = 0b0000000000000000; //0 and CCCC

int sensorDataHumidity = 0;
uint16_t binaryHumidity = 0b0000000000000000; //0 and CCCC

unsigned int sensorDataVOC = 0;
uint16_t binaryVOC = 0b1100110011001100; //52428 and CCCC

unsigned int sensorDataCO2 = 0;
uint16_t binaryCO2 = 0b1100110011001100; //52428 and CCCC


//////////////////////////////////////////////---COVID-Control---///////////////////////////////////////////////////////////////////
// Values used for Logic Controll of LED and Send-Decission
bool needCheck = false;

int gTEMPERATURETrigger_highLevel = 28;
int gTEMPERATURETrigger_riskLevel  = 30;
int gTEMPERATURETrigger_dangerLevel = 32;

int  alertTriggerHum = 90;
uint16_t gCO2Trigger_highLevel = 700;
uint16_t gCO2Trigger_riskLevel = 800;
uint16_t gCO2Trigger_dangerLevel = 1000;
