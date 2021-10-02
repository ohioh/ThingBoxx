#include "REBOOT.hpp"
#include <Arduino.h>

void rebootESP32(int timeToReboot) {
  Serial.println("Restarting in 10 seconds");

  delay(timeToReboot);

  ESP.restart();
}
