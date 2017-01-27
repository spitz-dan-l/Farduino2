#include "MeOrion.h"

struct Instruction {
  int8_t x_motor;
  int8_t y_motor;
  int8_t servo_1;
  int8_t servo_2;
  int8_t pump_motor;
};

MeDCMotor motor_9(9); // the pump motor.

#define PUMP_ON 255
#define PUMP_OFF 0

Servo servo_3_1; // poker/seeder toggle servo
Servo servo_3_2; // tray toggle servo
MePort port_3(3);

#define POKER_ENABLED_ANGLE 178
#define SEEDER_ENABLED_ANGLE 80

#define TRAY_IN_ANGLE 20
#define TRAY_OUT_ANGLE 135

void setup() {
  Serial.begin(9600);

  servo_3_1.attach(port_3.pin1());
  servo_3_2.attach(port_3.pin2());
  
  servo_3_1.write(178); //position for screw down
//  stepper1.setMaxSpeed(1000);
//  stepper1.setAcceleration(20000);
//  stepper2.setMaxSpeed(1000);
//  stepper2.setAcceleration(20000);
}

void loop() {
  // put your main code here, to run repeatedly:
  struct Instruction msg;
  getMsg(&msg);
  processMsg(&msg);
//  stepper1.run();
//  stepper2.run();
}

void processMsg(struct Instruction *i) {
  control_servo_1(i);
  control_servo_2(i);
  control_pump_motor(i);

//  stepper1.move(mi.xMotor * 100);
//  stepper2.move(mi.yMotor * 100);
}

void control_servo_1(struct Instruction *i){
  if (i->servo_1 == 1){
    servo_3_1.write(POKER_ENABLED_ANGLE);
  } else if (i->servo_1 == 2){
    servo_3_1.write(SEEDER_ENABLED_ANGLE);
  }
}

void control_servo_2(struct Instruction *i){
  if (i->servo_2 == 1){
    servo_3_2.write(TRAY_OUT_ANGLE);
  } else if (i->servo_2 == 2){
    servo_3_2.write(TRAY_IN_ANGLE);
  }
}

void control_pump_motor(struct Instruction *i){
  if (i->pump_motor == 2){
    motor_9.run(PUMP_OFF);
  } else if (i->pump_motor == 1){
    motor_9.run(PUMP_ON);
  }
}

void getMsg(struct Instruction *mi){

  uint8_t buffer[5];
  if (Serial.available() < 5){
    return;
  }

  for (int i=0; i < 5; i++){
    buffer[i] = Serial.read();
  }
  
  mi->x_motor = (int) buffer[0];
  mi->y_motor = (int) buffer[1];
  mi->servo_1 = (int) buffer[2];
  mi->servo_2 = (int) buffer[3];
  mi->pump_motor = (int) buffer[4];
  
  Serial.print("received message ");
  Serial.print((int) buffer[0]);
  Serial.print(" ");
  Serial.print((int) buffer[1]);
  Serial.print(" ");
  Serial.print((int) buffer[2]);
  Serial.print(" ");
  Serial.print((int) buffer[3]);
  Serial.print(" ");
  Serial.println((int) buffer[4]);
}