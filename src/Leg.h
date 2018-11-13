#pragma once
#include <Arduino.h>
class Leg {
 public:
  Leg(float shoulder_len, float femur_len, float tibia_len);
  uint8_t getShoulderAngle();
  uint8_t getFemurAngle();
  uint8_t getTibiaAngle();
  float getShoulderLength();
  float getFemurLength();
  float getTibiaLength();

 private:
  float shoulderLength;
  float femurLength;
  float tibiaLength;
  uint8_t shoulderAngle;
  uint8_t femurAngle;
  uint8_t tibiaAngle;
  void updateShoulderAngle(uint8_t newShoulderAngle);
  void updatefemurAngle(uint8_t newFemurAngle);
  void updateTibiaAngle(uint8_t newTibiaAngle);
  void updateLegMembers(uint8_t newShoulderAngle,
                        uint8_t newFemurAngle,
                        uint8_t newTibiaAngle);
};