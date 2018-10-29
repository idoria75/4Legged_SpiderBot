# 1 "/home/ivan/Documents/4Legged_SpiderBot/Threads/src/Definitions.cpp"
# 1 "/home/ivan/Documents/4Legged_SpiderBot/Threads/src/Definitions.cpp"
# 2 "/home/ivan/Documents/4Legged_SpiderBot/Threads/src/Definitions.cpp" 2

int new_max = map(120, 0, 180, 150 /* this is the 'minimum' pulse length count (out of 4096)*/, 600 /* this is the 'maximum' pulse length count (out of 4096)*/);
int new_min = map(60, 0, 180, 150 /* this is the 'minimum' pulse length count (out of 4096)*/, 600 /* this is the 'maximum' pulse length count (out of 4096)*/);

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
  pinMode(LED_BUILTIN, 0x02);
  // Pin Setup for FSM
  pinMode(4, 0x02);
  pinMode(13, 0x02);
  pinMode(15, 0x02);
  pinMode(26, 0x02);
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
# 1 "/home/ivan/Documents/4Legged_SpiderBot/Threads/src/Threads.ino"
/*
Developed by Ivan Posca Doria (ivanpdoria@gmail.com)
*/



void setup() {
  run_setUp();
  Robot rob;
}

void loop() {
  groupOfThreads.run();
  yield();
}
