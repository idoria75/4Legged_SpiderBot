#include "Leg.h"

void Leg::update_leg_members(int new_shoulder_angle,
                             int new_femur_angle,
                             int new_tibia_angle) {
  update_shoulder_angle(new_shoulder_angle);
  update_femur_angle(new_femur_angle);
  update_tibia_angle(new_tibia_angle);
}

void Leg::update_shoulder_angle(int new_shoulder_angle) {
  shoulder_angle = new_shoulder_angle;
}

void Leg::update_femur_angle(int new_femur_angle) {
  femur_angle = new_femur_angle;
}

void Leg::update_tibia_angle(int new_tibia_angle) {
  tibia_angle = new_tibia_angle;
}

int Leg::get_shoulder_angle() {
  return shoulder_angle;
}

int Leg::get_femur_angle() {
  return femur_angle;
}

int Leg::get_tibia_angle() {
  return tibia_angle;
}

int Leg::get_shoulder_length() {
  return shoulder_length;
}

int Leg::get_femur_length() {
  return femur_length;
}

int Leg::get_tibia_length() {
  return tibia_length;
}