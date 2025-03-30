#include <max7219.h>

// CLK -> D10
// CS -> D11
// DIN -> D12

MAX7219 max7219;
int j = 0;
char text[6] = {'~', '!', '@', ';', '.', '?'};
char btext[6] = {'?', '.', ';', '@', '!', '~'};
String dash = "-";



void start() {
  int i = 4;
  while (i > 0){
    i--;
    max7219.DisplayChar(0, text[0], 0);
    delay(50);
    max7219.DisplayChar(0, ' ', 0);
    max7219.DisplayChar(1, text[0], 0);
    delay(50);
    max7219.DisplayChar(1, ' ', 0);
    max7219.DisplayChar(2, text[0], 0);
    delay(50);
    max7219.DisplayChar(2, ' ', 0);
    max7219.DisplayChar(3, text[0], 0);
    delay(50);
    max7219.DisplayChar(3, ' ', 0);
    max7219.DisplayChar(4, text[0], 0);
    delay(50);
    max7219.DisplayChar(4, ' ', 0);
    max7219.DisplayChar(5, text[0], 0);
    delay(50);
    max7219.DisplayChar(5, ' ', 0);
    max7219.DisplayChar(5, text[1], 0);
    delay(50);
    max7219.DisplayChar(5, ' ', 0);
    max7219.DisplayChar(5, text[2], 0);
    delay(50);
    max7219.DisplayChar(5, ' ', 0);
    max7219.DisplayChar(5, text[3], 0);
    delay(50);
    max7219.DisplayChar(5, ' ', 0);
    max7219.DisplayChar(4, text[3], 0);
    delay(50);
    max7219.DisplayChar(4, ' ', 0);
    max7219.DisplayChar(3, text[3], 0);
    delay(50);
    max7219.DisplayChar(3, ' ', 0);
    max7219.DisplayChar(2, text[3], 0);
    delay(50);
    max7219.DisplayChar(2, ' ', 0);
    max7219.DisplayChar(1, text[3], 0);
    delay(50);
    max7219.DisplayChar(1, ' ', 0);
    max7219.DisplayChar(0, text[3], 0);
    delay(50);
    max7219.DisplayChar(0, ' ', 0);
    max7219.DisplayChar(0, text[4], 0);
    delay(50);
    max7219.DisplayChar(0, ' ', 0);
    max7219.DisplayChar(0, text[5], 0);
    delay(50);
    max7219.DisplayChar(0, ' ', 0);
  }
}

void setup() {
  Serial.begin(9600);
  max7219.Begin();
  max7219.Clear();
  start();
  delay(1000);
}

void loop(){
    

}