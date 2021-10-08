/*##########################################################################################################
    Variables.cpp
    Link:
    1.SENSOR-VARIABLES
    2.COVID-Control -> used from Signals.cpp -> void startSignalController();
    Variables which has to be non-volatily are handled in Storage.cpp
   ########################################################################################################
*/
#include "Variables.hpp"

#include <stdlib.h>
#include <stdint.h>
#include <cstddef>

//////////////////////////////////////////////---LED-VARIABLES---///////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int RED_PIN = 4;
int GREEN_PIN = 15;
int BLUE_PIN = 32;
int ALERT_PIN = 12 ;


/* MODE: Production
int red_times = 200;
int orange_times = 2;
int green_times = 2;
int blue_times = 1;
int alert_times = 100;
int white_times = 10;

int red_ms = 500;
int orange_ms = 500000;
int green_ms = 500000;
int blue_ms = 1000;
int alert_ms = 500000;
int white_ms = 1000;
*/

int red_times = 20;
int orange_times = 2;
int green_times = 2;
int blue_times = 1;
int alert_times = 10;
int white_times = 10;

int red_ms = 500;
int orange_ms = 5000;
int green_ms = 5000;
int blue_ms = 1000;
int alert_ms = 5000;
int white_ms = 1000;


//////////////////////////////////////////////---SENSOR-VARIABLES---///////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//EEPROM-Adressen
int Battery_Address = 37;
int BatteryValue = 95;
uint16_t ADCValue = 0;
int CO2_Address = 90;
int DEVICE_STATE_ADDRESS = 25;
uint16_t DEVICE_STATE = 77;
int temp;
int humidity;
int Co2;

// -> void decToBinary(int input):
uint16_t binPlatformData; //for integer values till to 65535


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
