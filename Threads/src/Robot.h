#pragma once
#include <Arduino.h>
#include "Leg.h"

class Robot {
 public:
  // Robot() : aux(0){};
  // Robot(Leg leg1, Leg leg2, Leg leg3, Leg leg4);
  Robot(Leg leg1, Leg leg2, Leg leg3, Leg leg4)
      : legA(leg1), legB(leg2), legC(leg3), legD(leg4){};
  void step_forward();
  void update_leg(Leg leg,
                  int shoulder_angle,
                  int femur_angle,
                  int tibia_angle);

 private:
  Leg legA;
  Leg legB;
  Leg legC;
  Leg legD;
  int aux;
  // Sensors!
};