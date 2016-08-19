#include "MeOrion.h"

int msg = 0;
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

      if(Serial.available()){
          msg = getMsg();
          switch(msg)
          {
            case 1:
              stepper1.move(100);
              break;
            case 2:
              stepper1.move(-100);
              break;
            case 3:
              stepper2.move(-100);
              break;
            case 4:
              stepper2.move(100);
              break;
            case 0:
              stepper1.move(0);
              stepper2.move(0);
              break;
          }
      }
      stepper1.run();
      stepper2.run();

}

int getMsg(){
  float inMsg = Serial.read();
  int value1 = (int) inMsg - '0';
  String value1Str = String(value1);

  inMsg = Serial.read();
  int value2 = (int) inMsg - '0';
  String value2Str = String(value2);

  String valueFinal = value1Str + value2Str;
  return valueFinal.toInt();
}

