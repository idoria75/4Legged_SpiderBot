# Developed by Ivan Posca Doria (ivanpdoria@gmail.com)
# This code is used to implement a Websocket communication between
# the ESP32 and a python client (tested on LINUX).

# This code was based on the example provided by TechTutorialsX
# https://techtutorialsx.com/2017/11/03/esp32-arduino-websocket-server-over-soft-ap/

import websocket
import time
import json

time_between_messages = .2
# Define websocket and connect to server
ws = websocket.WebSocket()
ws.connect("ws://192.168.4.1/")

i = 0
nrOfMessages = 200

while i < nrOfMessages:
    # Send message
    x = {
        "mode": "manual",
        "gaitDirection": "forward"
    }
    y = json.dumps(x)
    #print("Sent: ")
    #print(y)
    ws.send(y)

    #ws.send("Message Number: " + str(i))
    # Gets reply from server
    result = ws.recv()
    result_parsed = json.loads(result)
    #print("Received: ")
    #print(result)
    print("Parsed: ")
    print(result_parsed)
    i = i+1
    time.sleep(time_between_messages)

ws.close()
