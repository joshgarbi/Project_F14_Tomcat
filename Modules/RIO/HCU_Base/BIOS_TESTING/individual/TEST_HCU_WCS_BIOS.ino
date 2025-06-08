#define DCSBIOS_IRQ_SERIAL

#include "DcsBios.h"

enum RIO_HCU_WCS_Pin {
    WCS_Pin_A, // SET TO DESIRED PIN NUMBER
    WCS_Pin_B  // SET TO DESIRED PIN NUMBER
};

DcsBios::Switch3Pos rioHcuWcs("RIO_HCU_WCS", WCS_Pin_A, WCS_Pin_B);

void setup() {
    DcsBios::setup();
}

void loop() {
    DcsBios::loop();
}