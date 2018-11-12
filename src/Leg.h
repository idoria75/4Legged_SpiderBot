#pragma once
#include <Arduino.h>
class Leg {
 public:
  // Leg(int shoulder_len, int femur_len, int tibia_len)
  //     : shoulder_length(shoulder_len),
  //       femur_length(femur_len),
  //       tibia_length(tibia_len){};
  Leg(float shoulder_len, float femur_len, float tibia_len);
  uint8_t get_shoulder_angle();
  uint8_t get_femur_angle();
  uint8_t get_tibia_angle();
  float get_shoulder_length();
  float get_femur_length();
  float get_tibia_length();
  void update_leg_members(uint8_t new_shoulder_angle,
                          uint8_t new_femur_angle,
                          uint8_t new_tibia_angle);

 private:
  float shoulder_length;
  float femur_length;
  float tibia_length;
  uint8_t shoulder_angle;
  uint8_t femur_angle;
  uint8_t tibia_angle;
  void update_shoulder_angle(uint8_t new_shoulder_angle);
  void update_femur_angle(uint8_t new_femur_angle);
  void update_tibia_angle(uint8_t new_tibia_angle);
};