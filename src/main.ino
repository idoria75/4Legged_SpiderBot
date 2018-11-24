/*
Developed by Ivan Posca Doria (ivanpdoria@gmail.com)
*/

#include "Definitions.h"

void setup() {
  runSetUp();
  Ota::self();
  Leg::configurePwmDriver();
  configureStates();
}

void loop() {
  groupOfThreads.run();
  Ota::self().handle();
  fsm.run_machine();
  yield();
}