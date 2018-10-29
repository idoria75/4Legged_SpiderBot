#include "Definitions.h"

int new_max = map(MAX_ANGLE, 0, 180, SERVOMIN, SERVOMAX);
int new_min = map(MIN_ANGLE, 0, 180, SERVOMIN, SERVOMAX);

void change_LED_state1() {
  led_status1 = !led_status1;
}

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
        sensor_data.add(21);
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