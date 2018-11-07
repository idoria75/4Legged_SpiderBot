// Reference on variables accross multiple files:
// https://stackoverflow.com/questions/12290451/access-extern-variable-in-c-from-another-file

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

// Define ServoDriver
Adafruit_PWMServoDriver pwm_driver = Adafruit_PWMServoDriver();

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
Thread threadFSM, threadWebsocket, threadReadSensor1;
ThreadController groupOfThreads = ThreadController();

// Thread 1: WebSocket.getData()
WiFiClient client;
// String to receive data from WS
String data;
bool flag_isConnectedToClient = false;
bool flag_wasConnectedToClient = false;
void receiveDataFromWS();

void pinConfiguration();
void boardConfiguration();
void WiFiConfiguration();
void threadConfiguration();

long duration1, distance1;
int echo1 = 4;
int trigger1 = 5;

void readSensor1();

bool runSetUp();

// For writing position to servos:

void writeToServos();

// Assumindo frente como a "boca"
// Pernas 1, 2, 3 e 4
// 1 2
//  x
// 3 4

// Perna 1:
// pwm_driver.setPWM(0, 0, 400);
// pwm_driver.setPWM(1, 0, 420);
// pwm_driver.setPWM(11, 0, 400);

// Perna 2:
// pwm_driver.setPWM(2, 0, 350);
// pwm_driver.setPWM(3, 0, 450);
// pwm_driver.setPWM(4, 0, 400);

// Perna 3:
// pwm_driver.setPWM(5, 0, 400);
// pwm_driver.setPWM(6, 0, 350);
// pwm_driver.setPWM(7, 0, 400);

// Perna 4:
// pwm_driver.setPWM(8, 0, 300);
// pwm_driver.setPWM(9, 0, 420);
// pwm_driver.setPWM(10, 0, 400);