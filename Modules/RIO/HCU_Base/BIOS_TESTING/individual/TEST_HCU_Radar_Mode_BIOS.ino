#define DCSBIOS_IRQ_SERIAL

#include "DcsBios.h"

int HCU_rdr_tggl_Pin = 2; // SET TO DESIRED PIN NUMBER

DcsBios::ActionButton rioHcuRadarToggle("RIO_HCU_RADAR", "TOGGLE", HCU_rdr_tggl_Pin);

void setup() {
    DcsBios::setup();
}

void loop() {
    DcsBios::loop();
}