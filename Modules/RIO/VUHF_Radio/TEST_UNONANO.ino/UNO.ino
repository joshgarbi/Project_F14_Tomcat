#define DCSBIOS_IRQ_SERIAL
#include "DcsBios.h"


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



DcsBios::Switch2Pos rioVuhfSquelch("RIO_VUHF_SQUELCH", SquelchPin);
DcsBios::Switch2Pos rioVuhfFmAm("RIO_VUHF_FM_AM", FmAmPin);

//concentric rotary encoders for frequency presets and mode selection
DcsBios::RotaryEncoderT<POLL_EVERY_TIME, DcsBios::TWO_STEPS_PER_DETENT> rioVuhfPresets("RIO_VUHF_PRESETS", "DEC", "INC", APin, BPin);
DcsBios::RotaryEncoderT<POLL_EVERY_TIME, DcsBios::TWO_STEPS_PER_DETENT> rioVuhfFreqMode("RIO_VUHF_FREQ_MODE", "DEC", "INC", apin, bpin);

//potentiometers for brightness and volume control
DcsBios::Potentiometer rioVuhfBrightness("RIO_VUHF_BRIGHTNESS", brighnessPin);
DcsBios::Potentiometer rioVuhfVol("RIO_VUHF_VOL", volumePin);

void setup() {
    DcsBios::setup();
}
void loop() {
    DcsBios::loop();
}