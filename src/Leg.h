#pragma once
#include <Arduino.h>
class Leg {
 public:
  Leg(int shoulder_len, int femur_len, int tibia_len)
      : shoulder_length(shoulder_len),
        femur_length(femur_len),
        tibia_length(tibia_len){};

  int get_shoulder_angle();
  int get_femur_angle();
  int get_tibia_angle();
  int get_shoulder_length();
  int get_femur_length();
  int get_tibia_length();
  void update_leg_members(int new_shoulder_angle,
                          int new_femur_angle,
                          int new_tibia_angle);

 private:
  int shoulder_length;
  int femur_length;
  int tibia_length;
  int shoulder_angle;
  int femur_angle;
  int tibia_angle;
  void update_shoulder_angle(int new_shoulder_angle);
  void update_femur_angle(int new_femur_angle);
  void update_tibia_angle(int new_tibia_angle);
};