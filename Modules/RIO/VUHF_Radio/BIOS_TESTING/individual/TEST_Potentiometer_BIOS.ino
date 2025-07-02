#define DCSBIOS_DEFAULT_SERIAL

#include "DcsBios.h"



DCSBios::Potentiometer rioVuhfVolume("RIO_VUHF_VOLUME", A0);
DcsBios::Potentiometer rioVuhfBrightness("RIO_VUHF_BRIGHTNESS", A1);

void setup() {
    DcsBios::setup();
}

void loop() {
    DcsBios::loop();
}
