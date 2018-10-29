/*
Developed by Ivan Posca Doria (ivanpdoria@gmail.com)
This code is used to implement a Websocket communication between
the ESP32 and a python client (tested on LINUX).

This code was based on the example provided by TechTutorialsX
https://techtutorialsx.com/2017/11/03/esp32-arduino-websocket-server-over-soft-ap/
*/

#include <ArduinoJson.h>
#include <WebSocketServer.h>
#include <WiFi.h>

#define BUFFER_SIZE 1024

// Initialize WebSocketServer
WiFiServer server(80);
WebSocketServer webSocketServer;

// Define AP info (Router) [ap_mode = 1]
const char* ssid_ap = "SPIDERBOT";
const char* password_ap = "seashell";

// Define STA info (Client) [ap_mode = 0]
const char* ssid_sta = "GVT-3B34";
const char* password_sta = "0038817805";

int ap_mode = 0;

void setup() {
  Serial.begin(115200);

  if (ap_mode) {
    Serial.println("Setting up ESP32 as Access Point");
    // Initialize ESP32 in AP Mode
    WiFi.softAP(ssid_ap);
    // Get IP address of ESP32 in its own network
    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);
  } else {
    WiFi.begin(ssid_sta, password_sta);
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.println("Connecting to WiFi..");
    }
    Serial.println("Connected to the WiFi network");
    Serial.println(WiFi.localIP());
  }
  server.begin();
  delay(100);
}

String data;
bool flag_isConnectedToClient = false;
bool flag_wasConnectedToClient = false;
WiFiClient client;

int count_msgs_received = 0;
int msg_cont = 0;

void loop() {
  receiveDataFromWS();
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
        Serial.println("Data: ");
        Serial.println(data);

        char data_buf[BUFFER_SIZE];
        data.toCharArray(data_buf, BUFFER_SIZE);
        Serial.println("Data Buf: ");
        Serial.println(data_buf);

        StaticJsonBuffer<1024> jsonBuffer;
        JsonObject& root = jsonBuffer.parseObject(data_buf);

        if (!root.success()) {
          Serial.println("parseObject() failed");
          webSocketServer.sendData("Error!");
          return;
        }

        Serial.print("Message No: ");
        int msg_no = root["MessageNumber"];
        // Serial.println(root["MessageNumber"].as<int>());
        Serial.println(msg_no);

        Serial.print("Mode: ");
        const char* mode = root["Mode"];
        Serial.println(mode);

        Serial.print("Ref: ");
        const char* ref = root["Ref"];
        Serial.println(ref);

        root.prettyPrintTo(Serial);
        Serial.println("");

        Serial.println("Messages already received: ");
        Serial.println(count_msgs_received);

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
  delay(100);
}