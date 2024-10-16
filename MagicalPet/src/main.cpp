#include <Arduino.h>

int pos = 90;
int servoPin = 13;
int data;
void angle(int a);

void right_open();
void left_open();
void left_close();
void right_close();

void setup() {
  Serial.begin(9600);
  pinMode(servoPin, OUTPUT);
}

void loop() {
  while (Serial.available()) {
    data = Serial.read();

    if (data == '0') {
      right_open();
      delay(15000);
      right_close();
    } else if (data == '1') {
      left_open();
      delay(15000);
      left_close();
    } else {
      Serial.println("Invalid input");
    }
  }
}

void right_open() {
  for (pos = 90; pos >= 0; pos -= 1) {
    angle(pos);
  }
}

void left_open() {
  for (pos = 90; pos <= 180; pos += 1) {
    angle(pos);
  }
}

void left_close() {
  for (pos = 180; pos >= 90; pos -= 1) {
    angle(pos);
  }
}

void right_close() {
  for (pos = 0; pos <= 90; pos += 1) {
    angle(pos);
  }
}

void angle(int a) {
  int pulseWidth = map(a, 0, 180, 500, 2600);
  digitalWrite(servoPin, HIGH);
  delayMicroseconds(pulseWidth);
  digitalWrite(servoPin, LOW);
  delayMicroseconds(20000-pulseWidth);

}
