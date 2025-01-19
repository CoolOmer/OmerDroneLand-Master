//Includes the Arduino Stepper Library
#include <Stepper.h>

// Defines the number of steps per rotation
const int stepsPerRevolution = 260;

// For ultrasonic sensor
int trigPin = 11;    // TRIG pin
int echoPin = 12;    // ECHO pin
float duration_us, distance_cm;

// For status LED configurations
int fastBlue = 9;    // Blue LED pin
int slowRed = 6;    // Red LED pin

// Pins entered in sequence ... IN1-IN3-IN2-IN4
Stepper myStepper = Stepper(stepsPerRevolution, 2, 3, 4, 5);

void setup() {
  // Begins serial monitor, set up LEDs.
  Serial.begin(9600);
  pinMode(fastBlue, OUTPUT);
  pinMode(slowRed, OUTPUT);
  digitalWrite(fastBlue, LOW);
  digitalWrite(slowRed, LOW);

  // Configure the trigger pin to output mode (UltraSns module)
  pinMode(trigPin, OUTPUT);
  // Configure the echo pin to input mode (UltraSns module)
  pinMode(echoPin, INPUT);
}

void loop() {
    // Generate 10-microsecond pulse to TRIG pin
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Measure duration of pulse from ECHO pin
    duration_us = pulseIn(echoPin, HIGH);
    // Calculate the distance
    distance_cm = 0.017 * duration_us;
    // Print the value to Serial Monitor
    Serial.print("distance: ");
    Serial.print(distance_cm);
    Serial.println(" cm");

    // Variables for motor speeds,
    // based on rotations at top.
    int slowSpeed = 16;
    int fastSpeed = 55;
    int currentSpeed;

    if (distance_cm <= 10) {
      currentSpeed = slowSpeed;
      digitalWrite(fastBlue, LOW);
      digitalWrite(slowRed, HIGH);
      myStepper.setSpeed(slowSpeed);
    }
    else {
      currentSpeed = fastSpeed;
      digitalWrite(fastBlue, HIGH);
      digitalWrite(slowRed, LOW);
      myStepper.setSpeed(fastSpeed);
    }
    Serial.print("SPEED: ");
    Serial.print(currentSpeed);
    Serial.println();

	// Rotate counter-clock-wise
	myStepper.step(-1*stepsPerRevolution);
	delay(10);
}
