int val;
int oldval = 10;
void setup() {
  Serial.begin(9600);
}

void loop() {
  val = analogRead(A0);

}