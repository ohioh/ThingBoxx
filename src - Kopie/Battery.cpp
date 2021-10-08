/**
   ##########################################################################################################
    Battery.cpp
    Link: https://github.com/HelTecAutomation/Heltec_ESP32/blob/master/examples/ESP32/ADC_Read_Voltage/Battery_power/Battery_power.ino
    Link: https://github.com/HelTecAutomation/Heltec_ESP32/blob/master/examples/ESP32/VextControl/VextControl.ino

    ADC readings v voltage
    y = -0.000000000009824x3 + 0.000000016557283x2 + 0.000854596860691x + 0.065440348345433
    // Polynomial curve match, based on raw data thus:
     464     0.5
    1088     1.0
    1707     1.5
    2331     2.0
    2951     2.6 (Limit before shut down)
    3000     2.7 0
    3200     2.8 5
    3500     2.9 10
    3775     3.0 15
    3830     3.1 20
    3884     3.2 40
    3938     3.3 60
    3992     3.4 80
    4046     3.5 90
    4047     3.6 100
    4095     3.7 ( and 4.2 voltage stabel )
    //See more APIs about ADC here: https://github.com/Heltec-Aaron-Lee/WiFi_Kit_series/blob/master/esp32/cores/esp32/esp32-hal-adc.h
   ########################################################################################################
*/

#include <Arduino.h>
#include "Battery.hpp"
#include "Variables.hpp"
#include "Display.hpp"
#include "Storage.hpp"
//#include "heltec.h"

#include <cstddef>

TaskHandle_t readVoltageTask;

#define Fbattery 3700 //The default battery is 3700mv when the battery is fully charged.

float XS = 0.0025; //The returned reading is multiplied by this XS to get the battery voltage.
uint16_t MUL = 1000;
uint16_t MMUL = 100;

int Reading4Task;

int PowerPinTask;

void convertBatteryStatus() {
    if( ADCValue <= 3199){
      BatteryValue = 0;
    } else if (ADCValue >= 3200 && ADCValue <= 3499 ){
      BatteryValue = 5;
    } else if (ADCValue >= 3500 && ADCValue <= 3774 ){
      BatteryValue = 10;
    } else if (ADCValue >= 3775 && ADCValue <= 3830 ){
      BatteryValue = 15;
    } else if (ADCValue >= 3831 && ADCValue <= 3883 ){
      BatteryValue = 20;
    }else if (ADCValue >= 3884 && ADCValue <= 3937 ){
      BatteryValue = 40;
    }else if (ADCValue >= 3938 && ADCValue <= 3991 ){
      BatteryValue = 60;
    }else if (ADCValue >= 3992 && ADCValue <= 4045 ){
      BatteryValue = 80;
    }else if (ADCValue >= 4046 && ADCValue <= 4046 ){
      BatteryValue = 90;
    }else if (ADCValue >= 4047 && ADCValue <= 4093 ){
      BatteryValue = 100;
    }else if (ADCValue >= 4094  ){
      BatteryValue = 111;
    }
   Serial.printf("Battery-Status:");
   Serial.println(BatteryValue);
   Serial.println("------------------");
}

void setADC()
{
  //analogSetClockDiv(255); // 1338mS
  analogSetCycles(8);                    // Set number of cycles per sample, default is 8 and provides an optimal result, range is 1 - 255
  analogSetSamples(1);                   // Set number of samples in the range, default is 1, it has an effect on sensitivity has been multiplied
  analogSetClockDiv(1);                  // Set the divider for the ADC clock, default is 1, range is 1 - 255
  analogSetAttenuation(ADC_11db);        // Sets the input attenuation for ALL ADC inputs, default is ADC_11db, range is ADC_0db, ADC_2_5db, ADC_6db, ADC_11db
  analogSetPinAttenuation(36, ADC_11db); // Sets the input attenuation, default is ADC_11db, range is ADC_0db, ADC_2_5db, ADC_6db, ADC_11db
  analogSetPinAttenuation(37, ADC_11db);
  // ADC_0db provides no attenuation so IN/OUT = 1 / 1 an input of 3 volts remains at 3 volts before ADC measurement
  // ADC_2_5db provides an attenuation so that IN/OUT = 1 / 1.34 an input of 3 volts is reduced to 2.238 volts before ADC measurement
  // ADC_6db provides an attenuation so that IN/OUT = 1 / 2 an input of 3 volts is reduced to 1.500 volts before ADC measurement
  // ADC_11db provides an attenuation so that IN/OUT = 1 / 3.6 an input of 3 volts is reduced to 0.833 volts before ADC measurement
  //   adcAttachPin(VP);                     // Attach a pin to ADC (also clears any other analog mode that could be on), returns TRUE/FALSE result
  //   adcStart(VP);                         // Starts an ADC conversion on attached pin's bus
  //   adcBusy(VP);                          // Check if conversion on the pin's ADC bus is currently running, returns TRUE/FALSE result
  //   adcEnd(VP);

  adcAttachPin(36);
  adcAttachPin(37);
}

void readADC()
{
  adcStart(37);
  while (adcBusy(37));
  Serial.printf("Battery power in GPIO 37: ");
  ADCValue = analogRead(37);
  Serial.println();
  uint16_t c1 = int(analogRead(37)) * XS * MUL;  
  convertBatteryStatus();
  adcEnd(37);

  delay(100);

  adcStart(36);
  while (adcBusy(36));
  Serial.printf("voltage input on GPIO 36: ");
  Serial.println(analogRead(36));
  uint16_t c2 = analogRead(36) * 0.769 + 150;
  ADCValue = c2;
  Serial.printf("voltage: ");
  Serial.println(ADCValue);
  adcEnd(36);
  Serial.println("-------------");
}

void codeReadVoltageTask(void *parameter)
{
  for (;;)
  {
    Serial.print("ReadVoltageTask on Core: ");
    Serial.println(xPortGetCoreID());
    Reading4Task = analogRead(PowerPinTask); // Reference voltage is 3v3 so maximum reading is 3v3 = 4095 in range 0 to 4095
    writeBatteryState(Battery_Address, Reading4Task);
    Serial.print("Battery-Status");
    Serial.println(Reading4Task);
    delay(1000);
    vTaskDelete(readVoltageTask);
  }
}

int ReadVoltage(int PowerPin)
{

  PowerPinTask = PowerPin;

  xTaskCreatePinnedToCore(
    codeReadVoltageTask,  /*Task Function. */
    "WriteVoltage2PPROM", /*name of task. */
    10000,                /*Stack size of task. */
    NULL,                 /* parameter of the task. */
    2,                    /* proiority of the task. */
    &readVoltageTask,     /* Task handel to keep tra ck of created task. */
    1);                   /* choose Core */

  //return 0;
  // return -0.000000000009824 * pow(reading,3) + 0.000000016557283 * pow(reading,2) + 0.000854596860691 * reading + 0.065440348345433;
  //return -0.000000000000016 * pow(reading,4) + 0.000000000118171 * pow(reading,3)- 0.000000301211691 * pow(reading,2)+ 0.001109019271794 * reading + 0.034143524634089;
  return Reading4Task;
} // Added an improved polynomial, use either, comment out as required
