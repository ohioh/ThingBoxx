//########################################################################################################
//  Time.cpp
//
//
//########################################################################################################
#include "Time.hpp"
#include <ESP32Time.h>
#include "Storage.hpp"
#include "Variables.hpp"

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <cstddef>

ESP32Time rtc;
RTC_DATA_ATTR long RTC_Time = 0;
RTC_DATA_ATTR int RTC_Time_set = 0;

void setESP32Time()
{
  if ( RTC_Time_set == 0 ) {
    rtc.setTime(30, 50, 7, 8, 10, 2021); // 17th Jan 2021 15:24:30

    //rtc.setTime(1609459200);  // 1st Jan 2021 00:00:00
    Serial.println("---------------");                            //  (String) 15:24:38
    Serial.println("Set time to:");                            //  (String) 15:24:38
    RTC_Time_set = 1;
  } else if ( RTC_Time_set == 1) {
    Serial.println("Actual time to:");                            //  (String) 15:24:38
    Serial.println(rtc.getTime());                            //  (String) 15:24:38
    Serial.println("---------------");                            //  (String) 15:24:38
  }

}

void getESP32Time()
{
  Serial.println(rtc.getTime()); //  (String) 15:24:38
}

void storeESP32Time()
{
  Serial.println("---------------");
  Serial.println("Write Time to non-volatiy Storage"); //  (String) 15:24:38
  
  DEVICE_STATE = rtc.getHour(true);
  
  Serial.print("Full Hour: ");
  Serial.println(DEVICE_STATE);
  Serial.println("---------------");
  Serial.print("Full Time: ");
  Serial.println(rtc.getTime());
  Serial.println("---------------");
}
