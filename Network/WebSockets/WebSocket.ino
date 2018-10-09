/*
Developed by Ivan Posca Doria (ivanpdoria@gmail.com)
This code is used to implement a Websocket communication between
the ESP32 and a python client (tested on LINUX).

This code was based on the example provided by TechTutorialsX
https://techtutorialsx.com/2017/11/03/esp32-arduino-websocket-server-over-soft-ap/
*/

#include <WiFi.h>
#include <WebSocketServer.h>

// Initialize WebSocketServer
WiFiServer server(80);
WebSocketServer webSocketServer;

// Define AP info 
const char* ssid = "SPIDERBOT";
const char* password = "seashell";

void setup() {
 
    Serial.begin(115200);

    Serial.println("Setting up ESP32 as Access Point");

    // Initialize ESP32 in AP Mode
    WiFi.softAP(ssid);

    // Get IP address of ESP32 in its own network
    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);
    
    server.begin();
    delay(100);
}
 
void loop() {

    // Get data from client, if connected
    WiFiClient client = server.available();
    
    // If client connected and handshake is successfull
    if (client.connected() && webSocketServer.handshake(client)) {
 
        String data;      
 
        while (client.connected()) {
 
            data = webSocketServer.getData();
 
            // If data
            if (data.length() > 0) {
                 Serial.println(data);
                 data = "Reply: '"+data+"'";
                 webSocketServer.sendData(data);
            }
 
            delay(10); // Delay needed for receiving the data correctly
     }
 
     Serial.println("The client disconnected");
     delay(100);
    }
 
    delay(100);
}
