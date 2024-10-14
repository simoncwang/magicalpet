#include <Arduino.h>
#include <ESP32Servo.h>

int pos = 0;
int servoPin = 13;
Servo myServo;

void setup() {
  myservo.attach(servoPin, 500, 2600);
}

void loop() {

  for (pos = 0; pos <= 180; pos += 1) {
    myServo.write(pos);
    delay(15);
  }
  delay(500);
  for (pos = 180; pos >= 0; pos -= 1) {
    myServo.write(pos);
    delay(15);
  }
  delay(500);
}
