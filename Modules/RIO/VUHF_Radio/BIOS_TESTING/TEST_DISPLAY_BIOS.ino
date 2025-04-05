/*
  Tell DCS-BIOS to use a serial connection and use the default Arduino Serial
  library. This will work on the vast majority of Arduino-compatible boards,
  but you can get corrupted data if you have too many or too slow outputs
  (e.g. when you have multiple character displays), because the receive
  buffer can fill up if the sketch spends too much time updating them.
  
  If you can, use the IRQ Serial connection instead.
*/
#define DCSBIOS_DEFAULT_SERIAL

#include "DcsBios.h"
#include <max7219.h>

MAX7219 max7219;

void display(String text, int dec) {
    max7219.DisplayChar(0, text[0], 0);
    max7219.DisplayChar(1, text[1], 0);
    max7219.DisplayChar(2, text[2], dec);
    max7219.DisplayChar(3, text[3], 0);
    max7219.DisplayChar(4, text[4], 0);
    max7219.DisplayChar(5, text[5], 0);
}

void onRioLightIntentConsoleChange(unsigned int newValue) {
    display(String(newValue), 1);
}
DcsBios::IntegerBuffer rioLightIntentConsoleBuffer(0x1220, 0xf000, 12, onRioLightIntentConsoleChange);

void setup() {
    DcsBios::setup();
    max7219.Clear();
    max7219.Begin();
}

void loop() {
    DcsBios::loop();
}

