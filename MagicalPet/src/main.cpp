#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

// Define GPIO pins for the buttons
#define BUTTON_1_PIN 25  // GPIO for Button 1
#define BUTTON_2_PIN 23  // GPIO for Button 2

int pos = 90;
int servoPin = 13;
int data;
void angle(int a);

// Pins for wheels
// Original Pins
const int motorPin1 = 18;  // IN1 (GPIO 18)
const int motorPin2 = 19;  // IN2 (GPIO 19)

// Secondary Pins
const int motorPin3 = 16;  // IN1 (GPIO 18)
const int motorPin4 = 17;  // IN2 (GPIO 19)

// NeoPixel setup
#define LED_PIN 14          // Pin connected to NeoPixel data input
#define NUM_LEDS 42         // Number of LEDs in the strip
Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRBW + NEO_KHZ800);

void right_open();
void left_open();
void left_close();
void right_close();
void moveForward();
void moveBackward();
void stopMotor();
void displayRainbow();
void displayRed();
void clearLEDs();
void spin1();
void spin2();

void setup() {
  Serial.begin(9600);
  pinMode(servoPin, OUTPUT);

  // Set the motor control pins as outputs
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);

  // Set up both button pins as input with built-in pull-up resistors
  pinMode(BUTTON_1_PIN, INPUT_PULLUP);
  pinMode(BUTTON_2_PIN, INPUT_PULLUP);

  // Initialize NeoPixel strip
  strip.begin();
  strip.show(); // Initialize all LEDs to "off"
}

void loop() {
  // Read the states of both buttons
  int button1State = digitalRead(BUTTON_1_PIN);
  int button2State = digitalRead(BUTTON_2_PIN);

  // Check Button 1
  if (button1State == LOW) {  // Button 1 is pressed (active low)
    Serial.println("1");  // Send "1" when Button 1 is pressed
  }

  // Check Button 2
  if (button2State == LOW) {  // Button 2 is pressed (active low)
    Serial.println("2");  // Send "2" when Button 2 is pressed
  }

  // Short delay for debouncing
  delay(100);  // Prevent multiple triggers due to button bounce

  while (Serial.available()) {
    data = Serial.read();

    if (data == '0') {
      // Reacting for happy emotion
      displayRainbow();            // Display rainbow animation
      moveForward();
      delay(5000);
      stopMotor();
      spin1();
      delay(3000);
      spin2();
      delay(1500);
      stopMotor();
      left_open();
      delay(7000);
      left_close();
      moveBackward();
      delay(5000);
      stopMotor();
      clearLEDs();
    } else if (data == '1') {
      // Reacting for negative emotion
      displayRed();               // Display red LEDs
      moveBackward();
      delay(5000);
      stopMotor();
      right_open();
      delay(7000);
      right_close();
      moveForward();
      delay(5000);
      stopMotor();
      clearLEDs();
    } else {
      Serial.println("Invalid input");
    }
  }
}

// Function to display a rainbow animation
void displayRainbow() {
  for (int j = 0; j < 256; j++) {  // Cycle through colors
    for (int i = 0; i < strip.numPixels(); i++) {
      int pixelHue = (i * 65536L / strip.numPixels() + j * 256) & 65535;
      strip.setPixelColor(i, strip.ColorHSV(pixelHue)); // Set rainbow colors
    }
    strip.show();
    delay(20);  // Adjust speed of the animation
  }
}

// Function to display all LEDs in red
void displayRed() {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(255, 0, 0)); // Red color
  }
  strip.show();
}

void clearLEDs() {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0)); // Turn off the LED
  }
  strip.show();
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

// Function to spin
void spin1() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  Serial.println("Spinning 1");
}

// Function to spin
void spin2() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  Serial.println("Spinning 2");
}

// Function to move motor forward
void moveForward() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  Serial.println("Moving forward");
}

void moveBackward() {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
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
