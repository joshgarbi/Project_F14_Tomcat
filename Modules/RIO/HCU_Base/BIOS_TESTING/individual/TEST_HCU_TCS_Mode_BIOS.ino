#define DCSBIOS_IRQ_SERIAL

#include "DcsBios.h"

int HCU_TCS_tggl_Pin; // SET TO DESIRED PIN NUMBER

DcsBios::ActionButton rioHcuTcsToggle("RIO_HCU_TCS", "TOGGLE", HCU_TCS_tggl_Pin);

void setup() {
    DcsBios::setup();
}

void loop() {
    DcsBios::loop();
}