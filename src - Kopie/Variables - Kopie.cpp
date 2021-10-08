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

//LED
int RED_PIN = 4;
int GREEN_PIN = 15;
int BLUE_PIN = 32;
int ALERT_PIN = 12 ;

int red_times = 100;
int orange_times = 1;
int green_times = 1;
int blue_times = 1;
int alert_times = 100;
int white_times = 10;

int red_ms = 100;
int orange_ms = 10000;
int green_ms = 10000;
int blue_ms = 1000;
int alert_ms = 100;
int white_ms = 1000;

//EEPROM-Adressen
int Battery_Address = 37;
int BatteryValue = 0;
int CO2_Address = 90;
int DEVICE_STATE_ADDRESS = 25;
int DEVICE_STATE = 0;

// -> void decToBinary(int input):
uint16_t binPlatformData = 0b0000000000000000; //for integer values till to 65535
int averageCO2 = 0;
int averageCO2Store = 0;

// -> void decToBinary(int input):
const size_t arraySize = 16;
unsigned int invertedBinaryNum[arraySize] {0};
unsigned int binaryNum[arraySize] {0};
uint32_t binValue = 0;
uint16_t binSensorData = 0b0000000000000000; //for integer values till to 65535






//////////////////////////////////////////////---SENSOR-VARIABLES---///////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


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
