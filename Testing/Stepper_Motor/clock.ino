#include <Stepper.h>                    //load library

#define STEPS 64                    //establish number of steps

Stepper stepper1(STEPS, 8,9,10,11);

void setup() {
  // put your setup code here, to run once:
  // For 28BYJ-48: set speeds in RPM (typically 5-15 for this motor)
  stepper1.setSpeed(32);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Step through a full rotation (64 steps * 64 gear ratio = 4096 steps)
  stepper1.step(64);
}