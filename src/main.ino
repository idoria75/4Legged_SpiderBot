/*
Developed by Ivan Posca Doria (ivanpdoria@gmail.com)
*/

#include "Definitions.h"
#include "USensor.h"

Robot rob(2, 3, 4);
USensor s(5, 18);
void setup() {
  runSetUp();
  rob.printLegStatus();
  rob.updateLeg(1, 45, 45, 45);
  Serial.println("Leg A Updated!");
  rob.printLegStatus();
  Serial.println(s.getDistance());
  Serial.println(s.getSetup());
}

void loop() {
  groupOfThreads.run();
  yield();
}
