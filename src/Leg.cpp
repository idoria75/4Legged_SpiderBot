#include "Leg.h"

Leg::Leg(float shoulder_length, float femur_length, float tibia_length) {}

void Leg::update_leg_members(uint8_t new_shoulder_angle,
                             uint8_t new_femur_angle,
                             uint8_t new_tibia_angle) {
  update_shoulder_angle(new_shoulder_angle);
  update_femur_angle(new_femur_angle);
  update_tibia_angle(new_tibia_angle);
}

void Leg::update_shoulder_angle(uint8_t new_shoulder_angle) {
  shoulder_angle = new_shoulder_angle;
}

void Leg::update_femur_angle(uint8_t new_femur_angle) {
  femur_angle = new_femur_angle;
}

void Leg::update_tibia_angle(uint8_t new_tibia_angle) {
  tibia_angle = new_tibia_angle;
}

uint8_t Leg::get_shoulder_angle() {
  return shoulder_angle;
}

uint8_t Leg::get_femur_angle() {
  return femur_angle;
}

uint8_t Leg::get_tibia_angle() {
  return tibia_angle;
}

float Leg::get_shoulder_length() {
  return shoulder_length;
}

float Leg::get_femur_length() {
  return femur_length;
}

float Leg::get_tibia_length() {
  return tibia_length;
}