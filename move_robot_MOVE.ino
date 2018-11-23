#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  150 
#define SERVOMAX  801 
#define FIRST_TEXT 1
#define SECOND_TEXT 2
#define NUMBER_SERVO 12
#define MAX_ANGLE 105
#define MIN_ANGLE 75
#define DELAY_TIME 100
#define DELAY_TIME_SLOW_MOVE 5
#define SERVO_VALUE_STEP 8
#define NaN 0

#define COXA_DEFAULT_LEG_1 400
#define COXA_DEFAULT_LEG_2 390
#define COXA_DEFAULT_LEG_3 400
#define COXA_DEFAULT_LEG_4 390

#define FEMUR_DEFAULT_LEG_1 270 
#define FEMUR_DEFAULT_LEG_2 550 
#define FEMUR_DEFAULT_LEG_3 300 
#define FEMUR_DEFAULT_LEG_4 440 
/*
#define TIBIA_DEFAULT_LEG_1 250
#define TIBIA_DEFAULT_LEG_2 450
#define TIBIA_DEFAULT_LEG_3 500
#define TIBIA_DEFAULT_LEG_4 500 */

#define TIBIA_DEFAULT_LEG_1 270
#define TIBIA_DEFAULT_LEG_2 480
#define TIBIA_DEFAULT_LEG_3 520
#define TIBIA_DEFAULT_LEG_4 480

#define FEMUR_UP_LEG_1 510
#define FEMUR_UP_LEG_2 340
#define FEMUR_UP_LEG_3 500
#define FEMUR_UP_LEG_4 240

#define TIBIA_UP_LEG_1 350
#define TIBIA_UP_LEG_2 350
#define TIBIA_UP_LEG_3 600
#define TIBIA_UP_LEG_4 400

#define FORWARD_COXA_1_LEG_1 510
#define FORWARD_COXA_1_LEG_2 470
#define FORWARD_COXA_1_LEG_3 470
#define FORWARD_COXA_1_LEG_4 500

#define FORWARD_COXA_2_LEG_1 250
#define FORWARD_COXA_2_LEG_2 210
#define FORWARD_COXA_2_LEG_3 210
#define FORWARD_COXA_2_LEG_4 240

#define FORWARD_COXA_3_LEG_1 260
#define FORWARD_COXA_3_LEG_2 230
#define FORWARD_COXA_3_LEG_3 230
#define FORWARD_COXA_3_LEG_4 250

#define FORWARD_COXA_4_LEG_1 550
#define FORWARD_COXA_4_LEG_2 470
#define FORWARD_COXA_4_LEG_3 500
#define FORWARD_COXA_4_LEG_4 500

#define COXA_LEG_1 0
#define COXA_LEG_2 2
#define COXA_LEG_3 5
#define COXA_LEG_4 9

#define FEMUR_LEG_1 1
#define FEMUR_LEG_2 3
#define FEMUR_LEG_3 6
#define FEMUR_LEG_4 10

#define TIBIA_LEG_1 15
#define TIBIA_LEG_2 4
#define TIBIA_LEG_3 8
#define TIBIA_LEG_4 12

int number_input_id;
int number_input_value;
int new_max = 600;
int new_min = 150;

int vector_values[16] = {COXA_DEFAULT_LEG_1,FEMUR_DEFAULT_LEG_1,COXA_DEFAULT_LEG_2,
                         FEMUR_DEFAULT_LEG_2, TIBIA_DEFAULT_LEG_2, COXA_DEFAULT_LEG_3,   
                         FEMUR_DEFAULT_LEG_3, NaN, TIBIA_DEFAULT_LEG_3, 
                         COXA_DEFAULT_LEG_4, FEMUR_DEFAULT_LEG_4, NaN,
                         TIBIA_DEFAULT_LEG_4, NaN, NaN,
                         TIBIA_DEFAULT_LEG_1};
                                

void sweet_setPWM(int servo_number, int weird_number, int final_servo_value){
  int servo_value = vector_values[servo_number];
  int servo_value_step = 0;
  if(vector_values[servo_number] > final_servo_value){
    servo_value_step = -SERVO_VALUE_STEP;
  }
  else{
    servo_value_step = SERVO_VALUE_STEP;
  }
  while(abs(servo_value - final_servo_value) > 10){
    servo_value = servo_value + servo_value_step;
    pwm.setPWM(servo_number, weird_number ,servo_value);
    delay(DELAY_TIME);
  
  }
  vector_values[servo_number] = servo_value;
}

void quick_setPWM(int servo_number, int weird_number, int final_servo_value){
    vector_values[servo_number] = final_servo_value;
    pwm.setPWM(servo_number, weird_number ,final_servo_value);
    delay(DELAY_TIME);
}

void adjust_tibia_pos(int servo){
  
  if(servo == TIBIA_LEG_1 ){
    quick_setPWM(15, 0,TIBIA_DEFAULT_LEG_1 );
    quick_setPWM(15, 0,TIBIA_UP_LEG_1 );
    quick_setPWM(15, 0,TIBIA_DEFAULT_LEG_1 );
  }
  else if(servo == TIBIA_LEG_2 ){
    quick_setPWM(4, 0,TIBIA_DEFAULT_LEG_2 );
    quick_setPWM(4, 0,TIBIA_UP_LEG_2 );
    quick_setPWM(4, 0,TIBIA_DEFAULT_LEG_2 );
  }
  else if(servo == TIBIA_LEG_3 ){
    quick_setPWM(8, 0,TIBIA_DEFAULT_LEG_3 );
    quick_setPWM(8, 0,TIBIA_UP_LEG_3 );
    quick_setPWM(8, 0,TIBIA_DEFAULT_LEG_3 );
  }
  else if(servo == TIBIA_LEG_4 ){
    quick_setPWM(12, 0,TIBIA_DEFAULT_LEG_4 );
    quick_setPWM(12, 0,TIBIA_UP_LEG_4 );
    quick_setPWM(12, 0,TIBIA_DEFAULT_LEG_4 );
  }
  delay(DELAY_TIME);
}

void set_initial(){

  //RIGHT TOLKEN LEG
  //sweet_setPWM(1, 0,FEMUR_UP_LEG_1 );
  delay(DELAY_TIME);
  pwm.setPWM(0, 0,COXA_DEFAULT_LEG_1 );
  //pwm.setPWM(0, 0,FORWARD_COXA_1_LEG_1 );
  delay(DELAY_TIME);
  pwm.setPWM(1, 0,FEMUR_DEFAULT_LEG_1 );
  delay(DELAY_TIME);
  pwm.setPWM(15, 0,TIBIA_DEFAULT_LEG_1 );
  delay(DELAY_TIME);
  
  //BACK TOLKEN LEG
  //sweet_setPWM(3, 0,FEMUR_UP_LEG_2 );
  delay(DELAY_TIME);
  pwm.setPWM(2, 0,COXA_DEFAULT_LEG_2 );
  //pwm.setPWM(2, 0,FORWARD_COXA_1_LEG_2 );
  delay(DELAY_TIME);
  pwm.setPWM(3, 0,FEMUR_DEFAULT_LEG_2 );
  delay(DELAY_TIME);
  pwm.setPWM(4, 0,TIBIA_DEFAULT_LEG_2 );
  delay(DELAY_TIME);
  
  //LEFT TOLKEN LEG
  //sweet_setPWM(6, 0,FEMUR_UP_LEG_3 );
  delay(DELAY_TIME);
  pwm.setPWM(5, 0,COXA_DEFAULT_LEG_3 );
  delay(DELAY_TIME);
  pwm.setPWM(6, 0,FEMUR_DEFAULT_LEG_3 );
  delay(DELAY_TIME);
  pwm.setPWM(8, 0,TIBIA_DEFAULT_LEG_3 );
  delay(DELAY_TIME);
  
  //FORWARD TOLKEN LEG
  //sweet_setPWM(10, 0,FEMUR_UP_LEG_4);
  delay(DELAY_TIME);
  pwm.setPWM(9, 0,FORWARD_COXA_1_LEG_4 );
  //pwm.setPWM(9, 0,COXA_DEFAULT_LEG_4 );
  delay(DELAY_TIME);
  pwm.setPWM(10, 0,FEMUR_DEFAULT_LEG_4 );
  delay(DELAY_TIME);
  pwm.setPWM(12, 0,TIBIA_DEFAULT_LEG_4 );
  delay(DELAY_TIME);

}

void one_step_forward(){
/*
 * De acordo com a imagem proposta do movimento, apresentado em trabalhos anteriores
 * ele executara cada passo para frente de acordo com uma sequencia pre definida de movimentos
 * a imagem se encontra na pasta deste codigo
 */

 //levanta perna A e coloca no local do primeiro movimento
  sweet_setPWM(FEMUR_LEG_1 , 0,FEMUR_UP_LEG_1);
  adjust_tibia_pos(TIBIA_LEG_1 );
  sweet_setPWM(COXA_LEG_1 , 0,FORWARD_COXA_2_LEG_1);
  sweet_setPWM(FEMUR_LEG_1 , 0,FEMUR_DEFAULT_LEG_1);
  sweet_setPWM(FEMUR_LEG_4 , 0,FEMUR_UP_LEG_4);
  adjust_tibia_pos(TIBIA_LEG_4 );
  //coloca perna B e coloca no local do segundo movimento
  quick_setPWM(COXA_LEG_4 , 0,COXA_DEFAULT_LEG_4);
  sweet_setPWM(FEMUR_LEG_4 , 0,FEMUR_DEFAULT_LEG_4);

  //mexe coxa de A e C no 
  quick_setPWM(COXA_LEG_3 , 0,FORWARD_COXA_3_LEG_3);
  quick_setPWM(COXA_LEG_1 , 0,COXA_DEFAULT_LEG_1);

  //mexe coxa de D
  sweet_setPWM(FEMUR_LEG_2 , 0,FEMUR_UP_LEG_2);
  adjust_tibia_pos(TIBIA_LEG_2 );
  quick_setPWM(COXA_LEG_2 , 0,FORWARD_COXA_4_LEG_2);
  sweet_setPWM(FEMUR_LEG_2 , 0,FEMUR_DEFAULT_LEG_2);
  //levanta C e vai ate default de C
  sweet_setPWM(FEMUR_LEG_3 , 0,FEMUR_UP_LEG_3);
  adjust_tibia_pos(TIBIA_LEG_3 );
  sweet_setPWM(COXA_LEG_3 , 0,COXA_DEFAULT_LEG_3 );
  sweet_setPWM(FEMUR_LEG_3 , 0,FEMUR_DEFAULT_LEG_3);

  //mexe coxa de B e D 
  quick_setPWM(COXA_LEG_4 , 0,FORWARD_COXA_1_LEG_4);
  quick_setPWM(COXA_LEG_2 , 0,COXA_DEFAULT_LEG_2);
}

void one_step_right(){

  sweet_setPWM(FEMUR_LEG_2 , 0,FEMUR_UP_LEG_2);
  adjust_tibia_pos(TIBIA_LEG_2 );
  sweet_setPWM(COXA_LEG_2 , 0,FORWARD_COXA_2_LEG_2);
  sweet_setPWM(FEMUR_LEG_2 , 0,FEMUR_DEFAULT_LEG_2);
  sweet_setPWM(FEMUR_LEG_1 , 0,FEMUR_UP_LEG_1);
  adjust_tibia_pos(TIBIA_LEG_1);
  quick_setPWM(COXA_LEG_1 , 0,COXA_DEFAULT_LEG_1);
  sweet_setPWM(FEMUR_LEG_1 , 0,FEMUR_DEFAULT_LEG_1);

  quick_setPWM(COXA_LEG_4 , 0,FORWARD_COXA_3_LEG_4);
  quick_setPWM(COXA_LEG_2 , 0,COXA_DEFAULT_LEG_2);

  sweet_setPWM(FEMUR_LEG_3 , 0,FEMUR_UP_LEG_3);
  adjust_tibia_pos(TIBIA_LEG_3);
  quick_setPWM(COXA_LEG_3 , 0,FORWARD_COXA_4_LEG_3);
  sweet_setPWM(FEMUR_LEG_3 , 0,FEMUR_DEFAULT_LEG_3);
  sweet_setPWM(FEMUR_LEG_4 , 0,FEMUR_UP_LEG_4);
  adjust_tibia_pos(TIBIA_LEG_4);
  sweet_setPWM(COXA_LEG_4 , 0,COXA_DEFAULT_LEG_4 );
  sweet_setPWM(FEMUR_LEG_4 , 0,FEMUR_DEFAULT_LEG_4);

  quick_setPWM(COXA_LEG_1 , 0,FORWARD_COXA_1_LEG_1);
  quick_setPWM(COXA_LEG_3 , 0,COXA_DEFAULT_LEG_3);
}

void one_step_back(){

  sweet_setPWM(FEMUR_LEG_3 , 0,FEMUR_UP_LEG_3);
  adjust_tibia_pos(TIBIA_LEG_3);
  sweet_setPWM(COXA_LEG_3 , 0,FORWARD_COXA_2_LEG_3);
  sweet_setPWM(FEMUR_LEG_3 , 0,FEMUR_DEFAULT_LEG_3);
  sweet_setPWM(FEMUR_LEG_2 , 0,FEMUR_UP_LEG_2);
  adjust_tibia_pos(TIBIA_LEG_2);
  quick_setPWM(COXA_LEG_2 , 0,COXA_DEFAULT_LEG_2);
  sweet_setPWM(FEMUR_LEG_2 , 0,FEMUR_DEFAULT_LEG_2);

  quick_setPWM(COXA_LEG_1 , 0,FORWARD_COXA_3_LEG_1);
  quick_setPWM(COXA_LEG_3 , 0,COXA_DEFAULT_LEG_3);

  sweet_setPWM(FEMUR_LEG_4, 0,FEMUR_UP_LEG_4);
  adjust_tibia_pos(TIBIA_LEG_4);
  quick_setPWM(COXA_LEG_4 , 0,FORWARD_COXA_4_LEG_4);
  sweet_setPWM(FEMUR_LEG_4 , 0,FEMUR_DEFAULT_LEG_4);
  sweet_setPWM(FEMUR_LEG_1 , 0,FEMUR_UP_LEG_1);
  adjust_tibia_pos(TIBIA_LEG_1);
  sweet_setPWM(COXA_LEG_1 , 0,COXA_DEFAULT_LEG_1 );
  sweet_setPWM(FEMUR_LEG_1 , 0,FEMUR_DEFAULT_LEG_1);

  quick_setPWM(COXA_LEG_2 , 0,FORWARD_COXA_1_LEG_2);
  quick_setPWM(COXA_LEG_4 , 0,COXA_DEFAULT_LEG_4);
}

void one_step_left(){

  sweet_setPWM(FEMUR_LEG_4 , 0,FEMUR_UP_LEG_4);
  adjust_tibia_pos(TIBIA_LEG_4);
  sweet_setPWM(COXA_LEG_4 , 0,FORWARD_COXA_2_LEG_4);
  sweet_setPWM(FEMUR_LEG_4 , 0,FEMUR_DEFAULT_LEG_4);
  sweet_setPWM(FEMUR_LEG_3 , 0,FEMUR_UP_LEG_3);
  adjust_tibia_pos(TIBIA_LEG_3);
  quick_setPWM(COXA_LEG_3 , 0,COXA_DEFAULT_LEG_3);
  sweet_setPWM(FEMUR_LEG_3 , 0,FEMUR_DEFAULT_LEG_3);

  quick_setPWM(COXA_LEG_2 , 0,FORWARD_COXA_3_LEG_2);
  quick_setPWM(COXA_LEG_4 , 0,COXA_DEFAULT_LEG_4);

  sweet_setPWM(FEMUR_LEG_1, 0,FEMUR_UP_LEG_1);
  adjust_tibia_pos(TIBIA_LEG_1);
  quick_setPWM(COXA_LEG_1 , 0,FORWARD_COXA_4_LEG_1);
  sweet_setPWM(FEMUR_LEG_1 , 0,FEMUR_DEFAULT_LEG_1);
  sweet_setPWM(FEMUR_LEG_2 , 0,FEMUR_UP_LEG_2);
  adjust_tibia_pos(TIBIA_LEG_2);
  sweet_setPWM(COXA_LEG_2 , 0,COXA_DEFAULT_LEG_2 );
  sweet_setPWM(FEMUR_LEG_2 , 0,FEMUR_DEFAULT_LEG_2);

  quick_setPWM(COXA_LEG_3 , 0,FORWARD_COXA_1_LEG_3);
  quick_setPWM(COXA_LEG_1 , 0,COXA_DEFAULT_LEG_1);
}

void one_leg_up_test(){

  sweet_setPWM(1, 0,FEMUR_UP_LEG_1 );
  delay(DELAY_TIME);
  sweet_setPWM(1, 0,FEMUR_DEFAULT_LEG_1 );
  delay(DELAY_TIME);
  
}


void setup() {
  //Serial.begin(9600);
  pwm.begin();
  delay(10);
  pwm.setPWMFreq(60);  
  new_max = map(MAX_ANGLE, 0, 180, SERVOMIN, SERVOMAX);
  new_min = map(MIN_ANGLE, 0, 180, SERVOMIN, SERVOMAX);
  set_initial();
  delay(10);
}

void loop() {

  one_step_forward();
  //one_step_back();
  //one_step_right();
  //one_step_left();
}
