/*
Developed by Ivan Posca Doria (ivanpdoria@gmail.com)
*/

#include "Definitions.h"

void setup() {
  run_setUp();
  Robot rob;
}

void loop() {
  groupOfThreads.run();
  yield();
}
