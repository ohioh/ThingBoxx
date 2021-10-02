/*##########################################################################################################
    CJMCU811.cpp
    Link: printing results of the CCS811 digital gas sensor for monitoring indoor air quality from ams.






   ########################################################################################################
*/
#include <Arduino.h>
#include "Variables.hpp"
#include "LED.hpp"
#include "Tasks.hpp"
#include "Display.hpp"
#include "EEPROM.hpp"
#include <Wire.h>    // I2C library
#include <ccs811.h>  // CCS811 library


#include "CJMCU811.hpp"

CCS811 ccs811(23); // nWAKE on 23

TaskHandle_t readCO2Task;

int Reading4TaskCO2;
int counter = 30;
uint16_t eco2, etvoc, errstat, raw;



void codeReadCO2Task( void * parameter )
{
  for (;;) {
    averageCO2 = 400;
    
    Serial.println("ReadCO2Task on Core: ");
    Serial.println(xPortGetCoreID());
    
    for (int i = 0; i <= counter; i++) {
      ccs811.read(&eco2, &etvoc, &errstat, &raw);
      averageCO2 = ((averageCO2 + eco2) / 2);
      Serial.println("CO2 Average Counter:");
      Serial.println(counter);
      counter --;
      delay(2000);
    }
    
    // Read
    Serial.println("Messurment CO2 result:");
    Serial.println(averageCO2);
    writeCO2State(CO2_Address, averageCO2);
    // Switch Mode and give Signal
    
 
    // Print measurement results based on status
    if ( errstat == CCS811_ERRSTAT_OK ) {
      Serial.print("CCS811: ");
      Serial.print("eco2=");  Serial.print(eco2);     Serial.print(" ppm  ");
      Serial.print("etvoc="); Serial.print(etvoc);    Serial.print(" ppb  ");
      //Serial.print("raw6=");  Serial.print(raw/1024); Serial.print(" uA  ");
      //Serial.print("raw10="); Serial.print(raw%1024); Serial.print(" ADC  ");
      //Serial.print("R="); Serial.print((1650*1000L/1023)*(raw%1024)/(raw/1024)); Serial.print(" ohm");
      Serial.println();
    } else if ( errstat == CCS811_ERRSTAT_OK_NODATA ) {
      Serial.println("CCS811: waiting for (new) data");
    } else if ( errstat & CCS811_ERRSTAT_I2CFAIL ) {
      Serial.println("CCS811: I2C error");
    } else {
      Serial.print("CCS811: errstat="); Serial.print(errstat, HEX);
      Serial.print("="); Serial.println( ccs811.errstat_str(errstat) );
    }

    // Wait
    delay(100);
    vTaskDelete(readCO2Task);
  }
}


void getCJMCU811() {

  xTaskCreatePinnedToCore(
    codeReadCO2Task,           /*Task Function. */
    "get CO2 messurment data",               /*name of task. */
    100000,                   /*Stack size of task. */
    NULL,                   /* parameter of the task. */
    1,                      /* proiority of the task. */
    &readCO2Task,                 /* Task handel to keep tra ck of created task. */
    0);                     /* choose Core */

}


void activateCJMCU811() {
  ///////////////--Initialize CO2 Sensor--//////////////////
  Serial.println("");
  Serial.println("setup: Starting CCS811 envirnment");
  Serial.print("setup: ccs811 lib  version: "); Serial.println(CCS811_VERSION);

  // Enable I2C
  Wire.begin();

  // Enable CCS811
  ccs811.set_i2cdelay(50); // Needed for ESP8266 because it doesn't handle I2C clock stretch correctly
  bool ok = ccs811.begin();
  if ( !ok ) Serial.println("setup: CCS811 begin FAILED");

  // Print CCS811 versions
  Serial.print("setup: hardware    version: "); Serial.println(ccs811.hardware_version(), HEX);
  Serial.print("setup: bootloader  version: "); Serial.println(ccs811.bootloader_version(), HEX);
  Serial.print("setup: application version: "); Serial.println(ccs811.application_version(), HEX);

  // Start measuring
  ok = ccs811.start(CCS811_MODE_1SEC);
  if ( !ok ) Serial.println("setup: CCS811 start FAILED");
}
