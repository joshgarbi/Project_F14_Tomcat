int potPin = A0;
int potVal = 0;

int brightnessPin = A1;
int brightnessVal = 0;

void setup() {
    Serial.begin(9600); 
    pinMode(potPin, INPUT); 
    pinMode(brightnessPin, INPUT);
}

void loop() {
    potVal = analogRead(potPin);
    brightnessVal = analogRead(brightnessPin); 
    Serial.println("Potentiometer Value: " + String(potVal) + " | Brightness Value: " + String(brightnessVal));

}