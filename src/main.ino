/*
Developed by Ivan Posca Doria (ivanpdoria@gmail.com)
*/

#include "Definitions.h"
#include "USensor.h"

// Robot rob(2, 3, 4);

#define SENSOR_FRONT_ECHO 35
#define SENSOR_FRONT_TRIGGER 23
#define SENSOR_BACK_ECHO 26
#define SENSOR_BACK_TRIGGER 25
#define SENSOR_LEFT_ECHO 33
#define SENSOR_LEFT_TRIGGER 32
#define SENSOR_RIGHT_ECHO 14
#define SENSOR_RIGHT_TRIGGER 27
USensor sFront(SENSOR_FRONT_ECHO, SENSOR_FRONT_TRIGGER);
USensor sBack(SENSOR_BACK_ECHO, SENSOR_BACK_TRIGGER);
USensor sLeft(SENSOR_LEFT_ECHO, SENSOR_LEFT_TRIGGER);
USensor sRight(SENSOR_RIGHT_ECHO, SENSOR_RIGHT_TRIGGER);

void setup() {
  // runSetUp();
  // rob.printLegStatus();
  // rob.updateLeg(1, 45, 45, 45);
  // Serial.println("Leg A Updated!");
  // rob.printLegStatus();
  // Serial.println(rob.getSensorSetup());
  Serial.begin(115200);
}

void loop() {
  long duration = 0;
  long distance = 0;

  distance = sFront.getDistance();
  Serial.print("Sensor 1: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(250);
  distance = sBack.getDistance();
  Serial.print("Sensor 2: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(250);
  distance = sLeft.getDistance();
  Serial.print("Sensor 3: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(250);
  distance = sRight.getDistance();
  Serial.print("Sensor 4: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(1000);

  // groupOfThreads.run();
  // yield();
}
