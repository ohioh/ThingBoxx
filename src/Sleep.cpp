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
#include <Arduino.h>
#include "Sleep.hpp"
#include "Variables.hpp"

void setDeepSleepTime()
{
#define uS_TO_S_FACTOR 1000000 /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP 5        /* Time ESP32 will go to sleep (in seconds) */
}

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
