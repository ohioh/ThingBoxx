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
#define TIME_TO_SLEEP 60    /* Time ESP32 will go to sleep (in seconds) */

#define nightSleepTime 21600

int awakeTime = 300;
int actualTime = 0;

TaskHandle_t sleepControllHandle;
RTC_DATA_ATTR int nextSleepTime = 0;
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
  int needrestartValue = 1;
  int address = 90;
  EEPROM.writeFloat(address, needrestartValue);
  delay(1000);
  esp_deep_sleep_start();
}


void setNextSleepTime() {
  checkReboot();
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
    int address = 90;
    int needrestartValue = EEPROM.read(address);
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
    Serial.print("SleepControll begin: Need reboot: ");
    Serial.println(needReboot);
    Serial.println("--------------------");
    delay(3000);
    checkReboot();
    if ( actualTime < nextSleepTime && sleepTimeSet == 1 ) {
      Serial.println("--------------------");
      Serial.print("No keine Schlafenszeit.Waiting for ");
      int leftTime = nextSleepTime - actualTime;
      Serial.print(leftTime);
      Serial.println("--------------------");
      checkReboot();
    } else if (actualTime >= nextSleepTime && sleepTimeSet == 1) {
      needReboot = 1;
      Serial.println("--------------------");
      Serial.println("Schlafenszeit");
      Serial.print("SleepControll activate deepsleep: Need reboot: ");
      Serial.println(needReboot);
      Serial.println("--------------------");
      checkReboot();
      activateDeepSleep();
    } else if ( sleepTimeSet == 0) {
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
