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

void setup() {
  Serial.begin(9600);
  max7219.Begin();
  max7219.Clear();
  delay(1000);
  start();
}

void loop() {
  display("204839", 1);
}