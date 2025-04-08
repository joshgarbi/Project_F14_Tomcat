#define DCSBIOS_DEFAULT_SERIAL

#include "DcsBios.h"

DcsBios::Switch3Pos rioVuhf025Dial("RIO_VUHF_025_DIAL", 2, 3);

void setup() {
    DcsBios::setup();
}

void loop() {
    DcsBios::loop();
}
