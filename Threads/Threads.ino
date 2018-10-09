/*
Developed by Ivan Posca Doria (ivanpdoria@gmail.com)
*/

#include <WiFi.h>
#include <WebSocketServer.h>
#include <Thread.h>
#include <ThreadController.h>

// Initialize WebSocketServer
WiFiServer server(80);
WebSocketServer webSocketServer;

// Define AP info 
const char* ssid = "SPIDERBOT";
const char* password = "seashell";

// Defines threads and their controller:
Thread thread1, thread2, t_websocket;
ThreadController groupOfThreads = ThreadController();

bool led_status1 = false;

// Thread1: Blink
void change_LED_state1(){
    led_status1 = !led_status1;
    Serial.println(led_status1);
    Serial.print("LED:"); Serial.println(LED_BUILTIN);
}

void setup() {
    // Pin Setup
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(4, OUTPUT);

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

    thread1.onRun([]() {
        change_LED_state1();
    });
    thread1.setInterval(500);

    t_websocket.onRun([]() {
        Serial.println("Hello Thread");
    });
    t_websocket.setInterval(1000);


    groupOfThreads.add(&thread1);
    groupOfThreads.add(&t_websocket);
    //digitalWrite(LED_BUILTIN, led_status);
}

void loop() {

    groupOfThreads.run();
    
    digitalWrite(LED_BUILTIN, led_status1);
    
    yield();
}

