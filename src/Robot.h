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
  Robot(Leg leg1, Leg leg2, Leg leg3, Leg leg4)
      : legA(leg1), legB(leg2), legC(leg3), legD(leg4){};
  Robot(float shoulder_length, float femur_length, float tibia_length);

  //   Robot(float shoulder_length, float femur_length, float tibia_length)
  //       : legA(Leg(shoulder_length, femur_length, tibia_length)),
  //         legB(Leg(shoulder_length, femur_length, tibia_length)),
  //         legC(Leg(shoulder_length, femur_length, tibia_length)),
  //         legD(Leg(shoulder_length, femur_length, tibia_length)){};

  void update_leg(int leg_id,
                  int shoulder_angle,
                  int femur_angle,
                  int tibia_angle);
  void print_leg_status();
  // To-Do
  void step_forward();
};