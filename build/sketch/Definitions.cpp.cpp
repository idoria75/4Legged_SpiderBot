#include <Arduino.h>
#line 1 "/home/ivan/Documents/4Legged_SpiderBot/Threads/src/Definitions.cpp"
#line 1 "/home/ivan/Documents/4Legged_SpiderBot/Threads/src/Definitions.cpp"
#include "Definitions.h"

int new_max = map(MAX_ANGLE, 0, 180, SERVOMIN, SERVOMAX);
int new_min = map(MIN_ANGLE, 0, 180, SERVOMIN, SERVOMAX);

#line 6 "/home/ivan/Documents/4Legged_SpiderBot/Threads/src/Definitions.cpp"
void change_LED_state1();
#line 14 "/home/ivan/Documents/4Legged_SpiderBot/Threads/src/Definitions.cpp"
void receiveDataFromWS();
#line 53 "/home/ivan/Documents/4Legged_SpiderBot/Threads/src/Definitions.cpp"
void pinConfiguration();
#line 63 "/home/ivan/Documents/4Legged_SpiderBot/Threads/src/Definitions.cpp"
void WiFiConfiguration();
#line 75 "/home/ivan/Documents/4Legged_SpiderBot/Threads/src/Definitions.cpp"
void boardConfiguration();
#line 83 "/home/ivan/Documents/4Legged_SpiderBot/Threads/src/Definitions.cpp"
void threadConfiguration();
#line 98 "/home/ivan/Documents/4Legged_SpiderBot/Threads/src/Definitions.cpp"
bool run_setUp();
#line 7 "/home/ivan/Documents/4Legged_SpiderBot/Threads/src/Threads.ino"
void setup();
#line 12 "/home/ivan/Documents/4Legged_SpiderBot/Threads/src/Threads.ino"
void loop();
#line 6 "/home/ivan/Documents/4Legged_SpiderBot/Threads/src/Definitions.cpp"
void change_LED_state1() {
  led_status1 = !led_status1;
}

int count_msgs_received = 0;

StaticJsonBuffer<200> jsonBuffer;

void receiveDataFromWS() {
  Serial.println("receiveDataFromWS");
  if (!flag_isConnectedToClient) {
    client = server.available();
    if (client.connected() && webSocketServer.handshake(client)) {
      flag_isConnectedToClient = true;
    }
  }
  if (flag_wasConnectedToClient == false && flag_isConnectedToClient == true) {
    Serial.println("Client connected!");
  }
  if (flag_isConnectedToClient) {
    if (client.connected()) {
      data = webSocketServer.getData();
      if (data.length() > 0) {
        Serial.print("Data: ");
        Serial.println(data);
        JsonObject& root = jsonBuffer.parseObject(data);
        int msg_cont = root["MessageNumber"];
        Serial.print("Root: ");
        Serial.println(root);
        Serial.print("Message Number: ");
        Serial.println(msg_cont);
        count_msgs_received++;
        data = "Reply: '" + data +
               "'. Msgs recv cnt: " + String(count_msgs_received);
        webSocketServer.sendData(data);
      }
    }
    if (!client.connected()) {
      flag_isConnectedToClient = false;
    }
  }
  if (flag_wasConnectedToClient == true && flag_isConnectedToClient == false) {
    Serial.println("Client disconnected!");
  }
  flag_wasConnectedToClient = flag_isConnectedToClient;
}

void pinConfiguration() {
  // Pin Setup
  pinMode(LED_BUILTIN, OUTPUT);
  // Pin Setup for FSM
  pinMode(4, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(26, OUTPUT);
}

void WiFiConfiguration() {
  // Initialize WiFi service as Access Point (AP)
  Serial.println("Setting up ESP32 as Access Point");
  WiFi.softAP(ssid);
  // Get IP address of ESP32 in its own network
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  // Start websocket server
  server.begin();
}

void boardConfiguration() {
  // Configure pinModes
  pinConfiguration();

  // Initialize serial port
  Serial.begin(115200);
}

void threadConfiguration() {
  thread_blink.onRun([]() { change_LED_state1(); });
  thread_blink.setInterval(100);

  t_websocket.onRun([]() { receiveDataFromWS(); });
  t_websocket.setInterval(1000);

  thread_fsm.onRun([]() { runStateMachine(); });
  thread_fsm.setInterval(500);

  groupOfThreads.add(&thread_blink);
  groupOfThreads.add(&t_websocket);
  groupOfThreads.add(&thread_fsm);
}

bool run_setUp() {
  pinConfiguration();
  boardConfiguration();
  WiFiConfiguration();
  threadConfiguration();
}
#line 1 "/home/ivan/Documents/4Legged_SpiderBot/Threads/src/Threads.ino"
/*
Developed by Ivan Posca Doria (ivanpdoria@gmail.com)
*/

#include "Definitions.h"

void setup() {
  run_setUp();
  Robot rob;
}

void loop() {
  groupOfThreads.run();
  yield();
}

