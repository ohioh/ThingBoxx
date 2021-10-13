/*##########################################################################################################
    Sleep.cpp
    Link: https://randomnerdtutorials.com/esp32-deep-sleep-arduino-ide-wake-up-sources/






   ########################################################################################################
*/
#include <Arduino.h>
#include <EEPROM.h>//https://github.com/espressif/arduino-esp32/tree/master/libraries/EEPROM
#include "Sleep.hpp"
#include "Variables.hpp"
#include "Time.hpp"

#define uS_TO_S_FACTOR 1000000 /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP 900    /* Time ESP32 will go to sleep (in seconds) */
#define nightSleepTime 21600

TaskHandle_t sleepControllHandle;

long awakeTime = 900;

extern RTC_DATA_ATTR long nextSleepTime = 0;

RTC_DATA_ATTR int sleepTimeSet = 0 ;
RTC_DATA_ATTR int needReboot = 0 ;

//Constants
#define EEPROM_SIZE 12


void checkReboot()
{
  if ( needReboot == 1) {
    Serial.println("^°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°");
    Serial.println("Restarting in 3 seconds");
    Serial.println("^°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°");
    needReboot = 0;

    ESP.restart();
  } else {
    Serial.println("----------------");
    Serial.println("No reboot needed");
    Serial.println("----------------");
  }
}

void activateNightSleep() {
  sleepTimeSet = 0;
  esp_sleep_enable_timer_wakeup(nightSleepTime * uS_TO_S_FACTOR);
  Serial.println("Setup ESP32 to NightSleep for " + String(nightSleepTime) +
                 " Seconds");

  Serial.println("Going to NightSleep now");
  Serial.println("--------------------");
  delay(1000);
  Serial.flush();
  int needrestartValue = 1;
  int address = 90;
  EEPROM.writeFloat(address, needrestartValue);
  delay(1000);

  esp_deep_sleep_start();
}

void activateDeepSleep()
{
  sleepTimeSet = 0;
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  Serial.println("Setup ESP32 to DeepSleep for " + String(TIME_TO_SLEEP) +
                 " Seconds");

  Serial.println("Going to DeepSleep now");
  Serial.println("--------------------");
  delay(1000);
  Serial.flush();
  int needrestartValue = 1;
  int address = 90;
  EEPROM.writeFloat(address, needrestartValue);
  delay(1000);
  esp_deep_sleep_start();
}


void setNextSleepTime() {
  checkReboot();

  delay(250);
  int actualTime = getRTCTime();
  delay(150);
  nextSleepTime = (actualTime + awakeTime);
  sleepTimeSet = 1;
  Serial.println("--------------------");
  Serial.print("next Sleep-Time at ");
  Serial.print(nextSleepTime);
  Serial.print(" and sleepTimeSet is ");
  Serial.println(sleepTimeSet);
  Serial.println("--------------------");
}


void controllSleepTime(void *pvParameters) {
  for (;;)    {
    int actualTime = getRTCTime();
    int address = 90;
    int needrestartValue = EEPROM.read(address);
    checkReboot();
    if (eepromActivated == 0) {
      EEPROM.begin(EEPROM_SIZE);
      eepromActivated = 1;

      int needrestart = 0;
      eepromActivated = 1;
      EEPROM.writeFloat(address, needrestart);//EEPROM.put(address, param);
      EEPROM.commit();
    } else if (eepromActivated == 1 && needrestartValue == 1) {
      ESP.restart();
    }
    Serial.println("--------------------");
    Serial.print("[SleepControll begin] Need reboot: ");
    Serial.println(needReboot);
    Serial.println("--------------------");
    delay(3000);
    checkReboot();
    if ( (actualTime < nextSleepTime) && sleepTimeSet == 1 ) {
      Serial.println("--------------------");
      Serial.print("No keine Schlafenszeit.actual time: ");
      long aTime = actualTime;
      delay(250);
      long nTime = nextSleepTime;
      Serial.println(aTime);
      Serial.print("next sleep time ");
      Serial.println(nTime);
      Serial.println("--------------------");
      Serial.print("differenz: ");
      Serial.println((nTime - aTime));
      Serial.println("--------------------");
      checkReboot();
    } else if ((actualTime >= nextSleepTime) && sleepTimeSet == 1) {
      needReboot = 1;
      Serial.println("--------------------");
      Serial.print("[SleepControll] Need reboot: ");
      Serial.println(needReboot);
      Serial.println("--------------------");

      int actualHour = getRTCHour();
      Serial.println("--------------------");
      Serial.print("[Actual Hour]: ");
      Serial.println(actualHour);
      Serial.println("--------------------");
      if ( actualHour >= 0 && actualHour <= 6) {
        activateNightSleep();
      } else {
        activateDeepSleep();
      }



    } else if ( sleepTimeSet == 0) {
      Serial.println("--------------------");
      Serial.println("Set next Sleep time: ");
      Serial.println("--------------------");
      setNextSleepTime();
      checkReboot();
    } else {
      Serial.println("--------------------");
      Serial.println("Gar Nichts?");
      Serial.println("--------------------");
      checkReboot();
    }

    yield();

  }
}

void loopSleepTimeControll()
{
  xTaskCreatePinnedToCore(
    controllSleepTime,        // Function that should be called
    "controll Sleep Time",     // Name of the task (for debugging)
    100000,                // Stack size (bytes)
    NULL,                 // Parameter to pass
    2,                    // Task priority
    &sleepControllHandle, // Task handle
    1);                   //CORE

}
