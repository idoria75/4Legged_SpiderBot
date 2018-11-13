#include "Robot.h"

Robot::Robot(float shoulderLength, float femurLength, float tibiaLength)
    : legA(Leg(shoulderLength, femurLength, tibiaLength)),
      legB(Leg(shoulderLength, femurLength, tibiaLength)),
      legC(Leg(shoulderLength, femurLength, tibiaLength)),
      legD(Leg(shoulderLength, femurLength, tibiaLength)),
      sFront(SENSOR_FRONT_ECHO, SENSOR_FRONT_TRIGGER),
      sBack(SENSOR_BACK_ECHO, SENSOR_BACK_TRIGGER),
      sLeft(SENSOR_LEFT_ECHO, SENSOR_LEFT_TRIGGER),
      sRight(SENSOR_RIGHT_ECHO, SENSOR_RIGHT_TRIGGER){};

void Robot::setDefaultPose() {
  legA.updateLegMembers(10, 20, 40);
  legB.updateLegMembers(10, 20, 40);
  legC.updateLegMembers(10, 20, 40);
  legD.updateLegMembers(10, 20, 40);
}

void Robot::updateLeg(int legId,
                      int newShoulderAngle,
                      int newFemurAngle,
                      int newTibiaAngle) {
  if (legId == 1) {
    legA.updateLegMembers(newShoulderAngle, newFemurAngle, newTibiaAngle);
  }
  if (legId == 2) {
    legB.updateLegMembers(newShoulderAngle, newFemurAngle, newTibiaAngle);
  }
  if (legId == 3) {
    legC.updateLegMembers(newShoulderAngle, newFemurAngle, newTibiaAngle);
  }
  if (legId == 4) {
    legD.updateLegMembers(newShoulderAngle, newFemurAngle, newTibiaAngle);
  }
}

// To-Do: Try to enhance the function below:
void Robot::printLegStatus() {
  Serial.println("Leg A:");
  Serial.println(legA.getShoulderLength());
  Serial.println(legA.getFemurLength());
  Serial.println(legA.getTibiaLength());
  Serial.println(legA.getShoulderAngle());
  Serial.println(legA.getFemurAngle());
  Serial.println(legA.getTibiaAngle());
  Serial.println("Leg B:");
  Serial.println(legB.getShoulderLength());
  Serial.println(legB.getFemurLength());
  Serial.println(legB.getTibiaLength());
  Serial.println(legB.getShoulderAngle());
  Serial.println(legB.getFemurAngle());
  Serial.println(legB.getTibiaAngle());
  Serial.println("Leg C:");
  Serial.println(legC.getShoulderLength());
  Serial.println(legC.getFemurLength());
  Serial.println(legC.getTibiaLength());
  Serial.println(legC.getShoulderAngle());
  Serial.println(legC.getFemurAngle());
  Serial.println(legC.getTibiaAngle());
  Serial.println("Leg D:");
  Serial.println(legD.getShoulderLength());
  Serial.println(legD.getFemurLength());
  Serial.println(legD.getTibiaLength());
  Serial.println(legD.getShoulderAngle());
  Serial.println(legD.getFemurAngle());
  Serial.println(legD.getTibiaAngle());
}

void Robot::serializeLegs() {
  Serial.println("Serialize Legs");
}

String Robot::getSensorSetup() {
  String data;
  data = "Front: " + sFront.getSetup() + "\nBack: " + sBack.getSetup() +
         "\nLeft: " + sLeft.getSetup() + "\nRight:" + sRight.getSetup() + ".";
  return data;
}

String Robot::getDistances() {
  String data;
  data = "Front: " + String(sFront.getDistance()) +
         "cm\nBack: " + String(sBack.getDistance()) +
         "cm\nLeft: " + String(sLeft.getDistance()) +
         "cm\nRight:" + String(sRight.getDistance()) + "cm.";
  return data;
}