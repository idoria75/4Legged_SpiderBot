/*
Developed by Ivan Posca Doria (ivanpdoria@gmail.com)
*/

#include "Definitions.h"

void setup() {
  run_setUp();
  Leg leg1;
  Leg leg2;
  Leg leg3;
  Leg leg4;
  Robot rob(leg1, leg2, leg3, leg4);
}

void loop() {
  groupOfThreads.run();
  yield();
}
