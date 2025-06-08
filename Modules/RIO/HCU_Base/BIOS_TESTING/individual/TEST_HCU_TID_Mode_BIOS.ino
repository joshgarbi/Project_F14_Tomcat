#define DCSBIOS_IRQ_SERIAL

#include "DcsBios.h"

int HCU_TID_tggl_Pin = 2; // SET TO DESIRED PIN NUMBER

DcsBios::ActionButton rioHcuTidToggle("RIO_HCU_TID", "TOGGLE", HCU_TID_tggl_Pin);

void setup() {
    DcsBios::setup();
}

void loop() {
    DcsBios::loop();
}