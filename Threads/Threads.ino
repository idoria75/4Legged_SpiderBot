/*
Developed by Ivan Posca Doria (ivanpdoria@gmail.com)
*/

#include <WiFi.h>
#include <WebSocketServer.h>
#include <Thread.h>
#include <ThreadController.h>
#include "Leg.h"

// Initialize WebSocketServer
WiFiServer server(80);
WebSocketServer webSocketServer;

// Define AP info 
const char* ssid = "SPIDERBOT";
const char* password = "seashell";

// Defines threads and their controller:
Thread thread_blink, thread_fsm, t_websocket;
ThreadController groupOfThreads = ThreadController();

// thread_blink: Blink
bool led_status1 = false;

void change_LED_state1(){
    led_status1 = !led_status1;
}

// Thread 2: WebSocket.getData()
WiFiClient client;
String data;
bool flag_isConnectedToClient = false;
bool flag_wasConnectedToClient = false;

void receiveDataFromWS(){
    Serial.println("receiveDataFromWS");
    if(!flag_isConnectedToClient){
        client = server.available();
        if(client.connected() && webSocketServer.handshake(client)){
            flag_isConnectedToClient = true;
        }
    }
    if(flag_wasConnectedToClient == false && flag_isConnectedToClient == true){
        Serial.println("Client connected!");
    }    
    if(flag_isConnectedToClient){
        if(client.connected()){
            data = webSocketServer.getData();
            if(data.length() > 0){
                Serial.println(data);
                data = "Reply: '"+data+"'";
                webSocketServer.sendData(data);
            }           
        }
        if(!client.connected()){
            flag_isConnectedToClient = false;
        }
    }
    if(flag_wasConnectedToClient == true && flag_isConnectedToClient == false){
        Serial.println("Client disconnected!");
    }
    flag_wasConnectedToClient = flag_isConnectedToClient;
}

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
int led_4  = 0;
int led_13 = 0;
int led_15 = 0;
int led_26 = 0;

void updateStateMachine(){
    switch (state) {
        case 0: // State #0: SetUp
            led_4  = 1;
            led_13 = 0;
            led_15 = 0;
            led_26 = 1;
            state = state + 1;
            break;
        case 1: // State #1: Reset Stance
            led_4  = 0;
            led_13 = 1;
            led_15 = 1;
            led_26 = 0;
            state = state + 1;
            break;
        case 2: // State #2: Initial Robot Configuration
            led_4  = 1;
            led_13 = 1;
            led_15 = 1;
            led_26 = 1;
            state = state + 1;
            break;
        case 3: // State #3: Move B Forward (04)
            led_4  = 1;
            led_13 = 0;
            led_15 = 0;
            led_26 = 0;
            state = state + 1;
            break;
        case 4: // State #4: Move A Forward (15)
            led_4  = 0;
            led_13 = 0;
            led_15 = 1;
            led_26 = 0;
            state = state + 1;
            break;
        case 5: // State #5: Push Forward
            led_4  = 1;
            led_13 = 1;
            led_15 = 1;
            led_26 = 1;
            state = state + 1;
            break;
        case 6: // State #6: Move C Forward (26)
            led_4  = 0;
            led_13 = 0;
            led_15 = 0;
            led_26 = 1;
            state = state + 1;
            break;
        case 7: // State #7: Move D Forward (13)
            led_4  = 0;
            led_13 = 1;
            led_15 = 0;
            led_26 = 0;
            state = state + 1;
            break;
        case 8: // State #8: Push Forward -> Loop back to State #3
            led_4  = 1;
            led_13 = 1;
            led_15 = 1;
            led_26 = 1;
            state = 3;
            break;
    }
}

void runStateMachine(){
    updateStateMachine();
    digitalWrite( 4, led_4 );
    digitalWrite(13, led_13);
    digitalWrite(15, led_15);
    digitalWrite(26, led_26);
}

void setup() {
    // Pin Setup
    pinMode(LED_BUILTIN, OUTPUT);
    // Pin Setup for FSM
    pinMode( 4, OUTPUT);
    pinMode(13, OUTPUT);
    pinMode(15, OUTPUT);
    pinMode(26, OUTPUT);

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

    thread_blink.onRun([]() {
        change_LED_state1();
    });
    thread_blink.setInterval(500);

    t_websocket.onRun([]() {
        receiveDataFromWS();
    });
    t_websocket.setInterval(1000);

    thread_fsm.onRun([]() {
        runStateMachine();
    });
    thread_fsm.setInterval(500);

    groupOfThreads.add(&thread_blink);
    groupOfThreads.add(&t_websocket);
    groupOfThreads.add(&thread_fsm);
    //digitalWrite(LED_BUILTIN, led_status);

    Leg leg1;
    Serial.println(leg1.get_shoulder_length);
}

void loop() {

    groupOfThreads.run();
    
    digitalWrite(LED_BUILTIN, led_status1);
    
    yield();
}

