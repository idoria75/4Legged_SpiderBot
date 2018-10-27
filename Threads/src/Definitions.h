#pragma once

#include <Thread.h>
#include <ThreadController.h>
#include <WebSocketServer.h>
#include <WiFi.h>

#include "Robot.h"

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
void change_LED_state1();

// Thread 2: WebSocket.getData()
WiFiClient client;
String data;
bool flag_isConnectedToClient = false;
bool flag_wasConnectedToClient = false;
void receiveDataFromWS();

void pinConfiguration();
void WiFiConfiguration();
void boardConfigurations();
void threadConfiguration();
