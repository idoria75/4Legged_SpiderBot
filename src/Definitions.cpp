#include "Definitions.h"

int new_max = map(MAX_ANGLE, 0, 180, SERVOMIN, SERVOMAX);
int new_min = map(MIN_ANGLE, 0, 180, SERVOMIN, SERVOMAX);
int count_msgs_received = 0;

// Receive data from WebSocket (WS)
void receiveDataFromWS() {
  if (!flagIsConnectedToClient) {
    client = server.available();
    if (client.connected() && webSocketServer.handshake(client)) {
      flagIsConnectedToClient = true;
    }
  }
  if (flagWasConnectedToClient == false && flagIsConnectedToClient == true) {
    Serial.println("Client connected!");
  }
  if (flagIsConnectedToClient) {
    if (client.connected()) {
      data = webSocketServer.getData();
      if (data.length() > 0) {
        char data_buf[BUFFER_SIZE_RECV];
        data.toCharArray(data_buf, BUFFER_SIZE_RECV);
        StaticJsonBuffer<BUFFER_SIZE_RECV> jsonBuffer_recv;
        JsonObject& root_recv = jsonBuffer_recv.parseObject(data_buf);
        if (!root_recv.success()) {
          Serial.println("parseObject() failed");
          webSocketServer.sendData("Error!");
          return;
        }
        Serial.print("Mode: ");
        const char* mode = root_recv["mode"];
        Serial.println(mode);
        Serial.print("Ref: ");
        const char* ref = root_recv["gaitDirection"];
        Serial.println(ref);
        StaticJsonBuffer<BUFFER_SIZE_SEND> jsonBuffer_send;
        JsonObject& root_send = jsonBuffer_send.createObject();
        JsonArray& sensor_data = root_send.createNestedArray("sensors");
        sensor_data.add(20);  // sensor_data.add(distance1);
        sensor_data.add(22);
        sensor_data.add(23);
        sensor_data.add(24);
        JsonArray& imu_data = root_send.createNestedArray("imu");
        imu_data.add(20.575);
        imu_data.add(25.678);
        imu_data.add(30.123);
        JsonArray& legA_data = root_send.createNestedArray("legA");
        legA_data.add(20);
        legA_data.add(25);
        legA_data.add(30);
        JsonArray& legB_data = root_send.createNestedArray("legB");
        legB_data.add(20);
        legB_data.add(25);
        legB_data.add(30);
        JsonArray& legC_data = root_send.createNestedArray("legC");
        legC_data.add(20);
        legC_data.add(25);
        legC_data.add(30);
        JsonArray& legD_data = root_send.createNestedArray("legD");
        legD_data.add(20);
        legD_data.add(25);
        legD_data.add(30);
        char jsonChar[BUFFER_SIZE_SEND];
        root_send.printTo((char*)jsonChar, root_send.measureLength() + 1);
        webSocketServer.sendData(jsonChar);
      }
    }
    if (!client.connected()) {
      flagIsConnectedToClient = false;
    }
  }
  if (flagWasConnectedToClient == true && flagIsConnectedToClient == false) {
    Serial.println("Client disconnected!");
  }
  flagWasConnectedToClient = flagIsConnectedToClient;
  delay(10);
}

void pinConfiguration() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void WiFiConfiguration() {
  Serial.println("Setting up ESP32 as Access Point");
  WiFi.softAP(ssid);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  server.begin();
}

void threadConfiguration() {
  threadWebsocket.onRun([]() { receiveDataFromWS(); });
  threadWebsocket.setInterval(1000);
  threadFSM.onRun([]() { runStateMachine(); });
  threadFSM.setInterval(500);
  groupOfThreads.add(&threadWebsocket);
  groupOfThreads.add(&threadFSM);
}

bool runSetUp() {
  Serial.begin(115200);
  pinConfiguration();
  WiFiConfiguration();
  threadConfiguration();
}

/*
void writeToServos() {
  pwmDriver.setPWM(0, 0, 400);
  pwmDriver.setPWM(1, 0, 420);
  pwmDriver.setPWM(11, 0, 400);
  pwmDriver.setPWM(2, 0, 350);
  pwmDriver.setPWM(3, 0, 450);
  pwmDriver.setPWM(4, 0, 400);
  pwmDriver.setPWM(5, 0, 400);
  pwmDriver.setPWM(6, 0, 350);
  pwmDriver.setPWM(7, 0, 400);
  pwmDriver.setPWM(8, 0, 300);
  pwmDriver.setPWM(9, 0, 420);
  pwmDriver.setPWM(10, 0, 400);
}
*/