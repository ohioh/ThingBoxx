/*##########################################################################################################
    Sleep.cpp
    Link: https://randomnerdtutorials.com/esp32-deep-sleep-arduino-ide-wake-up-sources/






   ########################################################################################################
*/
#include <Arduino.h>
#include "Sleep.hpp"
#include "Variables.hpp"
#include "Time.hpp"

#define uS_TO_S_FACTOR 1000000 /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP 120    /* Time ESP32 will go to sleep (in seconds) */

#define nightSleepTime 21600

int awakeTime = 120;
int actualTime = 0;

TaskHandle_t sleepControllHandle;
RTC_DATA_ATTR int nextSleepTime = 0;
RTC_DATA_ATTR int sleepTimeSet = 0 ;
RTC_DATA_ATTR int needReboot = 0 ;



void checkReboot()
{
  if ( needReboot == 1) {
    Serial.println("----------------");
    Serial.println("Restarting in 3 seconds");
    Serial.println("----------------");
    needReboot = 0;
    delay(3000);
    ESP.restart();
  } else {
    Serial.println("----------------");
    Serial.println("No reboot needed");
    Serial.println("----------------");
  }
}


void activateDeepSleep()
{
  sleepTimeSet = 0;
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  Serial.println("Setup ESP32 to sleep for " + String(TIME_TO_SLEEP) +
                 " Seconds");

  Serial.println("Going to sleep now");
  Serial.println("--------------------");
  delay(1000);
  Serial.flush();
  esp_deep_sleep_start();
}


void setNextSleepTime() {

  int acutalTime = getESP32Time();
  nextSleepTime = acutalTime + awakeTime;
  sleepTimeSet = 1;
  Serial.print("next Sleep Time: ");
  Serial.print(nextSleepTime);
  Serial.print(" and sleepTimeSet is ");
  Serial.println(sleepTimeSet);
  Serial.println("--------------------");
}


void controllSleepTime(void *pvParameters) {
  for (;;)    {
    actualTime = getESP32Time();
    delay(5000);
    if ( actualTime < nextSleepTime && sleepTimeSet == 1 ) {
      Serial.println("--------------------");
      Serial.print("No keine Schlafenszeit.Waiting for ");
      int leftTime = nextSleepTime - actualTime;
      Serial.print(leftTime);
      Serial.println("--------------------");
      checkReboot();
    } else if (actualTime >= nextSleepTime && sleepTimeSet == 1) {
      Serial.println("--------------------");
      Serial.println("Schlafenszeit");
      Serial.println("--------------------");
      needReboot = 1;
      activateDeepSleep();
    } else if ( sleepTimeSet == 0) {
      setNextSleepTime();
    } else {
      Serial.println("--------------------");
      Serial.println("Gar Nichts?");
      Serial.println("--------------------");
      checkReboot();
    }
    
  }
  
  yield();

}

void loopSleepTimeControll()
{
  xTaskCreatePinnedToCore(
    controllSleepTime,        // Function that should be called
    "controll Sleep Time",     // Name of the task (for debugging)
    100000,                // Stack size (bytes)
    NULL,                 // Parameter to pass
    5,                    // Task priority
    &sleepControllHandle, // Task handle
    1);                   //CORE

}
