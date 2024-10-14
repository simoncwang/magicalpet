#include <Arduino.h>

int pos = 0;
int servoPin = 13;
void angle(int a);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(servoPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (pos = 0; pos < 180; pos += 1) {
    angle(pos);
  }
  

  for (pos = 180; pos > 0; pos -=1) {
    angle(pos);
  }
}

void angle(int a) {
  // map (x, fromA, toA, fromB, toB);
  int pulseWidth = map(a, 0, 180, 500, 2600);
  digitalWrite(servoPin, HIGH);
  delayMicroseconds(pulseWidth);
  digitalWrite(servoPin, LOW);
  delayMicroseconds(20000-pulseWidth);

}
