/*##########################################################################################################
 *  Sleep.cpp
 *  Link: https://randomnerdtutorials.com/esp32-deep-sleep-arduino-ide-wake-up-sources/
 * 
 * 
 * 
 * 
 * 
 * 
 * ########################################################################################################
 */

#include "Sleep.hpp"
#include "Variables.hpp"
#include "Display.hpp"
#include <Arduino.h>


//Deep-Sleep
#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define  TIME_TO_SLEEP  20        /* Time ESP32 will go to sleep (in seconds) */

void setDeepSleepTime(){
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  esp_sleep_enable_ulp_wakeup();
  Serial.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) +
                 " Seconds");
}


void activateDeepSleep()
{
  
  delay(1000);
  Serial.flush(); 
  Serial.println("Display off");
  turnoffDisplay();
  Serial.println("Going to sleep now");
  delay(1000);
  //esp_deep_sleep_start();
  esp_light_sleep_start();
  //esp_deep_sleep(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  
}
