// Created: 2025/04/08 12:24:41
// Last modified: 2025/04/13 22:38:27

#define DCSBIOS_IRQ_SERIAL
#include <max7219.h>
#include "DcsBios.h"

//Requires arduino mega

// CLK -> D10
// CS -> D11
// DIN -> D12

const int SquelchPin = 8;
const int FmAmPin = 9;

//freq pings
const int freq025PinUp = 22;
const int freq025PinDown = 23;
const int freq01PinDown = 24;
const int freq01PinUp = 25;
const int freq1PinUp = 26;
const int freq1PinDown = 27;
const int freq110PinUp = 28;
const int freq110PinDown = 29;

//concentric selector pins
const int APin = 4;
const int BPin = 5;
const int apin = 2; 
const int bpin = 3;

//potentiometer pins
const int brighnessPin = A1;
const int volumePin = A0;

//other necessary variables
bool preset = 1;
int mappedBrightness = -1;

MAX7219 max7219;

//custom function to display the frequency on the 7-segment display
void display(String text, int dec) {
    max7219.DisplayChar(0, text[0], 0);
    max7219.DisplayChar(1, text[1], 0);
    max7219.DisplayChar(2, text[2], dec);
    max7219.DisplayChar(3, text[3], 0);
    max7219.DisplayChar(4, text[4], 0);
    max7219.DisplayChar(5, text[5], 0);
}

//callback function to handle changes in the frequency display
void onRioVuhfDispChange(char* newValue) {
  String freq = String(newValue);
  freq.remove(3,1);
  display(freq, preset);
}
DcsBios::StringBuffer<7> rioVuhfDispBuffer(0x14fc, onRioVuhfDispChange);

//callback function to handle changes in the frequency mode
void onRioVuhfFreqModeChange(unsigned int newValue) {
  if (newValue == 3) {
    preset = 0;
  } else {
    preset = 1;
  }
}
DcsBios::IntegerBuffer rioVuhfFreqModeBuffer(0x124a, 0x0007, 0, onRioVuhfFreqModeChange);

//toggle switches located on either side of the frequency display
DcsBios::Switch2Pos rioVuhfSquelch("RIO_VUHF_SQUELCH", SquelchPin);
DcsBios::Switch2Pos rioVuhfFmAm("RIO_VUHF_FM_AM", FmAmPin);

//concentric rotary encoders for frequency presets and mode selection
DcsBios::RotaryEncoderT<POLL_EVERY_TIME, DcsBios::TWO_STEPS_PER_DETENT> rioVuhfPresets("RIO_VUHF_PRESETS", "DEC", "INC", APin, BPin);
DcsBios::RotaryEncoderT<POLL_EVERY_TIME, DcsBios::TWO_STEPS_PER_DETENT> rioVuhfFreqMode("RIO_VUHF_FREQ_MODE", "DEC", "INC", apin, bpin);

//potentiometers for brightness and volume control
DcsBios::PotentiometerEWMA<POLL_EVERY_TIME, 2048, 10> rioVuhfBrightness("RIO_VUHF_BRIGHTNESS", brighnessPin);
DcsBios::PotentiometerEWMA<POLL_EVERY_TIME, 128, 10> rioVuhfVol("RIO_VUHF_VOL", volumePin);

//freq adjustment
DcsBios::Switch3Pos rioVuhf025Dial("RIO_VUHF_025_DIAL", freq025PinUp, freq025PinDown);
DcsBios::Switch3Pos rioVuhf01Dial("RIO_VUHF_01_DIAL", freq01PinUp, freq01PinDown);
DcsBios::Switch3Pos rioVuhf1Dial("RIO_VUHF_1_DIAL", freq1PinDown, freq1PinUp);
DcsBios::Switch3Pos rioVuhf110Dial("RIO_VUHF_110_DIAL", freq110PinDown, freq110PinUp);

//callback function to handle changes in the brightness setting and output the brightness
void onRioVuhfBrightnessChange(unsigned int newValue) {
  static unsigned int lastValue = -1; // Cache the last value
  if (newValue != lastValue) {       // Only recompute if the value changes
    lastValue = newValue;
    mappedBrightness = map(newValue, 0, 65535, 0, 15) - 1;
    if (mappedBrightness != -1) {
      max7219.MAX7219_ShutdownStop();
      max7219.MAX7219_SetBrightness(mappedBrightness);
    } else {
      max7219.MAX7219_ShutdownStart();
    }
  }
}
DcsBios::IntegerBuffer rioVuhfBrightnessBuffer(F_14_RIO_VUHF_BRIGHTNESS, onRioVuhfBrightnessChange);

void setup() {
  DcsBios::setup();
  max7219.Clear();
  max7219.Begin();
}

void loop() {
  DcsBios::loop();
}
 