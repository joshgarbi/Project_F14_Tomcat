int potPin = A0;
int potVal = 0;

void setup() {
    Serial.begin(9600); 
    pinMode(potPin, INPUT); 
}

void loop() {
    potVal = analogRead(potPin); 
    Serial.println(potVal); 
}