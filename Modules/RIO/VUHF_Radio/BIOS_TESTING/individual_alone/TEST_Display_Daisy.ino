#include <max7219.h>

// CLK -> D10
// CS -> D11
// DIN -> D12

MAX7219 disp1(8,9,10);
MAX7219 disp2(11,12,13);
String dash = "-";
int i = 100000;
unsigned long startTime;
int aliveCaller = 0;

#define DISP2_CS_FEEDBACK 7
#define DISP2_CS_FEEDBACK_SEND 6

bool isDisplay2Alive(int callID) {
  if (digitalRead(DISP2_CS_FEEDBACK) == HIGH) {
    return true;
  } else {
    Serial.println("Disconnected");
    if (callID == 0) {
      startTime = millis();
    }
    return false;
  }
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
  pinMode(DISP2_CS_FEEDBACK, INPUT);
  pinMode(DISP2_CS_FEEDBACK_SEND, OUTPUT);
}

void loop() {
  digitalWrite(DISP2_CS_FEEDBACK_SEND, LOW);
  delay(5);
  digitalWrite(DISP2_CS_FEEDBACK_SEND, HIGH);

  if (!isDisplay2Alive(aliveCaller)) {
    int temp = millis();
    if (temp - startTime > 1000) {
      delay(10);
      disp2.Begin();
      disp2.Clear();
      startTime = millis();
      aliveCaller = 0;
    }
    aliveCaller++;
  }
  display(String(i), 1);
  if (i == 999999){
    i = 100000;
  }
  i++;

}