#include <Encoder.h>

Encoder rotaryEncoder(2, 3); // Select the two hardware interrupt pins on Arduino Uno

long positionEncoder = -999; // Previous position of the encoder

void setup() {
  Serial.begin(9600);
}

void loop() {
  long newEncoder = rotaryEncoder.read(); // Read the current position of the encoder

  if (newEncoder != positionEncoder) { // Check if the position has changed
    if (newEncoder > positionEncoder) {
      Serial.println("Turned Right (Clockwise)");
    } else {
      Serial.println("Turned Left (Counterclockwise)");
    }
    positionEncoder = newEncoder; // Update the previous position
  }
}