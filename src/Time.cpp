//########################################################################################################
//  Time.cpp
//
//
//########################################################################################################
#include "Time.hpp"
#include "Arduino.h"
#include "Storage.hpp"
#include "Variables.hpp"

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <cstddef>
#include <ESP32Time.h>

ESP32Time rtc;
RTC_DATA_ATTR long RTC_Time = 0;
RTC_DATA_ATTR int RTC_Time_set = 0;
extern RTC_DATA_ATTR long actualTime = 0 ;

void rtcSetTimeSetup() {
  if ( RTC_Time_set == 0 ) {
    //rtc.setTime(30, 31, 10, 13, 10, 2021); // 17th Jan 2021 15:24:30
    //   https://www.epochconverter.com/timezones?q=1634115052&tz=Europe%2FBerlin         
    rtc.setTime(1634126789);  // example 1st Jan 2021 00:00:00
    delay(50);
    
    Serial.println("---------------");                            //  (String) 15:24:38
    Serial.println("Set time to:");                            //  (String) 15:24:38
    RTC_Time_set = 1;
  } else if ( RTC_Time_set == 1) {
    Serial.println(rtc.getTime());                            //  (String) 15:24:38
    Serial.println("---------------");                            //  (String) 15:24:38
  }
}

void rtcBeginnTimeSetup() {
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

long getRTCTime() {
  actualTime = rtc.getEpoch();
  Serial.println("---------------");
  Serial.print("actual Time: ");
  Serial.println(actualTime); // 
  Serial.println(rtc.getTime()); //  
  Serial.println("---------------");
  return(actualTime);
}

int getRTCHour() {
  int hour = rtc.getHour();
  return(hour);
}
/*
  #include "RTCDS1307.h"
  RTCDS1307 rtc(0x68);
  uint8_t year, month, weekday, day, hour, minute, second;
  bool period = 0;
  String m[12] = {"Januar", "Februar", "März", "April", "Mai", "Juni", "Juli", "August", "September", "Oktober", "November", "Dezember"};
  String w[7] = {"Montag", "Dienstag", "Mittwoch", "Donnerstag", "Freitag", "Samstag", "Sonntag"};
*/


/*
  void rtcSetTimeSetup() {

  rtc.setDate(21, 10, 13);
  rtc.setTime(05, 51, 50);
  }

  void rtcBeginnTimeSetup(){
  rtc.begin();
  }

  int getRTCTime(){
    int actualTime;
    rtc.getDate(year, month, day, weekday);
    actualTime = rtc.getTime(hour, minute, second, period);
    if (!(second % 3)) rtc.setMode(1 - rtc.getMode());
    rtc.getTime(hour, minute, second, period);

    Serial.print(w[weekday - 1]);
    Serial.print("  ");
    Serial.print(day, DEC);
    Serial.print("/");
    Serial.print(m[month - 1]);
    Serial.print("/");
    Serial.print(year + 2000, DEC);
    Serial.print("  ");
    Serial.print(hour, DEC);
    Serial.print(":");
    Serial.print(minute, DEC);
    Serial.print(":");
    Serial.print(second, DEC);
    Serial.print(rtc.getMode() ? (period ? " PM" : " AM") : "");
    Serial.println();
    delay(1000);
    return(actualTime);
  }
*/
