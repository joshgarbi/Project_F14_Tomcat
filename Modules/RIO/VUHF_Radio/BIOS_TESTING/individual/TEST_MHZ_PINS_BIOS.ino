#define DCSBIOS_IRQ_SERIAL
#include "DcsBios.h"

//freq pings
const int freq025PinUp = 22;
const int freq025PinDown = 23;
const int freq01PinDown = 24;
const int freq01PinUp = 25;
const int freq1PinUp = 26;
const int freq1PinDown = 27;
const int freq110PinUp = 28;
const int freq110PinDown = 29;

//freq adjustment
DcsBios::Switch3Pos rioVuhf025Dial("RIO_VUHF_025_DIAL", freq025PinUp, freq025PinDown);
DcsBios::Switch3Pos rioVuhf01Dial("RIO_VUHF_01_DIAL", freq01PinUp, freq01PinDown);
DcsBios::Switch3Pos rioVuhf1Dial("RIO_VUHF_1_DIAL", freq1PinDown, freq01PinUp);
DcsBios::Switch3Pos rioVuhf110Dial("RIO_VUHF_110_DIAL", freq110PinDown, freq110PinUp);

void setup() {
  DcsBios::setup();
}

void loop() {
  DcsBios::loop();
}
 