#define DCSBIOS_IRQ_SERIAL

#include "DcsBios.h"

int UCU_DDD_Pin = 2; 
int HCU_Lght_Tst = 3; 
int HCU_Pwr_rst_Pin = 4; 
int HCU_rdr_tggl_Pin = 5; 
int HCU_TCS_tggl_Pin = 6; 
int HCU_TID_tggl_Pin = 7; 
int HCU_WCS_Pin_A = 8; 
int HCU_WCS_Pin_B = 9; 
int HCU_TVIR_Pin_A = 10; 
int HCU_TVIR_Pin_B = 11; 

DcsBios::Switch3Pos rioHcuTvirSw("RIO_HCU_TVIR_SW", HCU_TVIR_Pin_A, HCU_TVIR_Pin_B);
DcsBios::Switch3Pos rioHcuWcs("RIO_HCU_WCS", HCU_WCS_Pin_A, HCU_WCS_Pin_B);
DcsBios::ActionButton rioHcuTidToggle("RIO_HCU_TID", "TOGGLE", HCU_TID_tggl_Pin);
DcsBios::ActionButton rioHcuTcsToggle("RIO_HCU_TCS", "TOGGLE", HCU_TCS_tggl_Pin);
DcsBios::ActionButton rioHcuRadarToggle("RIO_HCU_RADAR", "TOGGLE", HCU_rdr_tggl_Pin);
DcsBios::ActionButton rioHcuPwResetToggle("RIO_HCU_PW_RESET", "TOGGLE", HCU_Pwr_rst_Pin);
DcsBios::ActionButton rioHcuLightTestToggle("RIO_HCU_LIGHT_TEST", "TOGGLE", HCU_Lght_Tst);
DcsBios::ActionButton rioHcuDddToggle("RIO_HCU_DDD", "TOGGLE", UCU_DDD_Pin);

void setup() {
    DcsBios::setup();
}

void loop() {
    DcsBios::loop();
}