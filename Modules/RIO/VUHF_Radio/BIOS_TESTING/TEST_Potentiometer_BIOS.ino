#define DCSBIOS_DEFAULT_SERIAL

#include "DcsBios.h"




DcsBios::Potentiometer rioVuhfBrightness("RIO_VUHF_BRIGHTNESS", A1);

void onRioVuhfBrightnessChange(unsigned int newValue) {
    int mappedBrightness = map(brightness, 0, 65535, 0, 15);
    max7219.MAX7219_SetBrightness(mappedBrightness);
}
DcsBios::IntegerBuffer rioVuhfBrightnessBuffer(F_14_RIO_VUHF_BRIGHTNESS, onRioVuhfBrightnessChange);

void setup() {
    DcsBios::setup();
}

void loop() {
    DcsBios::loop();
}
