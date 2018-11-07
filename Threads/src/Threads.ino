/*
Developed by Ivan Posca Doria (ivanpdoria@gmail.com)
*/

#include "Definitions.h"

// Rever necessidade de alocar memoria para o robo dinamicamente
Leg leg1(5, 3, 2, 90, 40, 50);
Leg leg2(2, 4, 4, 20, 50, 30);
Leg leg3(6, 5, 3, 10, 70, 40);
Leg leg4(3, 2, 1, 80, 90, 90);
Robot rob(leg1, leg2, leg3, leg4);

void setup() {
  runSetUp();
  rob.print_leg_status();
  rob.update_leg(1, 45, 45, 45);
  Serial.println("Leg A Updated!");
  rob.print_leg_status();
}

void loop() {
  groupOfThreads.run();
  yield();
}
