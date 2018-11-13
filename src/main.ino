/*
Developed by Ivan Posca Doria (ivanpdoria@gmail.com)
*/

#include "Definitions.h"
#include "USensor.h"

Robot rob(2, 3, 4);

unsigned long timeSince = 0;

void setup() {
  runSetUp();
}

void loop() {
  // Serial.println(rob.getDistances());
  if (millis() - timeSince > 1000) {
    Serial.println("Serialization: ");
    Serial.println(rob.serializeLegs());
    timeSince = millis();
  }
  groupOfThreads.run();
  yield();
}
