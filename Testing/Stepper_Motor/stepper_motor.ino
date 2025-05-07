#include <Stepper.h>                    //load library

#define STEPS 100                       //establish number of steps

Stepper stepper(STEPS, 8,9,10,11);

void setup() {
  // put your setup code here, to run once:

stepper.setSpeed(30);                   //set speed of motor

}

void loop() {
  // put your main code here, to run repeatedly:

stepper.step(150);                      //tell stepper motor to step

}