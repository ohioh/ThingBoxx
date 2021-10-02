/*##########################################################################################################
    Battery.cpp
    Link: https://github.com/HelTecAutomation/Heltec_ESP32/blob/master/examples/ESP32/ADC_Read_Voltage/Battery_power/Battery_power.ino
    Link: https://github.com/HelTecAutomation/Heltec_ESP32/blob/master/examples/ESP32/VextControl/VextControl.ino





   ########################################################################################################
*/
#include "Battery.hpp"
#include "Variables.hpp"
#include "Display.hpp"
#include "EEPROM.hpp"
#include <Arduino.h>
#include <Wire.h>
#include <cstddef>

TaskHandle_t readVoltageTask;

int Reading4Task;
int PowerPinTask;

void codeReadVoltageTask( void * parameter )
{
  for (;;) {
    Serial.print("ReadVoltageTask on Core: ");
    Serial.println(xPortGetCoreID());
    Reading4Task = analogRead(PowerPinTask); // Reference voltage is 3v3 so maximum reading is 3v3 = 4095 in range 0 to 4095
    writeBatteryState(Battery_Address, Reading4Task);
    delay(1000);
    vTaskDelete(readVoltageTask);
  }
}

int ReadVoltage(int PowerPin) {
  
  PowerPinTask = PowerPin;
  xTaskCreatePinnedToCore(
    codeReadVoltageTask,           /*Task Function. */
    "WriteVoltage2PPROM",               /*name of task. */
    10000,                   /*Stack size of task. */
    NULL,                   /* parameter of the task. */
    2,                      /* proiority of the task. */
    &readVoltageTask,                 /* Task handel to keep tra ck of created task. */
    1);                     /* choose Core */

  //return 0;
  // return -0.000000000009824 * pow(reading,3) + 0.000000016557283 * pow(reading,2) + 0.000854596860691 * reading + 0.065440348345433;
  //return -0.000000000000016 * pow(reading,4) + 0.000000000118171 * pow(reading,3)- 0.000000301211691 * pow(reading,2)+ 0.001109019271794 * reading + 0.034143524634089;
  return Reading4Task;
} // Added an improved polynomial, use either, comment out as required

//See more APIs about ADC here: https://github.com/Heltec-Aaron-Lee/WiFi_Kit_series/blob/master/esp32/cores/esp32/esp32-hal-adc.h

/* ADC readings v voltage
    y = -0.000000000009824x3 + 0.000000016557283x2 + 0.000854596860691x + 0.065440348345433
  // Polynomial curve match, based on raw data thus:
     464     0.5
    1088     1.0
    1707     1.5
    2331     2.0
    2951     2.5
    3775     3.0
    4095     3.7
*/
