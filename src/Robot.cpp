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

String Robot::serializeLegs() {
  // Serial.println("Serialize Legs!");
  StaticJsonBuffer<BUFFER_SIZE> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  JsonArray& legAData = root.createNestedArray("leg A");
  legAData.add(legA.getShoulderAngle());
  legAData.add(legA.getFemurAngle());
  legAData.add(legA.getTibiaAngle());
  JsonArray& legBData = root.createNestedArray("leg B");
  legBData.add(legB.getShoulderAngle());
  legBData.add(legB.getFemurAngle());
  legBData.add(legB.getTibiaAngle());
  JsonArray& legCData = root.createNestedArray("leg C");
  legCData.add(legC.getShoulderAngle());
  legCData.add(legC.getFemurAngle());
  legCData.add(legC.getTibiaAngle());
  JsonArray& legDData = root.createNestedArray("leg D");
  legDData.add(legC.getShoulderAngle());
  legDData.add(legC.getFemurAngle());
  legDData.add(legC.getTibiaAngle());
  char jsonChar[512];
  root.printTo((char*)jsonChar, root.measureLength() + 1);
  return jsonChar;
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