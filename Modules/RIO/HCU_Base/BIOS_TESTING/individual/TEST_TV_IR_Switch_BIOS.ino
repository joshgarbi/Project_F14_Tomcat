#define DCSBIOS_IRQ_SERIAL

#include "DcsBios.h"

enum HCU_TV_IR_Switch_Pin {
    HCU_TVIR_PIN_A, // SET TO DESIRED PIN NUMBER
    HCU_TVIR_PIN_B  // SET TO DESIRED PIN NUMBER
};

DcsBios::Switch3Pos rioHcuTvirSw("RIO_HCU_TVIR_SW", HCU_TVIR_PIN_A, HCU_TVIR_PIN_B);

void setup() {
    DcsBios::setup();
}

void loop() {
    DcsBios::loop();
}