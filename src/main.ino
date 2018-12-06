/*
Developed by Ivan Posca Doria (ivanpdoria@gmail.com)
*/

#include "Definitions.h"

void setup() {
  runSetUp();
  // Ota::self();
  // Leg::configurePwmDriver();
  // configureStates();
  // while (millis() <= 30000) {
  //   Ota::self().handle();
  // }
}

void loop() {
  rob.calculateDistances();

  // if (millis() - timeSince > 1000) {
  //   Serial.print("Millis: ");
  //   Serial.println(millis());
  //   if (flag) {
  //     rob.setDefaultPose();
  //   } else {
  //     rob.setAnotherPose();
  //   }
  //   // Serial.println(rob.serializeDistances());
  //   flag = !flag;
  //   timeSince = millis();
  // }

  groupOfThreads.run();
  // Ota::self().handle();
  // fsm.run_machine();
  yield();
}