#include "Leg.h"

Leg::Leg(float shoulderLen,
         float femurLen,
         float tibiaLen,
         uint8_t shoulderMotNum,
         uint8_t femurMotNum,
         uint8_t tibiaMotNum) {
  shoulderLength = shoulderLen;
  femurLength = femurLen;
  tibiaLength = tibiaLen;
  shoulderMotorNumber = shoulderMotNum;
  femurMotorNumber = femurMotNum;
  tibiaMotorNumber = tibiaMotNum;
}

void Leg::getMotorNumbers() {
  Serial.println(shoulderMotorNumber);
  Serial.println(femurMotorNumber);
  Serial.println(tibiaMotorNumber);
}

void Leg::setDefaultPosition() {
  updateLegMembers(300, 300, 300);
}

void Leg::setAnotherPosition() {
  updateLegMembers(400, 400, 400);
}

void Leg::updateLegMembers(uint16_t newShoulderAngle,
                           uint16_t newFemurAngle,
                           uint16_t newTibiaAngle) {
  Serial.print("New angle: ");
  Serial.println(newShoulderAngle);
  updateShoulderAngle(newShoulderAngle);
  updatefemurAngle(newFemurAngle);
  updateTibiaAngle(newTibiaAngle);
}

void Leg::updateShoulderAngle(uint16_t newShoulderAngle) {
  shoulderAngle = newShoulderAngle;
}

void Leg::updatefemurAngle(uint16_t newFemurAngle) {
  femurAngle = newFemurAngle;
}

void Leg::updateTibiaAngle(uint16_t newTibiaAngle) {
  tibiaAngle = newTibiaAngle;
}

uint8_t Leg::getShoulderAngle() {
  return shoulderAngle;
}

uint8_t Leg::getFemurAngle() {
  return femurAngle;
}

uint8_t Leg::getTibiaAngle() {
  return tibiaAngle;
}

float Leg::getShoulderLength() {
  return shoulderLength;
}

float Leg::getFemurLength() {
  return femurLength;
}

float Leg::getTibiaLength() {
  return tibiaLength;
}