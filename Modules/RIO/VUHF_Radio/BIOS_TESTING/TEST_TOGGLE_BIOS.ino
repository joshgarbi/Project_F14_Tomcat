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



const byte rioVuhfSquelchPins[2] = {8, 9};
DcsBios::Switch2Pos rioVuhfSquelch("RIO_VUHF_SQUELCH", 8);

DcsBios::Switch2Pos rioVuhfFmAm("RIO_VUHF_FM_AM", 10);

void setup() {
  DcsBios::setup();
}

void loop() {
  DcsBios::loop();
}

