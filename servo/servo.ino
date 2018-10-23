/***************************************************
  This is an example for our Adafruit 16-channel PWM & Servo driver
  Servo test - this will drive 8 servos, one after the other on the
  first 8 pins of the PCA9685

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/815

  These drivers use I2C to communicate, 2 pins are required to
  interface.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
// Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);
// you can also call it with a different address and I2C interface
// Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(&Wire, 0x40);

// Depending on your servo make, the pulse width min and max may vary, you
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
#define SERVOMIN 150  // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 600  // this is the 'maximum' pulse length count (out of 4096)

//#define MAX_ANGLE 100
//#define MIN_ANGLE 80

#define MAX_ANGLE 120
#define MIN_ANGLE 60

// our servo # counter
uint8_t servonum = 0;

int new_max = 600;
int new_min = 150;

void setup() {
  Serial.begin(9600);
  Serial.println("8 channel Servo test!");

  pwm.begin();

  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  delay(10);

  new_max = map(MAX_ANGLE, 0, 180, SERVOMIN, SERVOMAX);
  new_min = map(MIN_ANGLE, 0, 180, SERVOMIN, SERVOMAX);
  Serial.print("new_min: ");
  Serial.println(new_min);
  Serial.print("new_max: ");
  Serial.println(new_max);
  delay(2000);

  // Assumindo frente como a "boca"
  // Pernas 1, 2, 3 e 4
  // 1 2
  //  x
  // 3 4

  int perna1 = 1;
  int perna2 = 0;
  int perna3 = 0;
  int perna4 = 0;

  // Perna 1:
  if (perna1 == 1) {
    pwm.setPWM(0, 0, 400);
    pwm.setPWM(1, 0, 420);
    pwm.setPWM(11, 0, 400);
  }

  // Perna 2:
  if (perna2 == 1) {
    pwm.setPWM(2, 0, 350);
    pwm.setPWM(3, 0, 450);
    pwm.setPWM(4, 0, 400);
  }

  // Perna 3: (Feita)
  if (perna3 == 1) {
    pwm.setPWM(5, 0, 400);
    pwm.setPWM(6, 0, 350);  // F
    pwm.setPWM(7, 0, 400);
  }

  // Perna 4:
  if (perna4 == 1) {
    pwm.setPWM(8, 0, 300);
    pwm.setPWM(9, 0, 420);
    pwm.setPWM(10, 0, 400);
  }

  delay(5000);
}

void loop() {
  // Drive each servo one at a time
  Serial.println(servonum);
  delay(1000);
  // for (uint16_t pulselen = new_min; pulselen < new_max; pulselen++) {
  //   Serial.println(pulselen);
  //   pwm.setPWM(servonum, 0, pulselen);
  // }

  // delay(1000);
  // for (uint16_t pulselen = new_max; pulselen > new_min; pulselen--) {
  //   Serial.println(pulselen);
  //   pwm.setPWM(servonum, 0, pulselen);
  // }
  // delay(1000);

  // if (servonum > 1)
  //   servonum = 1;
}
