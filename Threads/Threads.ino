// Based on provant github

#include <Thread.h>
#include <ThreadController.h>

Thread thread1, thread2;
ThreadController groupOfThreads = ThreadController();

bool led_status1 = false;
bool led_status2 = false;

void change_LED_state1(){
    led_status1 = !led_status1;
    Serial.println(led_status1);
    Serial.print("LED:"); Serial.println(LED_BUILTIN);
}

void change_LED_state2(){
    led_status2 = !led_status2;
    Serial.println(led_status2);
    Serial.print("LED:"); Serial.println("D5");
}

void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);

    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(4, OUTPUT);

    thread1.onRun([]() {
        change_LED_state1();
    });
    thread1.setInterval(500);

    thread2.onRun([](){
        change_LED_state2();
    });
    thread2.setInterval(333);

    Serial.print("LED built-in:"); Serial.println(LED_BUILTIN);

    groupOfThreads.add(&thread1);
    groupOfThreads.add(&thread2);
    //digitalWrite(LED_BUILTIN, led_status);
}

void loop() {

    groupOfThreads.run();
    
    digitalWrite(LED_BUILTIN, led_status1);
    digitalWrite(4, led_status2);
    
    yield();
}

