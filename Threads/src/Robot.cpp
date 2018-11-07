#include "Robot.h"

void Robot::setDefaultPose() {
  legA.update_leg_members(10, 20, 40);
  legB.update_leg_members(10, 20, 40);
  legC.update_leg_members(10, 20, 40);
  legD.update_leg_members(10, 20, 40);
}

void Robot::update_leg(int leg_id,
                       int new_shoulder_angle,
                       int new_femur_angle,
                       int new_tibia_angle) {
  if (leg_id == 1) {
    legA.update_leg_members(new_shoulder_angle, new_femur_angle,
                            new_tibia_angle);
  }
  if (leg_id == 2) {
    legB.update_leg_members(new_shoulder_angle, new_femur_angle,
                            new_tibia_angle);
  }
  if (leg_id == 3) {
    legC.update_leg_members(new_shoulder_angle, new_femur_angle,
                            new_tibia_angle);
  }
  if (leg_id == 4) {
    legD.update_leg_members(new_shoulder_angle, new_femur_angle,
                            new_tibia_angle);
  }
}

// To-Do: Try to enhance the function below:
void Robot::print_leg_status() {
  Serial.println("Leg A:");
  Serial.println(legA.get_shoulder_length());
  Serial.println(legA.get_femur_length());
  Serial.println(legA.get_tibia_length());
  Serial.println(legA.get_shoulder_angle());
  Serial.println(legA.get_femur_angle());
  Serial.println(legA.get_tibia_angle());
  Serial.println("Leg B:");
  Serial.println(legB.get_shoulder_length());
  Serial.println(legB.get_femur_length());
  Serial.println(legB.get_tibia_length());
  Serial.println(legB.get_shoulder_angle());
  Serial.println(legB.get_femur_angle());
  Serial.println(legB.get_tibia_angle());
  Serial.println("Leg C:");
  Serial.println(legC.get_shoulder_length());
  Serial.println(legC.get_femur_length());
  Serial.println(legC.get_tibia_length());
  Serial.println(legC.get_shoulder_angle());
  Serial.println(legC.get_femur_angle());
  Serial.println(legC.get_tibia_angle());
  Serial.println("Leg D:");
  Serial.println(legD.get_shoulder_length());
  Serial.println(legD.get_femur_length());
  Serial.println(legD.get_tibia_length());
  Serial.println(legD.get_shoulder_angle());
  Serial.println(legD.get_femur_angle());
  Serial.println(legD.get_tibia_angle());
}