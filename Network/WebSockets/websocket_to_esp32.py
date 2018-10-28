# Developed by Ivan Posca Doria (ivanpdoria@gmail.com)
# This code is used to implement a Websocket communication between
# the ESP32 and a python client (tested on LINUX).

# This code was based on the example provided by TechTutorialsX
# https://techtutorialsx.com/2017/11/03/esp32-arduino-websocket-server-over-soft-ap/

# To-Do:
# Finish code cleanly after communication stops

import websocket
import time
import json

time_between_messages = 1
# Define websocket and connect to server
ws = websocket.WebSocket()
ws.connect("ws://192.168.4.1/")

i = 1
nrOfMessages = 200

while i < nrOfMessages:
    # Send message
    # ws.send("Message Number: " + str(i))

    # x = '{ "MessageNumber":"0", "A":'+str(i)+'}'
    # x = '{"MessageNumber":"0"}'

    x = {
        "MessageNumber": i
    }
    y = json.dumps(x)

    json.dumps(x, indent=4)
    # print(i)
    # print(x)
    # print(y)
    ws.send(y)
    #ws.send("Message Number: " + str(i))
    # Gets reply from server
    result = ws.recv()
    print(result)
    i = i+1
    time.sleep(time_between_messages)

ws.close()
