#pragma once
#include <Arduino.h>
#include "Leg.h"

class Robot {
 private:
  Leg legA;
  Leg legB;
  Leg legC;
  Leg legD;
  int aux;
  void setDefaultPose();
  // Sensors!

 public:
  Robot(float shoulderLength, float femurLength, float tibiaLength);

  void updateLeg(int legId, int shoulderAngle, int femurAngle, int tibiaAngle);
  void printLegStatus();
  // To-Do
  void stepForward();
};