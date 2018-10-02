#include <WiFi.h>
 
const char* ssid = "GVT-3B34";
const char* password =  "0038817805";
 
const uint16_t port = 5005;
const char * host = "192.168.25.165";

int cont = 0;
int flag_connection = 0;

void setup()
{
 
  Serial.begin(115200);
  Serial.print("Hello! \n");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("...");
  }
 
  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());
 
}
 
void loop()
{
    WiFiClient client;
    //if(flag_connection == 0){
    if (!client.connect(host, port)) {
        Serial.println("Connection to host failed");
        delay(1000);
        return;
    }
    //}
    else{
        Serial.println("Connected to server successful!");
        if(cont == 0){
            client.print("Hello from ESP32!");
        }
    }
    // if(cont <= 10){
    //     client.print(cont);
    // }
    // if(cont == 10){
    //     Serial.print("-1");
    //     Serial.println("Disconnecting...");
    //     client.stop();
    // }
    // cont = cont+1;
    delay(500);
}