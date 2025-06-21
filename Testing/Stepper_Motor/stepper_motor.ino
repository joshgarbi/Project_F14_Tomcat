#include <Stepper.h>                    //load library

#define STEPS 64                    //establish number of steps

Stepper stepper1(STEPS, 8,9,10,11);
Stepper stepper2(STEPS, 2,3,4,5);

void setup() {
  // put your setup code here, to run once:

stepper1.setSpeed(32);
stepper2.setSpeed(32/60);                   //set speed of motor

}

void loop() {
  // put your main code here, to run repeatedly:

stepper1.step(1);                      //tell stepper motor to step
stepper2.step(1);

}