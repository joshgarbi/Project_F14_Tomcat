#define DCSBIOS_IRQ_SERIAL
#include "DcsBios.h"

const int rioTacanBitPin = -1;
const int rioTacanChannelPin = -1;
const int rioTacanCmdButtonPin = -1;

DcsBios::Switch2Pos rioTacanBit("RIO_TACAN_BIT", rioTacanBitPin);
DcsBios::Switch2Pos rioTacanChannel("RIO_TACAN_CHANNEL", rioTacanChannelPin);
DcsBios::Switch2Pos rioTacanCmdButton("RIO_TACAN_CMD_BUTTON", rioTacanCmdButtonPin);

void setup() {
  DcsBios::setup();
}

void loop() {
  DcsBios::loop();
}
