

/*
Developed by Ivan Posca Doria (ivanpdoria@gmail.com)
*/

#include "Definitions.h"
#include "USensor.h"

Robot rob(2, 3, 4);

unsigned long timeSince = 0;

Adafruit_PWMServoDriver Leg::pwmDriver = Adafruit_PWMServoDriver();

void setup() {
  runSetUp();
  rob.getMotorNumbers();
  Ota::self();
  digitalWrite(LED_BUILTIN, LOW);
  Leg::configurePwmDriver();
}

bool flag = 0;

void loop() {
  // Serial.println(rob.getDistances());
  if (millis() - timeSince > 1000) {
    Serial.print("Millis: ");
    Serial.println(millis());
    if (flag) {
      rob.setDefaultPose();
    } else {
      rob.setAnotherPose();
    }
    Serial.println("Serialization: ");
    Serial.println(rob.serializeLegs());
    // Serial.println(rob.serializeDistances());
    flag = !flag;
    timeSince = millis();
  }
  groupOfThreads.run();
  Ota::self().handle();
  yield();
}