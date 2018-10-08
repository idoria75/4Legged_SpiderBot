// Based on: https://techtutorialsx.com/2017/12/30/esp32-arduino-using-the-pthreads-library/

#include <pthread.h>

bool led_status = false;

void *blink(void *threadid){
    led_status = !led_status;
    Serial.println(led_status);
}

void *printThreadId(void *threadid) {
   Serial.println((int)threadid);
}

void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);

    pinMode(LED_BUILTIN, OUTPUT);

    pthread_t thread1;

    // pthread_create successfull if return is 0
    
    if(pthread_create(&thread1, NULL, blink, NULL)){
        Serial.println("An error has occurred!");
    }
}

void loop() {
    // put your main code here, to run repeatedly:
    digitalWrite(LED_BUILTIN, led_status);
}

