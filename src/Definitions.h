#pragma once

#include <Adafruit_PWMServoDriver.h>
#include <ArduinoJson.h>
#include <Thread.h>
#include <ThreadController.h>
#include <WebSocketServer.h>
#include <WiFi.h>
#include <Wire.h>

#include "FSM.h"
#include "Robot.h"

Adafruit_PWMServoDriver pwmDriver = Adafruit_PWMServoDriver();

#define SERVOMIN 150  // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 600  // this is the 'maximum' pulse length count (out of 4096)
#define MAX_ANGLE 120
#define MIN_ANGLE 60

// For JSON Buffer (based on https://arduinojson.org/v5/assistant/)
#define BUFFER_SIZE_RECV 100
#define BUFFER_SIZE_SEND 512

// Initialize WebSocketServer
WiFiServer server(80);
WebSocketServer webSocketServer;

// Define AP info
const char* ssid = "SPIDERBOT";
const char* password = "seashell";

// Defines threads and their controller:
Thread threadFSM, threadWebsocket;
ThreadController groupOfThreads = ThreadController();

WiFiClient client;
// String to receive data from WS
String data;
bool flagIsConnectedToClient = false;
bool flagWasConnectedToClient = false;
void receiveDataFromWS();

void pinConfiguration();
void boardConfiguration();
void WiFiConfiguration();
void threadConfiguration();

long duration1, distance1;
int echo1 = 5;
int trigger1 = 18;
int echo2 = 26;
int trigger2 = 25;
int echo3 = 33;
int trigger3 = 32;
int echo4 = 14;
int trigger4 = 27;

bool runSetUp();

// void writeToServos();