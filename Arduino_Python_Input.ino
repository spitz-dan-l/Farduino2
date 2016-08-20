#include "MeOrion.h"

struct MotorInstruction {
  int xMotor;
  int yMotor;
};

MeStepper stepper1(PORT_1);
MeStepper stepper2(PORT_2);

void setup() {
  Serial.begin(9600);
  stepper1.setMaxSpeed(1000);
  stepper1.setAcceleration(20000);
  stepper2.setMaxSpeed(1000);
  stepper2.setAcceleration(20000);
}

void loop() {
      struct MotorInstruction msg;
      if(Serial.available()){
          msg = getMsg();
          processMsg(msg);
      }
      stepper1.run();
      stepper2.run();
}

void processMsg(struct MotorInstruction mi) {
  stepper1.move(mi.xMotor * 100);
  stepper2.move(mi.yMotor * 100);
}

struct MotorInstruction getMsg(){
  struct MotorInstruction mi;
  int i;
  char *buffer;
  unsigned char msgSize = Serial.read();
  buffer = (char *) malloc(sizeof(char) * msgSize);

  for (i = 0; i < msgSize; i++){
    buffer[i] = Serial.read(); 
  }

  mi.xMotor = (int) buffer[0];
  mi.yMotor = (int) buffer[1];
  
  Serial.printf("received %d %d\n", buffer[0], buffer[1])
  
  free(buffer);
  return mi;
}
