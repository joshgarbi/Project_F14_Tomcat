const int aPin = 3;
const int bPin = 2;
const int APin = 4;
const int BPin = 5;

int enc1Last = 0;
int enc1Pos = 0;
int enc2Last = 0;
int enc2Pos = 0;

void setup() {
    Serial.begin(9600);
    pinMode(aPin, INPUT_PULLUP);
    pinMode(bPin, INPUT_PULLUP);
    pinMode(APin, INPUT_PULLUP);
    pinMode(BPin, INPUT_PULLUP);
}

void loop() {
    // Encoder 1
    int enc1Val = digitalRead(aPin);
    int enc1Val2 = digitalRead(bPin);
    int enc1Current = (enc1Val << 1) | enc1Val2;

    if (enc1Current != enc1Last) {
        if ((enc1Last == 0b00 && enc1Current == 0b01) ||
            (enc1Last == 0b01 && enc1Current == 0b11) ||
            (enc1Last == 0b11 && enc1Current == 0b10) ||
            (enc1Last == 0b10 && enc1Current == 0b00)) {
            enc1Pos++;
            Serial.println(enc1Pos);
        } else if ((enc1Last == 0b00 && enc1Current == 0b10) ||
                   (enc1Last == 0b10 && enc1Current == 0b11) ||
                   (enc1Last == 0b11 && enc1Current == 0b01) ||
                   (enc1Last == 0b01 && enc1Current == 0b00)) {
            enc1Pos--;
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
            (enc2Last == 0b01 && enc2Current == 0b11) ||
            (enc2Last == 0b11 && enc2Current == 0b10) ||
            (enc2Last == 0b10 && enc2Current == 0b00)) {
            enc2Pos++;
            Serial.println(enc2Pos);
        } else if ((enc2Last == 0b00 && enc2Current == 0b10) ||
                   (enc2Last == 0b10 && enc2Current == 0b11) ||
                   (enc2Last == 0b11 && enc2Current == 0b01) ||
                   (enc2Last == 0b01 && enc2Current == 0b00)) {
            enc2Pos--;
            Serial.println(enc2Pos);
        }
    }
    enc2Last = enc2Current;
}