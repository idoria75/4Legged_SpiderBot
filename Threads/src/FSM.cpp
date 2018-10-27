#include "FSM.h"

int state = 0;
int led_4 = 0;
int led_13 = 0;
int led_15 = 0;
int led_26 = 0;

void updateStateMachine() {
  switch (state) {
    case 0:  // State #0: SetUp
      led_4 = 1;
      led_13 = 0;
      led_15 = 0;
      led_26 = 1;
      state = state + 1;
      break;
    case 1:  // State #1: Reset Stance
      led_4 = 0;
      led_13 = 1;
      led_15 = 1;
      led_26 = 0;
      state = state + 1;
      break;
    case 2:  // State #2: Initial Robot Configuration
      led_4 = 1;
      led_13 = 1;
      led_15 = 1;
      led_26 = 1;
      state = state + 1;
      break;
    case 3:  // State #3: Move B Forward (04)
      led_4 = 1;
      led_13 = 0;
      led_15 = 0;
      led_26 = 0;
      state = state + 1;
      break;
    case 4:  // State #4: Move A Forward (15)
      led_4 = 0;
      led_13 = 0;
      led_15 = 1;
      led_26 = 0;
      state = state + 1;
      break;
    case 5:  // State #5: Push Forward
      led_4 = 1;
      led_13 = 1;
      led_15 = 1;
      led_26 = 1;
      state = state + 1;
      break;
    case 6:  // State #6: Move C Forward (26)
      led_4 = 0;
      led_13 = 0;
      led_15 = 0;
      led_26 = 1;
      state = state + 1;
      break;
    case 7:  // State #7: Move D Forward (13)
      led_4 = 0;
      led_13 = 1;
      led_15 = 0;
      led_26 = 0;
      state = state + 1;
      break;
    case 8:  // State #8: Push Forward -> Loop back to State #3
      led_4 = 1;
      led_13 = 1;
      led_15 = 1;
      led_26 = 1;
      state = 3;
      break;
  }
}

void runStateMachine() {
  updateStateMachine();
  digitalWrite(4, led_4);
  digitalWrite(13, led_13);
  digitalWrite(15, led_15);
  digitalWrite(26, led_26);
}