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
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN 150  // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 600  // this is the 'maximum' pulse length count (out of 4096)
#define MAX_ANGLE 120
#define MIN_ANGLE 60

// For JSON Buffer (based on https://arduinojson.org/v5/assistant/)
#define BUFFER_SIZE_RECV 100
#define BUFFER_SIZE_SEND 512

// Assumindo frente como a "boca"
// Pernas 1, 2, 3 e 4
// 1 2
//  x
// 3 4

// Perna 1:
// pwm.setPWM(0, 0, 400);
// pwm.setPWM(1, 0, 420);
// pwm.setPWM(11, 0, 400);

// Perna 2:
// pwm.setPWM(2, 0, 350);
// pwm.setPWM(3, 0, 450);
// pwm.setPWM(4, 0, 400);

// Perna 3:
// pwm.setPWM(5, 0, 400);
// pwm.setPWM(6, 0, 350);
// pwm.setPWM(7, 0, 400);

// Perna 4:
// pwm.setPWM(8, 0, 300);
// pwm.setPWM(9, 0, 420);
// pwm.setPWM(10, 0, 400);

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
// String to receive data from WS
String data;
bool flag_isConnectedToClient = false;
bool flag_wasConnectedToClient = false;
void receiveDataFromWS();

void pinConfiguration();
void boardConfiguration();
void WiFiConfiguration();
void threadConfiguration();

bool run_setUp();
