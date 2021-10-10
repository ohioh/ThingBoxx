/*##########################################################################################################
    Variables.cpp
    Link:
    1.SENSOR-VARIABLES
    2.COVID-Control -> used from Signals.cpp -> void startSignalController();
   ########################################################################################################
*/
/*##########################################################################################################
    Link:
   ########################################################################################################
*/
// reference: https://www.arduino.cc/reference/de/language/functions/digital-io/pinmode/
// reference: https://www.arduino.cc/reference/de/language/functions/analog-io/analogwrite/

#include <Arduino.h>
#include <stdlib.h>
#include <stdint.h>
#include <cstddef>

#include "LED1.hpp"
#include "Variables.hpp"

TaskHandle_t redAlertBlinkCore;
TaskHandle_t redLEDBlinkCore;

int LED_SET = 2; // 2 Sets are avaible Version1 = 1 the Version2 = 2


////////////////////////////////////////////////////////////////////////////////////////////////////
void setLEDPins()
{
  Serial.println("--------------------");
  Serial.println("Activate LED Pins:");

  switch ( LED_SET )
  {
    case 1:
      {
        pinMode(LED_BUILTIN, OUTPUT);
        pinMode(RED_PIN, OUTPUT); // Setzt den Digitalpin Outputpin
        pinMode(GREEN_PIN, OUTPUT); // Setzt den Digitalpin Outputpin
        pinMode(BLUE_PIN, OUTPUT); // Setzt den Digitalpin Outputpin
        pinMode(ALERT_PIN, OUTPUT);
        digitalWrite(RED_PIN, HIGH);
        digitalWrite(GREEN_PIN, HIGH);
        digitalWrite(BLUE_PIN, HIGH);
        digitalWrite(ALERT_PIN, LOW);
        Serial.println("SET 1 of LEDS.");
        Serial.println("--------------------");
        break;
      }
    case 2:
      {
        pinMode(LED_BUILTIN, OUTPUT);
        pinMode(RED_PIN, OUTPUT); // Setzt den Digitalpin Outputpin
        pinMode(GREEN_PIN, OUTPUT); // Setzt den Digitalpin Outputpin
        pinMode(BLUE_PIN, OUTPUT); // Setzt den Digitalpin Outputpin
        pinMode(ALERT_PIN, OUTPUT);
        pinMode(LED_BUILTIN, HIGH);
        digitalWrite(RED_PIN, LOW);
        digitalWrite(GREEN_PIN, LOW);
        digitalWrite(BLUE_PIN, LOW);
        digitalWrite(ALERT_PIN, LOW);
        Serial.println("SET 2 of LEDS.");
        Serial.println("--------------------");
        break;
      }
  }


}


////////////////////////////////////////////////////////////////////////////////////////////////////
void blinkRedLED(void * pvParameters) {
  String taskMessage = "Task running on core ";
  taskMessage = taskMessage + xPortGetCoreID();
  Serial.println(taskMessage);  //log para o serial monitor
  switch ( LED_SET )
  {
    case 1:
      {
        digitalWrite(RED_PIN, LOW);
        digitalWrite(BLUE_PIN, HIGH);
        digitalWrite(GREEN_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)

        vTaskDelete(NULL);
        break;
      }
    case 2:
      {
        digitalWrite(RED_PIN, HIGH);
        digitalWrite(BLUE_PIN, LOW);
        digitalWrite(GREEN_PIN, LOW);    // turn the LED off by making the voltage LOW

        vTaskDelete(NULL);
        break;
      }

  }

}

////////////////////////////////////////////////////////////////////////////////////////////////////
void blinkRED()
{
  xTaskCreatePinnedToCore(
    blinkRedLED,    // Function that should be called
    "Toggle red LED",   // Name of the task (for debugging)
    10000,            // Stack size (bytes)
    NULL,            // Parameter to pass
    2,               // Task priority
    &redLEDBlinkCore, // Task handle
    0);         //CORE

}


////////////////////////////////////////////////////////////////////////////////////////////////////
void blinkRedALERT(void * pvParameters) {

  switch ( LED_SET )
  {
    case 1:
      {

        digitalWrite(BLUE_PIN, HIGH);
        digitalWrite(GREEN_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)

        for (int i = 0; i <= 60; i++) {
          digitalWrite(ALERT_PIN, HIGH);
          delay(500);
          digitalWrite(ALERT_PIN, LOW);
        }
        
        vTaskDelete(NULL);
        break;
      }
    case 2:
      {

        digitalWrite(BLUE_PIN, LOW);
        digitalWrite(GREEN_PIN, LOW);    // turn the LED off by making the voltage LOW

        for (int i = 0; i <= 60; i++) {
          digitalWrite(ALERT_PIN, HIGH);
          delay(500);
          digitalWrite(ALERT_PIN, LOW);
          delay(500);
        }
        
        vTaskDelete(NULL);
        break;
      }

  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void blinkALERT()
{
  xTaskCreatePinnedToCore(
    blinkRedALERT,    // Function that should be called
    "Toggle red alert LED",   // Name of the task (for debugging)
    10000,            // Stack size (bytes)
    NULL,            // Parameter to pass
    1,               // Task priority
    &redAlertBlinkCore, // Task handle
    0);                 //CORE
}


//set RGB
//analogWrite(pin, value) value as int between 0 and 255


////////////////////////////////////////////////////////////////////////////////////////////////////
void blinkLEDBuildin()
{
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}


////////////////////////////////////////////////////////////////////////////////////////////////////
void blinkGREEN()
{

  switch ( LED_SET )
  {
    case 1:
      {
        digitalWrite(RED_PIN, HIGH);
        digitalWrite(BLUE_PIN, HIGH);
        digitalWrite(GREEN_PIN, LOW);    // turn the LED off by making the voltage LOW
        digitalWrite(ALERT_PIN, LOW);
        break;
      }
    case 2:
      {
        digitalWrite(RED_PIN, LOW);
        digitalWrite(BLUE_PIN, LOW);
        digitalWrite(ALERT_PIN, LOW);

        digitalWrite(GREEN_PIN, HIGH);    // turn the LED off by making the voltage LOW
        delay(50);                       // wait for a second
        break;
      }

  }
}


////////////////////////////////////////////////////////////////////////////////////////////////////
void blinkBLUE()
{
  switch ( LED_SET )
  {
    case 1:
      {
        digitalWrite(RED_PIN, HIGH);
        digitalWrite(BLUE_PIN, HIGH);
        digitalWrite(GREEN_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)

        digitalWrite(GREEN_PIN, LOW);    // turn the LED off by making the voltage LOW

        break;
      }
    case 2:
      {
        digitalWrite(RED_PIN, LOW);
        digitalWrite(BLUE_PIN, LOW);
        digitalWrite(ALERT_PIN, LOW);

        digitalWrite(GREEN_PIN, HIGH);    // turn the LED off by making the voltage LOW
        delay(50);                       // wait for a second
        break;
      }

  }
}


////////////////////////////////////////////////////////////////////////////////////////////////////
void blinkWHITE()
{
  for (byte i = 0; i < white_times; i++) {
    digitalWrite(RED_PIN, LOW);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(GREEN_PIN, LOW);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(BLUE_PIN, LOW);   // turn the LED on (HIGH is the voltage level)
    delay(white_ms);                       // wait for a second
    digitalWrite(RED_PIN, HIGH);    // turn the LED off by making the voltage LOW
    digitalWrite(GREEN_PIN, HIGH);    // turn the LED off by making the voltage LOW
    digitalWrite(BLUE_PIN, HIGH);    // turn the LED off by making the voltage LOW
    delay(white_ms);                       // wait for a second
  }
}


////////////////////////////////////////////////////////////////////////////////////////////////////
void blinkORANGE()
{
  switch ( LED_SET )
  {
    case 1:
      {
        digitalWrite(RED_PIN, LOW);
        digitalWrite(BLUE_PIN, HIGH);
        digitalWrite(GREEN_PIN, LOW);   // turn the LED on (HIGH is the voltage level)
        digitalWrite(ALERT_PIN, LOW);


        break;
      }
    case 2:
      {
        digitalWrite(RED_PIN, HIGH);
        digitalWrite(BLUE_PIN, LOW);
        digitalWrite(GREEN_PIN, HIGH);    // turn the LED off by making the voltage LOW
        digitalWrite(ALERT_PIN, LOW);

        delay(50);                       // wait for a second
        break;
      }

  }
}


////////////////////////////////////////////////////////////////////////////////////////////////////
void mainCO22Signal(int averageCO2) {
  if (averageCO2 <= 750 && averageCO2 > 0 ) {
    blinkGREEN();
    delay(50);
  } else if ( averageCO2 > 750 && averageCO2 <= 999) {
    blinkORANGE();
    delay(50);
  } else if ( averageCO2 >= 1000) {
    blinkALERT();
    blinkRED();
  } else {
    blinkGREEN();
    delay(50);
  }


}
