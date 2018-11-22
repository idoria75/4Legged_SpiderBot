/*
Developed by Ivan Posca Doria (ivanpdoria@gmail.com)
*/

#include "Definitions.h"
#include "USensor.h"

Robot rob(2, 3, 4);

unsigned long timeSince = 0;

Adafruit_PWMServoDriver Leg::pwmDriver = Adafruit_PWMServoDriver();

bool flag = 0;

// FSM
// Define states (on_enter, on_state, on_exit)
State stateDefaultStance(&setDefaultStance, NULL, NULL);
State stateAnotherStance(&setAnotherStance, NULL, NULL);
// Initialize machine with initial state
Fsm fsm(&stateDefaultStance);

void setDefaultStance() {
  rob.setDefaultPose();
  Serial.println(rob.serializeLegs());
}

void setAnotherStance() {
  rob.setAnotherPose();
  Serial.println(rob.serializeLegs());
}

// Transition: past state, new state, (DEF) int event, transition call
// fsm.add_transition(&state_led_off, &state_led_on, PIN_EVENT, NULL);
// Timed transition: past state, new state, interval, transition call
// fsm.add_timed_transition(&state_led_on, &state_led_off, 3000, NULL);

void setup() {
  runSetUp();
  rob.getMotorNumbers();
  Ota::self();
  digitalWrite(LED_BUILTIN, LOW);
  Leg::configurePwmDriver();
  fsm.add_timed_transition(&stateAnotherStance, &stateDefaultStance, 1000,
                           NULL);
  fsm.add_timed_transition(&stateDefaultStance, &stateAnotherStance, 1000,
                           NULL);
}

void loop() {
  groupOfThreads.run();
  Ota::self().handle();
  fsm.run_machine();
  yield();
}