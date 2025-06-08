#define DCSBIOS_IRQ_SERIAL

#include "DcsBios.h"

int UCU_DDD_Pin = 2; // SET TO DESIRED PIN NUMBER

DcsBios::ActionButton rioHcuDddToggle("RIO_HCU_DDD", "TOGGLE", UCU_DDD_Pin);

void setup() {
    DcsBios::setup();
}

void loop() {
    DcsBios::loop();
}