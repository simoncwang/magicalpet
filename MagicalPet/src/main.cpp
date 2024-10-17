#include <Arduino.h>

int pos = 90;
int servoPin = 13;
int data;
void angle(int a);

const int redPin = 32; 
const int greenPin = 33; 

void right_open();
void left_open();
void left_close();
void right_close();

void setup() {
  Serial.begin(9600);
  pinMode(servoPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}

void loop() {
  while (Serial.available()) {
    data = Serial.read();

    if (data == '0') {
      right_open();
      digitalWrite(greenPin, HIGH); // set the LED on
      delay(15000);
      right_close();
      digitalWrite(greenPin, LOW); // set the LED off
    } else if (data == '1') {
      left_open();
      digitalWrite(redPin, HIGH); // set the LED on
      delay(15000);
      left_close();
      digitalWrite(redPin, LOW); // set the LED off
    } else {
      Serial.println("Invalid input");
    }
  }
}

void right_open() {
  for (pos = 90; pos >= 45; pos -= 1) {
    angle(pos);
  }
}

void right_close() {
  for (pos = 45; pos <= 90; pos += 1) {
    angle(pos);
  }
}

void left_open() {
  for (pos = 90; pos <= 135 ; pos += 1) {
    angle(pos);
  }
}

void left_close() {
  for (pos = 135; pos >= 90; pos -= 1) {
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

// #include <Arduino.h>
// constants definition
// const int redPin = 32; // Default LED is connected to GPIO 23
// const int greenPin = 33; // Default LED is connected to GPIO 23
// The setup() method runs once, when the sketch starts
// void setup() {
// // initialize the digital pin as an output:
// pinMode(redPin, OUTPUT);
// pinMode(greenPin, OUTPUT);
// }
// the loop() method runs over and over again,
// as long as the Arduino has power
// void loop()
// {
// digitalWrite(redPin, HIGH); // set the LED on
// delay(5000); // wait for 5 second
// digitalWrite(redPin, LOW); // set the LED off
// delay(5000); // wait for 5 second

// digitalWrite(greenPin, HIGH); // set the LED on
// delay(5000); // wait for 5 second
// digitalWrite(greenPin, LOW); // set the LED off
// delay(5000); // wait for 5 second
// }