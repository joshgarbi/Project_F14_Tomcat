#include <max7219.h>

// CLK -> D10
// CS -> D11
// DIN -> D12

MAX7219 disp1(8,9,10);
MAX7219 disp2(11,12,13);
String dash = "-";
int i = 100000;
int time = millis();

bool checkConnection() {
  digitalWrite(6, HIGH);      // Set output HIGH
  delay(10);                       // Small delay to allow voltage to settle
  int state = digitalRead(7);  // Read input pin
  return state == HIGH;
}

void display(String text, int dec) {
  while (text.length() < 6){
    text = " " + text;
  }
  disp1.DisplayChar(0, text[0], 0);
  disp1.DisplayChar(1, text[1], 0);
  disp1.DisplayChar(2, text[2], dec);
  disp1.DisplayChar(3, text[3], 0);
  disp1.DisplayChar(4, text[4], 0);
  disp1.DisplayChar(5, text[5], 0);
  
  disp2.DisplayChar(0, text[0], 0);
  disp2.DisplayChar(1, text[1], 0);
  disp2.DisplayChar(2, text[2], dec);
  disp2.DisplayChar(3, text[3], 0);
  disp2.DisplayChar(4, text[4], 0);
  disp2.DisplayChar(5, text[5], 0);
  
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
  disp1.Clear();
  delay(100);
}

void setup() {
  Serial.begin(9600);
  disp1.Begin();
  disp1.Clear();
  disp2.Begin();
  disp2.Clear();  
  delay(1000);
  start();
  pinMode(7, INPUT);
  pinMode(6, OUTPUT);
}

void loop() {
  if (!checkConnection() && (time - millis()) > 100) {
    delay(100);
    disp2.Begin();
    disp2.Clear();
    time = millis();
  }
  display(String(i), 1);
  if (i == 999999){
    i = 100000;
  }
  i++;

}