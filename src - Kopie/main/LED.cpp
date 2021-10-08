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

#include "LED.hpp"
#include "Variables.hpp"

TaskHandle_t redAlertBlinkCore;
TaskHandle_t redLEDBlinkCore;


////////////////////////////////////////////////////////////////////////////////////////////////////
void setLEDPins()
{
  Serial.println("--------------------");
  Serial.println("Activate LED Pins.");
  Serial.println("--------------------");

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT); // Setzt den Digitalpin Outputpin
  pinMode(GREEN_PIN, OUTPUT); // Setzt den Digitalpin Outputpin
  pinMode(BLUE_PIN, OUTPUT); // Setzt den Digitalpin Outputpin
  pinMode(ALERT_PIN, OUTPUT);
}


////////////////////////////////////////////////////////////////////////////////////////////////////
void blinkRedLED(void * pvParameters) {
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);
  String taskMessage = "Task running on core ";
  taskMessage = taskMessage + xPortGetCoreID();
  Serial.println(taskMessage);  //log para o serial monitor
  for (byte i = 0; i < red_times; i++) {
    digitalWrite(RED_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(red_ms);                       // wait for a second
    digitalWrite(RED_PIN, LOW);    // turn the LED off by making the voltage LOW
    delay(850);                       // wait for a second
  }
  vTaskDelete(NULL);

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
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);
  String taskMessage = "Task running on core ";
  taskMessage = taskMessage + xPortGetCoreID();
  Serial.println(taskMessage);  //log para o serial monitor
  pinMode(ALERT_PIN, OUTPUT);
  Serial.println("Alert-Signal -> ");
  for (uint16_t i = 0 ; i < alert_times; i++) {
    digitalWrite(ALERT_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(alert_ms);
    digitalWrite(ALERT_PIN, LOW);   // turn the LED on (HIGH is the voltage level)
    delay(alert_ms);
  }
  vTaskDelete(NULL);
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
  for (uint16_t i = 0; i < green_times; i++) {
    digitalWrite(RED_PIN, LOW);
    digitalWrite(BLUE_PIN, LOW);
    digitalWrite(GREEN_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(green_ms);                       // wait for a second
    digitalWrite(GREEN_PIN, LOW);    // turn the LED off by making the voltage LOW
    delay(50);                       // wait for a second
  }
}


////////////////////////////////////////////////////////////////////////////////////////////////////
void blinkBLUE()
{
  for (uint16_t i = 0; i < blue_times; i++) {
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(BLUE_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(blue_ms);                       // wait for a second
    digitalWrite(BLUE_PIN, LOW);    // turn the LED off by making the voltage LOW
    delay(50);                       // wait for a second
  }
}


////////////////////////////////////////////////////////////////////////////////////////////////////
void blinkWHITE()
{
  for (byte i = 0; i < white_times; i++) {
    digitalWrite(RED_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(GREEN_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(BLUE_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(white_ms);                       // wait for a second
    digitalWrite(RED_PIN, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite(GREEN_PIN, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite(BLUE_PIN, LOW);    // turn the LED off by making the voltage LOW
    delay(white_ms);                       // wait for a second
  }
}


////////////////////////////////////////////////////////////////////////////////////////////////////
void blinkORANGE()
{
  for (byte i = 0; i < orange_times; i++) {
    digitalWrite(RED_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(GREEN_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(orange_ms);
    // wait for a second
    digitalWrite(RED_PIN, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite(GREEN_PIN, LOW);    // turn the LED off by making the voltage LOW
    delay(50);                       // wait for a second
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
