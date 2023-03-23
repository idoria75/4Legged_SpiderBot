/*
Developed by Ivan Posca Doria (ivanpdoria@gmail.com)
*/

#include "Definitions.h"

void setup() {
  runSetUp();
  Ota::self();
  configureStates();
  while (millis() <= 30000) {
    Ota::self().handle();
    Serial.println(millis());
  }
  digitalWrite(POWERON_I2C, HIGH);
  Leg::configurePwmDriver();
}

void loop() {
  rob.calculateDistances();
  groupOfThreads.run();
  Ota::self().handle();
  fsm.run_machine();
  yield();
}