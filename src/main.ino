/*
Developed by Ivan Posca Doria (ivanpdoria@gmail.com)
*/

#include "Definitions.h"
#include "USensor.h"

Robot rob(2, 3, 4);

void setup() {
  runSetUp();
}

void loop() {
  Serial.println(rob.getDistances());
  groupOfThreads.run();
  yield();
}
