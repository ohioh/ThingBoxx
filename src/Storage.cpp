//########################################################################################################
//  Storage.cpp
//  
//
//########################################################################################################

#include <Arduino.h>
#include "Storage.hpp"
#include "Variables.hpp"
#include "LED1.hpp"

//########################################################################################################
//  non-volatily storage for Deep-Sleep Mode
//  
//
//########################################################################################################
RTC_DATA_ATTR int Temp = 0;
RTC_DATA_ATTR int BootCounter = 0;



//########################################################################################################
//  Storage for ultra non volatily-storage ( WARNING: EEPROM has a  write maximum of 100k !!!)
//  
//########################################################################################################
// include library to read and write from flash memory
#include <EEPROM.h> //https://github.com/espressif/arduino-esp32/tree/master/libraries/EEPROM

// define the number of bytes you want to access
#define EEPROM_SIZE 4


//########################################################################################################
// 
//  
//########################################################################################################
int read_int(int address) {  
  delay(500);
  int value = EEPROM.read(address);
  Serial.println("[EEPROM]: read Value");
  Serial.println(value);
  Serial.println("-------------------------");
  delay(500);
  //EEPROM.end();
  
  return value;
}


void write_int(int address, int state) {
  Serial.println("[EEPROM]: write Device State");
  //EEPROM.begin(EEPROM_SIZE);
  delay(500);
  EEPROM.write(address, byte(state));
  EEPROM.commit();
  delay(500);
  //EEPROM.end(); 
}


//########################################################################################################
// 
//  
//########################################################################################################
void writeBatteryState(int BatteryAddress, int state) {
  BatteryValue = state;
  Serial.println("[EEPROM]: write Battery State");
  //EEPROM.begin(EEPROM_SIZE);
  delay(500);
  EEPROM.write(BatteryAddress, BatteryValue);
  EEPROM.commit();
  delay(500);
  //EEPROM.end();
  
}

int readBatteryState(int BatteryAddress) {  
  delay(500);
  byte value = EEPROM.read(BatteryAddress);
  Serial.println("[EEPROM]: read Battery State");
  Serial.println(value);
  Serial.println("-------------------------");
  delay(500);
  //EEPROM.end();
  
  return value;
}


//########################################################################################################
// 
//  
//########################################################################################################
void writeCO2State(int CO2Address, int state) {
  int byteValue = state;
  Serial.println("[EEPROM]: write CO2 State");
  //EEPROM.begin(EEPROM_SIZE);
  delay(500);
  EEPROM.write(CO2Address, byteValue);
  EEPROM.commit();
  delay(500);
  //EEPROM.end();
  
}

int readCO2State(int CO2Address) {  
  delay(500);
  byte value = EEPROM.read(CO2Address);
  Serial.println("[EEPROM]: read CO2 State");
  Serial.println(value);
  Serial.println("-------------------------");
  delay(500);
  //EEPROM.end();
  
  return value;
}
