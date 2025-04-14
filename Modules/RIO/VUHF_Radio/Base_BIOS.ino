#define DCSBIOS_IRQ_SERIAL
#include <max7219.h>
#include "DcsBios.h"

// CLK -> D10
// CS -> D11
// DIN -> D12

const int SquelchPin = 8;
const int FmAmPin = 9;

//concentric selector pins
const int APin = 4;
const int BPin = 5;
const int apin = 2; 
const int bpin = 3;

//potentiometer pins
const int brighnessPin = A1;
const int volumePin = A0;

String freq;
int brightness;

MAX7219 max7219;

DcsBios::Switch2Pos rioVuhfSquelch("RIO_VUHF_SQUELCH", SquelchPin);
DcsBios::Switch2Pos rioVuhfFmAm("RIO_VUHF_FM_AM", FmAmPin);

//concentric rotary encoders for frequency presets and mode selection
DcsBios::RotaryEncoderT<POLL_EVERY_TIME, DcsBios::TWO_STEPS_PER_DETENT> rioVuhfPresets("RIO_VUHF_PRESETS", "DEC", "INC", APin, BPin);
DcsBios::RotaryEncoderT<POLL_EVERY_TIME, DcsBios::TWO_STEPS_PER_DETENT> rioVuhfFreqMode("RIO_VUHF_FREQ_MODE", "DEC", "INC", apin, bpin);

//potentiometers for brightness and volume control
DcsBios::Potentiometer rioVuhfBrightness("RIO_VUHF_BRIGHTNESS", brighnessPin);
DcsBios::Potentiometer rioVuhfVol("RIO_VUHF_VOL", volumePin);

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
  