/*
 *  This sketch sends random data over UDP on a ESP32 device
 *
 */
#include <WiFi.h>
#include <WiFiUdp.h>

// WiFi network name and password:
const char * networkName = "LCA-ROBOTICA";
const char * networkPswd = "RedeRoboticaLca2015";

//IP address to send UDP data to:
// either use the ip address of the server or 
// a network broadcast address
const char * udpAddress = "150.162.209.13";
const int udpPort = 6413;

// Stores incoming messages
const int BUFFER_LEN = 128;
char buffer[BUFFER_LEN];

time_t millis_time = 0;

//Are we currently connected?
boolean connected = false;

//The udp library class
WiFiUDP udp;

void setup(){
  // Initilize hardware serial:
  Serial.begin(115200);
  
  //Connect to the WiFi network
  connectToWiFi(networkName, networkPswd);
}

void loop(){
  //only send data when connected
  if(connected){
    Serial.println("Trying to send packet");
    //Send a packet
    udp.beginPacket(udpAddress,udpPort);
    millis_time = millis()/1000;
    udp.printf("Seconds since boot: %u \n", millis_time);
    udp.endPacket();

    int packetSize = udp.parsePacket();
    if (packetSize) {
      Serial.print("Received packet of size ");
      Serial.println(packetSize);
      //Serial.print("From ");
      //IPAddress remoteIp = udp.remoteIP();
      //Serial.print(remoteIp);
      //Serial.print(", port ");
      //Serial.println(udp.remotePort());

      // read the packet into packetBufffer
      int len = udp.read(buffer, 255);
      if (len > 0) {
        buffer[len] = 0;
      }
      Serial.println("Contents:");
      Serial.println(buffer);

      //Serial.print("Buffer: "); Serial.println(buffer);
    }

    //Wait for 1 second
    delay(1000);
  }
}

void connectToWiFi(const char * ssid, const char * pwd){
  Serial.println("Connecting to WiFi network: " + String(ssid));

  // delete old config
  WiFi.disconnect(true);
  //register event handler
  WiFi.onEvent(WiFiEvent);
  
  //Initiate connection
  WiFi.begin(ssid, pwd);

  Serial.println("Waiting for WIFI connection...");
}

//wifi event handler
void WiFiEvent(WiFiEvent_t event){
    switch(event) {
      case SYSTEM_EVENT_STA_GOT_IP:
          //When connected set 
          Serial.print("WiFi connected! IP address: ");
          Serial.println(WiFi.localIP());  
          //initializes the UDP state
          //This initializes the transfer buffer
          udp.begin(WiFi.localIP(),udpPort);
          connected = true;
          break;
      case SYSTEM_EVENT_STA_DISCONNECTED:
          Serial.println("WiFi lost connection");
          connected = false;
          break;
    }
}
