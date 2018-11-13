#pragma once
#include <Arduino.h>
#include "Leg.h"
#include "USensor.h"

#define SENSOR_FRONT_ECHO 5
#define SENSOR_FRONT_TRIGGER 18
#define SENSOR_BACK_ECHO 26
#define SENSOR_BACK_TRIGGER 25
#define SENSOR_LEFT_ECHO 33
#define SENSOR_LEFT_TRIGGER 32
#define SENSOR_RIGHT_ECHO 14
#define SENSOR_RIGHT_TRIGGER 17

class Robot {
 private:
  Leg legA;
  Leg legB;
  Leg legC;
  Leg legD;
  USensor sFront;
  USensor sBack;
  USensor sLeft;
  USensor sRight;
  int aux;
  void setDefaultPose();
  // Sensors!

 public:
  Robot(float shoulderLength, float femurLength, float tibiaLength);

  void updateLeg(int legId, int shoulderAngle, int femurAngle, int tibiaAngle);
  void printLegStatus();
  // To-Do
  void stepForward();

  void serializeLegs();

  String getSensorSetup();
};