#pragma once
#include <Adafruit_PWMServoDriver.h>
#include <Arduino.h>

#define SERVOMIN 150  // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 600  // this is the 'maximum' pulse length count (out of 4096)
#define MAX_ANGLE 120
#define MIN_ANGLE 60

class Leg {
 public:
  Leg(float shoulderLen,
      float femurLen,
      float tibiaLen,
      uint8_t shoulderMotNum,
      uint8_t femurMotNum,
      uint8_t tibiaMotNum);
  uint8_t getShoulderAngle();
  uint8_t getFemurAngle();
  uint8_t getTibiaAngle();
  float getShoulderLength();
  float getFemurLength();
  float getTibiaLength();
  void setDefaultPosition();
  void setAnotherPosition();
  void getMotorNumbers();

 private:
  static Adafruit_PWMServoDriver pwmDriver;
  uint8_t shoulderMotorNumber;
  uint8_t femurMotorNumber;
  uint8_t tibiaMotorNumber;
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