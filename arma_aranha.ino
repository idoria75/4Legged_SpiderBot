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

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);
// you can also call it with a different address and I2C interface
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(&Wire, 0x40);

// Depending on your servo make, the pulse width min and max may vary, you 
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096)

// our servo # counter
uint8_t servonum = 0;
int cont = 0;

void set_initial(){
  
  pwm.setPWM(0, 0,map(110,0,180,150,600)); // mao - diminui para abrir aberto
  pwm.setPWM(1, 0,map(160,0,180,150,600)); //cotovelo - diminui para abrir
  pwm.setPWM(2, 0,map(90,0,180,150,600)); //ombro

  //perna 2 perna dobrada
  pwm.setPWM(3, 0,map(20,0,180,150,600)); // mao - aumenta para abrir 30-fechado
  pwm.setPWM(4, 0,map(20,0,180,150,600)); // cotovelo - aumenta para abrir
  pwm.setPWM(5, 0,map(40,0,180,150,600));

  //perna 3
  pwm.setPWM(6, 0,map(35,0,180,150,600)); // mao - aumenta para abrir
  pwm.setPWM(7, 0,map(20,0,180,150,600)); // cotovelo - aumenta para abrir
  pwm.setPWM(8, 0,map(50,0,180,150,600));

  //perna 4
  pwm.setPWM(9, 0,map(140,0,180,150,600)); // mao - diminui para abrir
  pwm.setPWM(10, 0,map(180,0,180,150,600)); // cotovelo - diminui para abrir
  pwm.setPWM(11, 0,map(80,0,180,150,600)); 
}




void spider_lift(){
  for(int i=0;i<50;i++){
    pwm.setPWM(10, 0,map(180-i,0,180,150,600)); //perna 4
    pwm.setPWM(7, 0,map(20+i,0,180,150,600));  //perna 3
    pwm.setPWM(4, 0,map(20+i,0,180,150,600)); //perna 2
    pwm.setPWM(1, 0,map(160-i,0,180,150,600)); //perna 1
    delay(50);
  }
}
void setup() {
  Serial.begin(9600);
  Serial.println("Chose: ");
  Serial.println("1 - Lift  2 - Initial");

  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
  set_initial();
  delay(10);
}

void loop() {
  delay(2000);
  spider_lift();
  delay(5000);
}
  


