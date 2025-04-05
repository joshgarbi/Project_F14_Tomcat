#define DCSBIOS_DEFAULT_SERIAL
#include <max7219.h>
#include "DcsBios.h"

// CLK -> D10
// CS -> D11
// DIN -> D12


const int SquelchPin = 8;
const int FmAmPin = 9;

const int APin = 4;
const int BPin = 5;
const int apin = 2; 
const int bpin = 3;

String freq;
String preset;
bool preset = false;

MAX7219 max7219;

void display(String text, int dec) {
    max7219.DisplayChar(0, text[0], 0);
    max7219.DisplayChar(1, text[1], 0);
    max7219.DisplayChar(2, text[2], dec);
    max7219.DisplayChar(3, text[3], 0);
    max7219.DisplayChar(4, text[4], 0);
    max7219.DisplayChar(5, text[5], 0);
}

void onRioVuhfDispChange(char* newValue) {
  freq = String(newValue);
  freq.remove(3, 1);
  if (preset){
    display(freq, 0);
  } else {
    display(freq, 1);
  }
}
DcsBios::StringBuffer<7> rioVuhfDispBuffer(0x14fc, onRioVuhfDispChange);

void onRioVuhfFreqModeChange(unsigned int newValue) {
  if (newValue == 3) {
    preset = true;
  } else {
    preset = false;
  }
}
DcsBios::IntegerBuffer rioVuhfFreqModeBuffer(0x124a, onRioVuhfFreqModeChange);

DcsBios::Switch2Pos rioVuhfSquelch("RIO_VUHF_SQUELCH", SquelchPin);

DcsBios::Switch2Pos rioVuhfFmAm("RIO_VUHF_FM_AM", FmAmPin);

DcsBios::RotaryEncoderT<POLL_EVERY_TIME, DcsBios::TWO_STEPS_PER_DETENT> rioVuhfPresets("RIO_VUHF_PRESETS", "DEC", "INC", APin, BPin);
DcsBios::RotaryEncoderT<POLL_EVERY_TIME, DcsBios::TWO_STEPS_PER_DETENT> rioVuhfFreqMode("RIO_VUHF_FREQ_MODE", "DEC", "INC", apin, bpin);

void setup() {
  DcsBios::setup();
  max7219.Clear();
  max7219.Begin();
}

void loop() {
  DcsBios::loop();
}

