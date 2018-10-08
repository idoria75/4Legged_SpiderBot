// Based on provant github

#include <Thread.h>
#include <ThreadController.h>

Thread thread1;
ThreadController groupOfThreads = ThreadController();

bool led_status = false;


void change_LED_state(){
    led_status = !led_status;
    Serial.println(led_status);
}

void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);

    pinMode(LED_BUILTIN, OUTPUT);

    thread1.onRun([]() {
        change_LED_state();
    });
    
    thread1.setInterval(500);

    groupOfThreads.add(&thread1);
    //digitalWrite(LED_BUILTIN, led_status);
}

void loop() {

    groupOfThreads.run();
    
    digitalWrite(LED_BUILTIN, led_status);
    
    yield();
}

