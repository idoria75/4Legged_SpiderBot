#include "USensor.h"

USensor::USensor(uint8_t echo, uint8_t trigger) {
  echoPin = echo;
  triggerPin = trigger;
  pinMode(echo, INPUT);
  pinMode(trigger, OUTPUT);
}

String USensor::getSetup() {
  return "Echo: " + String(echoPin) + ", Trigger: " + String(triggerPin);
}

long USensor::getDistance() {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
  return distance;
}