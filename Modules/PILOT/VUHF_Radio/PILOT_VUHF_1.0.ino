// Created: 2025/04/08 12:24:41
// Last modified: 2025/04/13 22:38:13

#define DCSBIOS_IRQ_SERIAL
#include <max7219.h>
#include "DcsBios.h"

// CLK -> D10
// CS -> D11
// DIN -> D12

const int channelSelectorPinA = 1;
const int channelSelectorPinB = 2;

const int freqModePin0 = 3;
const int freqModePin1 = 4;
const int freqModePin2 = 5;

const int functionPin0 = 6;
const int functionPin1 = 7;
const int functionPin2 = 8;
const int functionPin3 = 9;

const int loadPin = 13;
const int tonePin = 14;

const int squelchPin = 15;
const int readPin = 16;

const int volumePin = A0;
const int brightnessPin = A1;

const int freq025PinUp = 22;
const int freq025PinDown = 23;
const int freq01PinUp = 24;
const int freq01PinDown = 25;
const int freq1PinUp = 26;
const int freq1PinDown = 27;
const int freq100PinUp = 28;
const int freq100PinDown = 29;

MAX7219 max7219;

void display(String text, int dec) {
    max7219.DisplayChar(0, text[0], 0);
    max7219.DisplayChar(1, text[1], 0);
    max7219.DisplayChar(2, text[2], dec);
    max7219.DisplayChar(3, text[3], 0);
    max7219.DisplayChar(4, text[4], 0);
    max7219.DisplayChar(5, text[5], 0);
}

void onPltUhfRemoteDispChange(char* newValue) {
  String freq = String(newValue);
  freq.remove(3,1);
  display(freq, preset);
}
DcsBios::StringBuffer<7> pltUhfRemoteDispBuffer(0x1472, onPltUhfRemoteDispChange);

void onPltUhf1FreqModeChange(unsigned int newValue) {
  if (newValue == 2) {
    preset = 0;
  } else {
    preset = 1;
  }
}
DcsBios::IntegerBuffer pltUhf1FreqModeBuffer(F_14_PLT_UHF1_FREQ_MODE, onPltUhf1FreqModeChange);

void onPltUhf1BrightnessChange(unsigned int newValue) {
  static unsigned int lastValue = -1;
  if (newValue != lastValue) {       
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
DcsBios::IntegerBuffer pltUhf1BrightnessBuffer(F_14_PLT_UHF1_BRIGHTNESS, onPltUhf1BrightnessChange);

DcsBios::RotaryEncoder pltUhf1Presets("PLT_UHF1_PRESETS", "DEC", "INC", channelSelectorPinA, channelSelectorPinB);

const byte pltUhf1FreqModePins[3] = {freqModePin0, freqModePin1, freqModePin2};
DcsBios::SwitchMultiPos pltUhf1FreqMode("PLT_UHF1_FREQ_MODE", pltUhf1FreqModePins, 3);

const byte pltUhf1FunctionPins[4] = {functionPin0, functionPin1, functionPin2, functionPin3};
DcsBios::SwitchMultiPos pltUhf1Function("PLT_UHF1_FUNCTION", pltUhf1FunctionPins, 4);

DcsBios::Switch2Pos pltUhf1Load("PLT_UHF1_LOAD", loadPin);

DcsBios::Switch2Pos pltUhf1Tone("PLT_UHF1_TONE", tonePin);

DcsBios::Switch2Pos pltUhf1Squelch("PLT_UHF1_SQUELCH", squelchPin);

DcsBios::Switch2Pos pltUhf1ShowPresetFreq("PLT_UHF1_SHOW_PRESET_FREQ", readPin);

DcsBios::PotentiometerEWMA<POLL_EVERY_TIME, 128, 10> pltUhf1Brightness("PLT_UHF1_BRIGHTNESS", brightnessPin);

DcsBios::PotentiometerEWMA<POLL_EVERY_TIME, 128, 10> pltUhf1Vol("PLT_UHF1_VOL", volumePin);

DcsBios::Switch3Pos pltUhf1025Dial("PLT_UHF1_025_DIAL", freq025PinUp, freq025PinDown);

DcsBios::Switch3Pos pltUhf101Dial("PLT_UHF1_01_DIAL", freq01PinUp, freq01PinDown);

DcsBios::Switch3Pos pltUhf11Dial("PLT_UHF1_1_DIAL", freq1PinUp, freq1PinDown);

DcsBios::Switch3Pos pltUhf1110Dial("PLT_UHF1_110_DIAL", freq100PinUp, freq100PinDown);

void setup() {
  DcsBios::setup();
  max7219.Clear();
  max7219.Begin();
}

void loop() {
  DcsBios::loop();
}
