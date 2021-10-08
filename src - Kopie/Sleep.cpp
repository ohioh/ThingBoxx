/*##########################################################################################################
    Sleep.cpp
    Link: https://randomnerdtutorials.com/esp32-deep-sleep-arduino-ide-wake-up-sources/






   ########################################################################################################
*/
#include <Arduino.h>
#include "Sleep.hpp"
#include "Variables.hpp"

#define uS_TO_S_FACTOR 1000000 /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP 300    /* Time ESP32 will go to sleep (in seconds) */

#define nightSleepTime 21600

void activateDeepSleep()
{
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  Serial.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) +
                 " Seconds");

  Serial.println("Going to sleep now");
  delay(1000);
  Serial.flush();
  esp_deep_sleep_start();
}

void activateNightSleep()
{
  esp_sleep_enable_timer_wakeup(nightSleepTime * uS_TO_S_FACTOR);
  Serial.println("Setup ESP32 to sleep for every " + String(nightSleepTime) +
                 " Seconds");

  Serial.println("Going to sleep now");
  delay(1000);
  Serial.flush();
  esp_deep_sleep_start();
}
