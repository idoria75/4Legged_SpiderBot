#pragma once
#include <Arduino.h>
#include <ArduinoJson.h>
#include "Leg.h"
#include "USensor.h"

#define SENSOR_FRONT_ECHO 35
#define SENSOR_FRONT_TRIGGER 23
#define SENSOR_BACK_ECHO 26
#define SENSOR_BACK_TRIGGER 25
#define SENSOR_LEFT_ECHO 33
#define SENSOR_LEFT_TRIGGER 32
#define SENSOR_RIGHT_ECHO 14
#define SENSOR_RIGHT_TRIGGER 27
#define BUFFER_SIZE 512

#define LEG_A_SHOULDER 0
#define LEG_A_FEMUR 1
#define LEG_A_TIBIA 15
#define LEG_B_SHOULDER 2
#define LEG_B_FEMUR 3
#define LEG_B_TIBIA 4
#define LEG_C_SHOULDER 5
#define LEG_C_FEMUR 6
#define LEG_C_TIBIA 8
#define LEG_D_SHOULDER 9
#define LEG_D_FEMUR 10
#define LEG_D_TIBIA 12

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
  // void setDefaultPose();
  // void setAnotherPose();

 public:
  Robot(float shoulderLength, float femurLength, float tibiaLength);
  String getDistances();
  String serializeLegs();
  String serializeDistances();
  void stepForward();
  void setDefaultPose();
  void setAnotherPose();
  void getMotorNumbers();
};