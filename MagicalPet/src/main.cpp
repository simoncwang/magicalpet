#include <Arduino.h>

int pos = 90;
int servoPin = 13;
int data;
void angle(int a);

const int redPin = 32; 
const int greenPin = 33; 

// Pins for wheels
// Original Pins
const int motorPin1 = 18;  // IN1 (GPIO 18)
const int motorPin2 = 19;  // IN2 (GPIO 19)

// Secondary Pins
const int motorPin3 = 16;  // IN1 (GPIO 18)
const int motorPin4 = 17;  // IN2 (GPIO 19)

void right_open();
void left_open();
void left_close();
void right_close();
void moveForward();
void moveBackward();
void stopMotor();

void setup() {
  Serial.begin(9600);
  pinMode(servoPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);

  // Set the motor control pins as outputs
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
}

void loop() {
  while (Serial.available()) {
    data = Serial.read();

    if (data == '0') {
      // Reacting for happy emotion
      moveForward();
      delay(5000);
      stopMotor();
      right_open();
      digitalWrite(greenPin, HIGH); // set the LED on
      delay(15000);
      right_close();
      moveBackward();
      delay(5000);
      stopMotor();
      digitalWrite(greenPin, LOW); // set the LED off
    } else if (data == '1') {
      // Reacting for negative emotion
      moveBackward();
      delay(5000);
      stopMotor();
      left_open();
      digitalWrite(redPin, HIGH); // set the LED on
      delay(15000);
      left_close();
      moveForward();
      delay(5000);
      stopMotor();
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

// Function to move motor forward
void moveForward() {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  Serial.println("Moving forward");
}

void moveBackward() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
  Serial.println("Moving backward");
}

void stopMotor() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  Serial.println("Stopped");
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