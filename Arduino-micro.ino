#include <Arduino.h>

void setup() {
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
}

void loop() {
  if (digitalRead(A0) == HIGH)
    digitalWrite(2, HIGH);
  else
    digitalWrite(2, LOW);

  if (digitalRead(A1) == HIGH)
    digitalWrite(3, HIGH);
  else
    digitalWrite(3, LOW);
}