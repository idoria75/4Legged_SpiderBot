#include "Definitions.h"
#include "Robot.h"

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
      // Send data to client
      StaticJsonBuffer<BUFFER_SIZE_SEND> jsonBufferSend;
      JsonObject& rootSend = jsonBufferSend.createObject();
      JsonArray& sensorData = rootSend.createNestedArray("sensors");
      sensorData.add(rob.getOneDistance("Front"));
      sensorData.add(rob.getOneDistance("Back"));
      sensorData.add(rob.getOneDistance("Left"));
      sensorData.add(rob.getOneDistance("Right"));
      JsonArray& imuData = rootSend.createNestedArray("imu");
      imuData.add(20.575);
      imuData.add(25.678);
      imuData.add(30.123);
      JsonArray& legAData = rootSend.createNestedArray("legA");
      legAData.add(20);
      legAData.add(25);
      legAData.add(30);
      JsonArray& legBData = rootSend.createNestedArray("legB");
      legBData.add(20);
      legBData.add(25);
      legBData.add(30);
      JsonArray& legCData = rootSend.createNestedArray("legC");
      legCData.add(20);
      legCData.add(25);
      legCData.add(30);
      JsonArray& legDData = rootSend.createNestedArray("legD");
      legDData.add(20);
      legDData.add(25);
      legDData.add(30);
      char jsonChar[BUFFER_SIZE_SEND];
      rootSend.printTo((char*)jsonChar, rootSend.measureLength() + 1);
      // Serial.println(jsonChar);
      webSocketServer.sendData(jsonChar);
      // webSocketServer.sendData(rob.serializeDistances());

      // Receive data from Client
      data = webSocketServer.getData();
      // Serial.print("Data: ");
      // Serial.println(data);
      if (data.length() > 0) {
        char data_buf[BUFFER_SIZE_RECV];
        data.toCharArray(data_buf, BUFFER_SIZE_RECV);
        StaticJsonBuffer<BUFFER_SIZE_RECV> jsonBufferRecv;
        JsonObject& rootRecv = jsonBufferRecv.parseObject(data_buf);
        if (!rootRecv.success()) {
          Serial.println("parseObject() failed");
          webSocketServer.sendData("Error!");
          return;
        }
        Serial.print("Mode: ");
        const char* mode = rootRecv["mode"];
        Serial.println(mode);
        Serial.print("Ref: ");
        const char* ref = rootRecv["gaitDirection"];
        Serial.println(ref);
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

void wifiConfiguration() {
  Serial.println("Setting up ESP32 as Access Point");
  WiFi.softAP(ssid);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  server.begin();
  Serial.println("WiFi setup complete!");
}

void threadConfiguration() {
  threadWebsocket.onRun([]() {
    // Serial.println("Receive Data From WS()");
    receiveDataFromWS();
  });
  threadWebsocket.setInterval(200);
  // threadFSM.onRun([]() { runStateMachine(); });
  // threadFSM.setInterval(500);
  groupOfThreads.add(&threadWebsocket);
  // groupOfThreads.add(&threadFSM);
  Serial.println("Thread setup complete!");
}

void runSetUp() {
  Serial.begin(115200);
  pinMode(POWERON_I2C, OUTPUT);
  digitalWrite(POWERON_I2C, LOW);
  Serial.println("Turn on I2C!");
  delay(1000);
  wifiConfiguration();
  delay(1000);
  threadConfiguration();
}

void setDefaultStance() {
  rob.setDefaultPose();
  Serial.println(rob.serializeLegs());
}

void setAnotherStance() {
  rob.setAnotherPose();
  Serial.println(rob.serializeLegs());
}

void configureStates() {
  fsm.add_timed_transition(&stateAnotherStance, &stateDefaultStance, 3000,
                           NULL);
  fsm.add_timed_transition(&stateDefaultStance, &stateAnotherStance, 3000,
                           NULL);
}