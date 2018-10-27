#include "Definitions.h"

void change_LED_state1() {
  led_status1 = !led_status1;
}

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
        Serial.println(data);
        data = "Reply: '" + data + "'";
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

void WiFiConfiguration() {}

void boardConfigurations() {}

void threadConfiguration() {}