/*
File to demonstrate the use of all hardware currently available parts for this module
last updated 2025-03-23
*/

#include <max7219.h>

// CLK -> D10
// CS -> D11
// DIN -> D12

MAX7219 max7219;
String dash = "-";

void display(String text, int dec) {
  while (text.length() < 6){
    text = " " + text;
  }
  max7219.DisplayChar(0, text[0], 0);
  max7219.DisplayChar(1, text[1], 0);
  max7219.DisplayChar(2, text[2], dec);
  max7219.DisplayChar(3, text[3], 0);
  max7219.DisplayChar(4, text[4], 0);
  max7219.DisplayChar(5, text[5], 0);

}

const int aPin = 3;
const int bPin = 2;
const int APin = 4;
const int BPin = 5;
const int swPin = 6;

const int sqlPin = 8;
const int uhfPin = 9;

int enc1Last = 0;
int enc1Pos = 0;
int enc2Last = 0;
int enc2Pos = 0;
long int currentFreq = 1000;
int brightness = 0x0F;

int start_time = millis();


void start() {
  for (int i = 0; i < 6; i++) {
    for (int i = 0; i < 6; i++) {
      display(dash, 0);
      delay(40);
      dash += " ";
    }
    for (int i = 6; i > 0; i--) {
      dash = dash.substring(0, i);
      display(dash, 0);
      delay(40);
    }
  }
  max7219.Clear();
  delay(100);
}

void test(){
    max7219.DisplayChar(0, '8', 1);
    max7219.DisplayChar(1, '8', 1);
    max7219.DisplayChar(2, '8', 1);
    max7219.DisplayChar(3, '8', 1);
    max7219.DisplayChar(4, '8', 1);
    max7219.DisplayChar(5, '8', 1);
}

void setup() {
    Serial.begin(9600);
    pinMode(aPin, INPUT_PULLUP);
    pinMode(bPin, INPUT_PULLUP);
    pinMode(APin, INPUT_PULLUP);
    pinMode(BPin, INPUT_PULLUP);
    pinMode(swPin, INPUT_PULLUP);
    pinMode(sqlPin, INPUT_PULLUP);
    pinMode(uhfPin, INPUT_PULLUP);
    Serial.begin(9600);
    max7219.Begin();
    max7219.Clear();
    delay(1000);
    start();
}

void loop() {
    // Encoder 1
    int enc1Val = digitalRead(aPin);
    int enc1Val2 = digitalRead(bPin);
    int enc1Current = (enc1Val << 1) | enc1Val2;

    if (enc1Current != enc1Last) {
        if ((enc1Last == 0b00 && enc1Current == 0b01) ||
            (enc1Last == 0b11 && enc1Current == 0b10)) {
            enc1Pos++;
            if (currentFreq < 255000){
              currentFreq += 1000;
            }
            Serial.println(enc1Pos);
        } else if ((enc1Last == 0b00 && enc1Current == 0b10) ||
                   (enc1Last == 0b11 && enc1Current == 0b01)) {
            enc1Pos--;
            if (currentFreq > 1000) {
              currentFreq -= 1000;
            }
            Serial.println(enc1Pos);
        }
    }
    enc1Last = enc1Current;

    // Encoder 2
    int enc2Val = digitalRead(APin);
    int enc2Val2 = digitalRead(BPin);
    int enc2Current = (enc2Val << 1) | enc2Val2;

    if (enc2Current != enc2Last) {
        if ((enc2Last == 0b00 && enc2Current == 0b01) ||
            (enc2Last == 0b11 && enc2Current == 0b10)) {
            enc2Pos++;
            if (currentFreq < 255255) {
              if (start_time < 1000){
                currentFreq += 10;
                start_time = millis();
              } else if (start_time > 1000) {
                currentFreq += 1;
                start_time = millis();
              }
            }
            // if (brightness < 0x0F) {
            //   brightness += 1;
            //   max7219.MAX7219_SetBrightness(brightness);
            // }
            Serial.println(enc2Pos);
        } else if ((enc2Last == 0b00 && enc2Current == 0b10) ||
                   (enc2Last == 0b11 && enc2Current == 0b01)) {
            enc2Pos--;
            if (currentFreq > 0) {
              currentFreq -= 1;
            }
            // if (brightness > 0) {
            //   brightness -= 1;
            //   max7219.MAX7219_SetBrightness(brightness);
            // }
            Serial.println(enc2Pos);
        }
    }
    enc2Last = enc2Current;

    // Button
    if (digitalRead(swPin) == LOW) {
        test();
    } else {
      display(String(currentFreq), 1);
      max7219.MAX7219_SetBrightness(brightness);
      if (digitalRead(sqlPin) == LOW) {
        Serial.println("SQL On");
      }
      if (digitalRead(uhfPin) == LOW) {
        Serial.println("UHF On");
      }
    }
}