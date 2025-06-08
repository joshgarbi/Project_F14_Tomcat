#define DCSBIOS_IRQ_SERIAL

#include "DcsBios.h"

int HCU_Pwr_rst_Pin = 2;

DcsBios::ActionButton rioHcuPwResetToggle("RIO_HCU_PW_RESET", "TOGGLE", HCU_Pwr_rst_Pin);

void setup() {
    DcsBios::setup();
}

void loop() {
    DcsBios::loop();
}