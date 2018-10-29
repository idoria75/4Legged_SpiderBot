#pragma once
#include <Arduino.h>
#include "Leg.h"

class Robot {
 public:
  Robot();
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
  // Sensors!
};