#include "Definitions.h"

int new_max = map(MAX_ANGLE, 0, 180, SERVOMIN, SERVOMAX);
int new_min = map(MIN_ANGLE, 0, 180, SERVOMIN, SERVOMAX);
int count_msgs_received = 0;

// Receive data from WebSocket (WS)
void receiveDataFromWS() {
  // If no client connected to WS
  if (!flag_isConnectedToClient) {
    client = server.available();
    // If client connects and handshakes
    if (client.connected() && webSocketServer.handshake(client)) {
      flag_isConnectedToClient = true;
    }
  }
  // If client just connected, print to serial
  if (flag_wasConnectedToClient == false && flag_isConnectedToClient == true) {
    Serial.println("Client connected!");
  }
  // If flag means client is connected
  if (flag_isConnectedToClient) {
    // Check if still connected
    if (client.connected()) {
      // Retrieve data from client
      data = webSocketServer.getData();
      // If there is data
      if (data.length() > 0) {
        // Investigate why this needs to be here for it to work
        // Converts string received to chat array
        char data_buf[BUFFER_SIZE_RECV];
        data.toCharArray(data_buf, BUFFER_SIZE_RECV);

        // Investigate why this declaration needs to be here for it to work
        StaticJsonBuffer<BUFFER_SIZE_RECV> jsonBuffer_recv;
        JsonObject& root_recv = jsonBuffer_recv.parseObject(data_buf);

        // If parsing fails
        if (!root_recv.success()) {
          Serial.println("parseObject() failed");
          // Sends to client "Error" message
          webSocketServer.sendData("Error!");
          return;
        }

        // Prints mode received from JSON
        Serial.print("Mode: ");
        const char* mode = root_recv["mode"];
        Serial.println(mode);

        // Prints gaitDirection received from JSON
        Serial.print("Ref: ");
        const char* ref = root_recv["gaitDirection"];
        Serial.println(ref);

        // Creates JSON for sending data
        StaticJsonBuffer<BUFFER_SIZE_SEND> jsonBuffer_send;
        JsonObject& root_send = jsonBuffer_send.createObject();

        // Creates nested objects
        JsonArray& sensor_data = root_send.createNestedArray("sensors");
        sensor_data.add(distance1);
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

        // root_send.prettyPrintTo(Serial);

        // Creates char array to send message to client
        char jsonChar[BUFFER_SIZE_SEND];
        // Copy JSON to char array
        root_send.printTo((char*)jsonChar, root_send.measureLength() + 1);
        // Sends JSON to client
        webSocketServer.sendData(jsonChar);
      }
    }
    // If client is not connected
    if (!client.connected()) {
      flag_isConnectedToClient = false;
    }
  }
  // If client has just disconnected
  if (flag_wasConnectedToClient == true && flag_isConnectedToClient == false) {
    Serial.println("Client disconnected!");
  }
  // Updates previous connection status
  flag_wasConnectedToClient = flag_isConnectedToClient;
  delay(10);
}

void pinConfiguration() {
  // Pin Setup
  pinMode(LED_BUILTIN, OUTPUT);
  // Pin Setup for Sensor 1
  pinMode(echo1, INPUT);
  pinMode(trigger1, OUTPUT);
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
  threadWebsocket.onRun([]() { receiveDataFromWS(); });
  threadWebsocket.setInterval(1000);

  threadFSM.onRun([]() { runStateMachine(); });
  threadFSM.setInterval(500);

  threadReadSensor1.onRun([]() { readSensor1(); });
  threadReadSensor1.setInterval(500);

  groupOfThreads.add(&threadWebsocket);
  groupOfThreads.add(&threadFSM);
  groupOfThreads.add(&threadReadSensor1);
}

void readSensor1() {
  digitalWrite(trigger1, LOW);
  delayMicroseconds(2);

  digitalWrite(trigger1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger1, LOW);
  duration1 = pulseIn(echo1, HIGH);
  distance1 = (duration1 / 2) / 29.1;

  Serial.print(distance1);
  Serial.println(" cm");
}

bool runSetUp() {
  pinConfiguration();
  boardConfiguration();
  WiFiConfiguration();
  threadConfiguration();
}

void writeToServos() {
  // Perna 1:
  pwm_driver.setPWM(0, 0, 400);   // SHOULDER
  pwm_driver.setPWM(1, 0, 420);   // FEMUR
  pwm_driver.setPWM(11, 0, 400);  // TIBIA

  // Perna 2:
  pwm_driver.setPWM(2, 0, 350);  // SHOULDER
  pwm_driver.setPWM(3, 0, 450);  // FEMUR
  pwm_driver.setPWM(4, 0, 400);  // TIBIA

  // Perna 3:
  pwm_driver.setPWM(5, 0, 400);  // SHOULDER
  pwm_driver.setPWM(6, 0, 350);  // FEMUR
  pwm_driver.setPWM(7, 0, 400);  // TIBIA

  // Perna 4:
  pwm_driver.setPWM(8, 0, 300);   // SHOULDER
  pwm_driver.setPWM(9, 0, 420);   // FEMUR
  pwm_driver.setPWM(10, 0, 400);  // TIBIA
}