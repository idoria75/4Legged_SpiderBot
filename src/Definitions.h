#pragma once

#include <ArduinoJson.h>
#include <ArduinoOTA.h>
#include <Thread.h>
#include <ThreadController.h>
#include <WebSocketServer.h>
#include <WiFi.h>
#include <Wire.h>

#include "Fsm.h"
#include "Robot.h"
#include "ota.h"

// For JSON Buffer (based on https://arduinojson.org/v5/assistant/)
#define BUFFER_SIZE_RECV 100
#define BUFFER_SIZE_SEND 512

// Initialize WebSocketServer
WiFiServer server(80);
WebSocketServer webSocketServer;

// Define AP info
const char* ssid = "SPIDERBOT";
const char* password = "seashell";

// Dfines threads and their controller:
Thread threadWebsocket;
ThreadController groupOfThreads = ThreadController();

// String to receive data from WS
bool flagIsConnectedToClient = false;
bool flagWasConnectedToClient = false;
void receiveDataFromWS();

void pinConfiguration();
void boardConfiguration();
void wifiConfiguration();
void threadConfiguration();
void runSetUp();