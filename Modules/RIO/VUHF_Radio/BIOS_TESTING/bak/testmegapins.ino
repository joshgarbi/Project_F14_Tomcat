void setup(){
    Serial.begin(9600);
    pinMode(24, INPUT_PULLUP);
    pinMode(27, INPUT_PULLUP);
}

void loop(){
    if (digitalRead(24) == LOW) {
        Serial.println("Button 1 pressed");
    }
    if (digitalRead(27) == LOW) {
        Serial.println("Button 2 pressed");
    }
}