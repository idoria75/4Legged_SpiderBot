#include "Robot.h"

Robot::Robot(float shoulderLength, float femurLength, float tibiaLength)
    : legA(Leg(shoulderLength,
               femurLength,
               tibiaLength,
               LEG_A_SHOULDER,
               LEG_A_FEMUR,
               LEG_A_TIBIA)),
      legB(Leg(shoulderLength,
               femurLength,
               tibiaLength,
               LEG_B_SHOULDER,
               LEG_B_FEMUR,
               LEG_B_TIBIA)),
      legC(Leg(shoulderLength,
               femurLength,
               tibiaLength,
               LEG_C_SHOULDER,
               LEG_C_FEMUR,
               LEG_C_TIBIA)),
      legD(Leg(shoulderLength,
               femurLength,
               tibiaLength,
               LEG_D_SHOULDER,
               LEG_D_FEMUR,
               LEG_D_TIBIA)),
      sFront(SENSOR_FRONT_ECHO, SENSOR_FRONT_TRIGGER),
      sBack(SENSOR_BACK_ECHO, SENSOR_BACK_TRIGGER),
      sLeft(SENSOR_LEFT_ECHO, SENSOR_LEFT_TRIGGER),
      sRight(SENSOR_RIGHT_ECHO, SENSOR_RIGHT_TRIGGER){};

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
  legDData.add(legD.getShoulderAngle());
  legDData.add(legD.getFemurAngle());
  legDData.add(legD.getTibiaAngle());
  char jsonChar[512];
  root.printTo((char*)jsonChar, root.measureLength() + 1);
  return jsonChar;
}

String Robot::getDistances() {
  String data;
  data = "Front: " + String(sFront.getDistance()) +
         "cm\nBack: " + String(sBack.getDistance()) +
         "cm\nLeft: " + String(sLeft.getDistance()) +
         "cm\nRight:" + String(sRight.getDistance()) + "cm.";
  return data;
}

String Robot::serializeDistances() {
  StaticJsonBuffer<BUFFER_SIZE> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["front"] = sFront.getDistance();
  root["back"] = sBack.getDistance();
  root["left"] = sLeft.getDistance();
  root["right"] = sRight.getDistance();
  char jsonChar[512];
  root.printTo((char*)jsonChar, root.measureLength() + 1);
  return jsonChar;
}

void Robot::setDefaultPose() {
  legA.setDefaultPosition();
  legB.setDefaultPosition();
  legC.setDefaultPosition();
  legD.setDefaultPosition();
}
void Robot::setAnotherPose() {
  legA.setAnotherPosition();
  legB.setAnotherPosition();
  legC.setAnotherPosition();
  legD.setAnotherPosition();
}

void Robot::getMotorNumbers() {
  legA.getMotorNumbers();
  legB.getMotorNumbers();
  legC.getMotorNumbers();
  legD.getMotorNumbers();
}