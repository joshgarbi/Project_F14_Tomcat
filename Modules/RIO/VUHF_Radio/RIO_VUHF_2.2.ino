// Created: 2025/06/25 12:24:41
// Last modified: 2025/06/25 17:55:30

#define DCSBIOS_IRQ_SERIAL
#include <max7219.h>
#include "DcsBios.h"

//Requires arduino mega

// CLK -> D10
// CS -> D11
// DIN -> D12

const int SquelchPin;
const int FmAmPin;

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
const int APin = 35;
const int BPin = 37;
const int apin = 39; 
const int bpin = 41;

//potentiometer pins
const int brightnessPin = A1;
const int volumePin = A0;

//other necessary variables
bool preset = 1;
int mappedBrightness = -1;

MAX7219 display_1(8,9,10);
MAX7219 display_2(11,12,13);


//custom function to display the frequency on the 7-segment display
void display(String text, int dec) {
    display_1.DisplayChar(0, text[0], 0);
    display_1.DisplayChar(1, text[1], 0);
    display_1.DisplayChar(2, text[2], dec);
    display_1.DisplayChar(3, text[3], 0);
    display_1.DisplayChar(4, text[4], 0);
    display_1.DisplayChar(5, text[5], 0);

    display_2.DisplayChar(0, text[0], 0);
    display_2.DisplayChar(1, text[1], 0);
    display_2.DisplayChar(2, text[2], dec);
    display_2.DisplayChar(3, text[3], 0);
    display_2.DisplayChar(4, text[4], 0);
    display_2.DisplayChar(5, text[5], 0);
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
DcsBios::PotentiometerEWMA<POLL_EVERY_TIME, 2048, 10> rioVuhfBrightness("RIO_VUHF_BRIGHTNESS", brightnessPin);
DcsBios::PotentiometerEWMA<POLL_EVERY_TIME, 128, 10> rioVuhfVol("RIO_VUHF_VOL", volumePin);

//freq adjustment
DcsBios::Switch3Pos rioVuhf025Dial("RIO_VUHF_025_DIAL", freq025PinUp, freq025PinDown);
DcsBios::Switch3Pos rioVuhf01Dial("RIO_VUHF_01_DIAL", freq01PinUp, freq01PinDown);
DcsBios::Switch3Pos rioVuhf1Dial("RIO_VUHF_1_DIAL", freq1PinDown, freq1PinUp);
DcsBios::Switch3Pos rioVuhf110Dial("RIO_VUHF_110_DIAL", freq110PinDown, freq110PinUp);

//callback function to handle changes in the brightness setting and output the brightness
void onRioVuhfBrightnessChange(unsigned int newValue) {
  static unsigned int lastValue = -1;
  if (newValue != lastValue) {       
    lastValue = newValue;
    mappedBrightness = map(newValue, 0, 65535, 0, 15) - 1;
    if (mappedBrightness != -1) {
      display_1.MAX7219_ShutdownStop();
      display_1.MAX7219_SetBrightness(mappedBrightness);
    } else {
      display_1.MAX7219_ShutdownStart();
    }
  }
}
DcsBios::IntegerBuffer rioVuhfBrightnessBuffer(F_14_RIO_VUHF_BRIGHTNESS, onRioVuhfBrightnessChange);

void setup() {
  DcsBios::setup();
  display_1.Clear();
  display_1.Begin();
  display_2.Clear();
  display_2.Begin();
}

void loop() {
  DcsBios::loop();
}
 