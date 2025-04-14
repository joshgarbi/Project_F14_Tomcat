#define DCSBIOS_IRQ_SERIAL
#include <max7219.h>
#include "DcsBios.h"

// CLK -> D10
// CS -> D11
// DIN -> D12

String freq;
int brightness;

MAX7219 max7219;

void onRioVuhfDispChange(char* newValue) {
    freq = String(newValue);
    freq.remove(3, 1);
}
DcsBios::StringBuffer<7> rioVuhfDispBuffer(0x14fc, onRioVuhfDispChange);

void onRioVuhfBrightnessChange(unsigned int newValue) {
    brightness = newValue;
}
DcsBios::IntegerBuffer rioVuhfBrightnessBuffer(0x1252, 0xffff, 0, onRioVuhfBrightnessChange);

void display(String text, int dec, int brightness) {
    int localBrightness = map(brightness, 0, 65535, 0, 15);
    if (localBrightness != 0) {
        max7219.MAX7219_SetBrightness(localBrightness);
        max7219.DisplayChar(0, text[0], 0);
        max7219.DisplayChar(1, text[1], 0);
        max7219.DisplayChar(2, text[2], dec);
        max7219.DisplayChar(3, text[3], 0);
        max7219.DisplayChar(4, text[4], 0);
        max7219.DisplayChar(5, text[5], 0);
    } else if (localBrightness == 0) {
        max7219.Clear();
        max7219.Begin();
    }
}

void setup() {
    max7219.Clear();
    max7219.Begin();
    DcsBios::setup();
}
  
void loop() {
    DcsBios::loop();
    display(freq, 1, brightness);
}
  