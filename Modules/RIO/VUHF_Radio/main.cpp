#include "max7219.h"

// Create MAX7219 object with custom pins
MAX7219 max7219(8, 9, 10); // Example: CLK=8, CS=9, DIN=10

void setup() {
    max7219.Begin();
    max7219.Clear();
    max7219.MAX7219_SetBrightness(5);
}

void loop() {
    max7219.DisplayChar(0, 'A', false);
    delay(1000);
    max7219.Clear();
    delay(1000);
}
