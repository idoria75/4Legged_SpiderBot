#pragma once
#include <Arduino.h>

class USensor {
 public:
  USensor(uint8_t echo, uint8_t trigger);
  long getDistance();
  void calculateDistance();
  String getSetup();

 private:
  uint8_t echoPin, triggerPin;
  long distance = 0, duration = 0;
};