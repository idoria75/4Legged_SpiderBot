#include "Robot.h"

// Robot::Robot(){};

// Robot::Robot(Leg leg1, Leg leg2, Leg leg3, Leg leg4) {
//   legA = leg1;
//   legB = leg2;
//   legC = leg3;
//   legD = leg4;
// }

void Robot::update_leg(Leg leg,
                       int new_shoulder_angle,
                       int new_femur_angle,
                       int new_tibia_angle) {
  leg.update_shoulder_angle(new_shoulder_angle);
  leg.update_femur_angle(new_femur_angle);
  leg.update_tibia_angle(new_tibia_angle);
}
