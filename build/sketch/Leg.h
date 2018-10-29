#pragma once
#include <Arduino.h>

#define INITIAL_SHOULDER_ANGLE 0;
#define INITIAL_FEMUR_ANGLE 0;
#define INITIAL_TIBIA_ANGLE 0;

// #define SHOULDER_LENGTH 5;
// #define FEMUR_LENGTH    5;
// #define TIBIA_LENGTH    4;

class Leg {
 public:
  Leg();
  void update_shoulder_angle(int new_shoulder_angle);
  void update_femur_angle(int new_femur_angle);
  void update_tibia_angle(int new_tibia_angle);
  int get_shoulder_angle();
  int get_femur_angle();
  int get_tibia_angle();
  int get_shoulder_length();
  int get_femur_length();
  int get_tibia_length();

 private:
  const int shoulder_length = 5;
  const int femur_length = 5;
  const int tibia_length = 3;
  int shoulder_angle;
  int femur_angle;
  int tibia_angle;

  // Leg();
};