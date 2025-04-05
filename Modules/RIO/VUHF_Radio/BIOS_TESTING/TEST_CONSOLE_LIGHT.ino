#define DCSBIOS_DEFAULT_SERIAL

#include "DcsBios.h"

int brighness = 0; 
const double maps[9] = {0.0, 31.875, 63.75, 95.625, 127.5, 159.375, 191.25, 223.125, 255.0};

void onRioLightIntentConsoleChange(unsigned int newValue) {
    brighness = maps[newValue];
}
DcsBios::IntegerBuffer rioLightIntentConsoleBuffer(0x1220, 0xf000, 12, onRioLightIntentConsoleChange);

void setup() {
    DcsBios::setup();
    pinMode(9, OUTPUT);
}

void loop() {
    DcsBios::loop();
    analogWrite(9, brighness);
}

