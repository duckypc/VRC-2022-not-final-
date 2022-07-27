#include <stdio.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>


#define MIN_PWM 0
#define MAX_PWM 4095

//#define SDA 3
//#define SCL 0
// PWM channels of pca9685 0-16
#define PWM_CHANNEL1 8
#define PWM_CHANNEL2 9
#define PWM_CHANNEL3 10
#define PWM_CHANNEL4 11
#define PWM_CHANNEL5 12
#define PWM_CHANNEL6 13
#define PWM_CHANNEL7 14
#define PWM_CHANNEL8 15


//line tracker GPIO
#define SEN_1_PIN 39
#define SEN_2_PIN 36
#define SEN_3_PIN 25
#define SEN_4_PIN 32


int counter = 0;
#define ON  4095
#define OFF  0
#define off 4096

#define SERVO_3_PIN 3 // pusher
#define SERVO_4_PIN 6 // holder


Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();



#define SERVOMIN  150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // This is the 'maximum' pulse length count (out of 4096)
#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

void quayservo(char n,int a, int b){
  pwm.setPWM(n, a, b);
}

void setPWMMotors(int c1, int c2, int c3, int c4)
{
  // setPWM(channel, on_duty_cycle, off_duty_cycle)
  /*********
  Serial.print(c1);
  Serial.print("\t");
  Serial.print(c2);
  Serial.print("\t");
  Serial.print(c3);
  Serial.print("\t");
  Serial.print(c4);
  Serial.println();
*/

/*
  pwm.setPWM(PWM_CHANNEL1, c1 , MAX_PWM - c1);
  pwm.setPWM(PWM_CHANNEL2, c2, MAX_PWM - c2);
  pwm.setPWM(PWM_CHANNEL3, c3, MAX_PWM - c3);
  pwm.setPWM(PWM_CHANNEL4, c4, MAX_PWM - c4);
*/

  pwm.setPWM(PWM_CHANNEL1, 0, c1);
  pwm.setPWM(PWM_CHANNEL2, 0, c2);
  pwm.setPWM(PWM_CHANNEL3, 0, c3);
  pwm.setPWM(PWM_CHANNEL4, 0, c4);
}

//----------------------------------------------------------------------------------------------------
void rongroc(int n) {
  pwm.setPWM(PWM_CHANNEL5, n, MAX_PWM - n);
  pwm.setPWM(PWM_CHANNEL6, MAX_PWM - n,  n);

}
//----------------------------------------------------------------------------------------------------
void collector(int n){
  pwm.setPWM(PWM_CHANNEL7, n, MAX_PWM - n);
  pwm.setPWM(PWM_CHANNEL8,  MAX_PWM - n,  n);
}
// ----------------------------------------------------------------------------------------------------

// set_up do line - ham chay dong co
int trai (int c1, int c2){
  pwm.setPWM(PWM_CHANNEL1, 0, c1);
  pwm.setPWM(PWM_CHANNEL2, 0, c2);
}
int phai (int c1, int c2){
  pwm.setPWM(PWM_CHANNEL3, 0, c1);
  pwm.setPWM(PWM_CHANNEL4, 0, c2);
}


// line tracker:
void doline (){
 /*** while (1 > 0){
  Serial.println(digitalRead(SEN_1_PIN));
  Serial.println(digitalRead(SEN_2_PIN));
  Serial.println(digitalRead(SEN_3_PIN));
  Serial.println(digitalRead(SEN_4_PIN));
  Serial.println("_____________");
  delay(2000);
  }
  **/
  counter = 0;
  // den tat la 1 
  while ((digitalRead(SEN_1_PIN) == 1) ||  (digitalRead(SEN_2_PIN) == 1) ||  (digitalRead(SEN_3_PIN) == 1) ||  (digitalRead(SEN_4_PIN) == 1)) {
    //runstraight
    phai (MAX_PWM/2, 0);
    Serial.println("chua vao line");
    trai (MAX_PWM/2,0);
    Serial.println("chua vao line");
  }
while (counter <= 3 ){
  Serial.println(counter);
  if ((digitalRead(SEN_1_PIN) == 0) ||  (digitalRead(SEN_2_PIN) == 0) ||  (digitalRead(SEN_3_PIN) == 0) ||  (digitalRead(SEN_4_PIN) == 0))  {
    
    if (counter == 2){
    rongroc(ON);
    delay(1000);
    rongroc(off);
    quayservo( SERVO_4_PIN, 0, 150);
    delay(500);
    quayservo( SERVO_4_PIN, 0, 410);
          delay(200);
    //runstraight 
    phai (0,MAX_PWM/2);
    Serial.println("thoat line");
    trai (0,MAX_PWM/2);
    Serial.println("thoat line");
    delay(2000);
     counter += 3;
    }
    else {
     phai (MAX_PWM/2, 0);
    trai (MAX_PWM/2,0);
    delay(500);
     while ((digitalRead(SEN_1_PIN) == 0) ||  (digitalRead(SEN_2_PIN) == 0) ||  (digitalRead(SEN_3_PIN) == 0) ||  (digitalRead(SEN_4_PIN) == 0)){
    //runstraight
    phai (MAX_PWM/2, 0);
    Serial.println("chuyen_line");
    trai (MAX_PWM/2,0);
    Serial.println("chuyen_line");
  }
    counter += 2;
    }
  }
  
  }

}

// end 



void initMotors()
{
  Wire.begin(); //SDA, SCL,400000);
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(1600);
  Wire.setClock(400000);

  setPWMMotors(0, 0, 0, 0);
}

// /**
//  * Set speed and direction for 2 motors
//  *
//  * @param left_motor_speed: speed with direction for left motor. Range from -1 to 1. 1: max speed forward, -1: max speed reverse
//  * @param right_motor_speed: speed with direction for right motor. Range from -1 to 1. 1: max speed forward, -1: max speed reverse
//  */
// void setSpeed(float left_motor_speed, float right_motor_speed) {

//   int c1 = 0, c2 = 0, c3 = 0, c4 = 0;

//   if (left_motor_speed > 0) {
//     c1 = max(MIN_PWM, min(int(abs(left_motor_speed) * MAX_PWM), MAX_PWM));
//   } else {
//     c2 = max(MIN_PWM, min(int(abs(left_motor_speed) * MAX_PWM), MAX_PWM));
//   }

//   if (right_motor_speed > 0) {
//     c3 = max(MIN_PWM, min(int(abs(right_motor_speed) * MAX_PWM), MAX_PWM));
//   } else {
//     c4 = max(MIN_PWM, min(int(abs(right_motor_speed) * MAX_PWM), MAX_PWM));
//   }

//   setPWMMotors(c1, c2, c3, c4);
// }
