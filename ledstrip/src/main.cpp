#include "Arduino.h"

#define PIN13 9

void setup() {
  pinMode(PIN13, OUTPUT);
}

void loop() {
  for(;;) {
    digitalWrite(PIN13, LOW);
    delay(400);
    digitalWrite(PIN13, HIGH);
    delay(400);
  }
}
