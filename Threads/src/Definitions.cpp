#include "Definitions.h"

int new_max = map(MAX_ANGLE, 0, 180, SERVOMIN, SERVOMAX);
int new_min = map(MIN_ANGLE, 0, 180, SERVOMIN, SERVOMAX);

void change_LED_state1() {
  led_status1 = !led_status1;
}

int count_msgs_received = 0;

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

        // Investigate why this declaration needs to be here for it to work
        char data_buf[BUFFER_SIZE];

        data.toCharArray(data_buf, BUFFER_SIZE);
        Serial.println("Data Buf: ");
        Serial.println(data_buf);

        // Investigate why this declaration needs to be here for it to work
        StaticJsonBuffer<BUFFER_SIZE> jsonBuffer;

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