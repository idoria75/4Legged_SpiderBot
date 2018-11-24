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
#include "USensor.h"
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

Robot rob(2, 3, 4);
Adafruit_PWMServoDriver Leg::pwmDriver = Adafruit_PWMServoDriver();

unsigned long timeSince = 0;
bool flag = 0;

void setDefaultStance();
void setAnotherStance();

// FSM
// Define states (on_enter, on_state, on_exit)
State stateDefaultStance(&setDefaultStance, NULL, NULL);
State stateAnotherStance(&setAnotherStance, NULL, NULL);
// Initialize machine with initial state
Fsm fsm(&stateDefaultStance);

// Transition: past state, new state, (DEF) int event, transition call
// fsm.add_transition(&state_led_off, &state_led_on, PIN_EVENT, NULL);
// Timed transition: past state, new state, interval, transition call
// fsm.add_timed_transition(&state_led_on, &state_led_off, 3000, NULL);

void configureStates();