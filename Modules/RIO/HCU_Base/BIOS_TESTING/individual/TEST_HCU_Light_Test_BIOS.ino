#define DCSBIOS_IRQ_SERIAL

#include "DcsBios.h"

int HCU_Lght_Tst; // SET TO DESIRED PIN NUMBER

DcsBios::ActionButton rioHcuLightTestToggle("RIO_HCU_LIGHT_TEST", "TOGGLE", HCU_Light_Test);

void setup() {
    DcsBios::setup();
}

void loop() {
    DcsBios::loop();
}