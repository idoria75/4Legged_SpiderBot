/*
Developed by Ivan Posca Doria (ivanpdoria@gmail.com)
*/

#include "Definitions.h"

// FSM (Finite-State Machine)
// State #0: SetUp
// State #1: Reset Stance
// State #2: Initial Robot Configuration
// State #3: Move B Forward (04)
// State #4: Move A Forward (15)
// State #5: Push Forward
// State #6: Move C Forward (26)
// State #7: Move D Forward (13)
// State #8: Push Forward -> Loop back to State #3
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

void setup() {
  // Configure pinModes
  pinConfiguration();

  // Initialize serial port
  Serial.begin(115200);

  // Initialize WiFi service as Access Point (AP)
  Serial.println("Setting up ESP32 as Access Point");
  WiFi.softAP(ssid);
  // Get IP address of ESP32 in its own network
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  // Start websocket server
  server.begin();

  thread_blink.onRun([]() { change_LED_state1(); });
  thread_blink.setInterval(100);

  t_websocket.onRun([]() { receiveDataFromWS(); });
  t_websocket.setInterval(1000);

  thread_fsm.onRun([]() { runStateMachine(); });
  thread_fsm.setInterval(500);

  groupOfThreads.add(&thread_blink);
  groupOfThreads.add(&t_websocket);
  groupOfThreads.add(&thread_fsm);
  // digitalWrite(LED_BUILTIN, led_status);

  // Leg leg1;
  // Serial.print("SHOULDER LENGTH: ");
  // Serial.println(leg1.get_shoulder_length());
  Robot rob;
  // Serial.println(rob.)
}

void loop() {
  groupOfThreads.run();
  yield();
}
