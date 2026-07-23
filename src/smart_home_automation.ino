/*
 * Project: Arduino Smart Home Automation
 * Course: Programming 1
 * Lecturer: Eitan Alimi
 *
 * System 1 - Rain protection:
 * A rain sensor controls a servo-driven roof above a laundry area.
 * Wet conditions close the roof; dry conditions reopen it.
 *
 * System 2 - Parking gate:
 * An HC-SR04 ultrasonic sensor detects an approaching object.
 * The gate opens for five seconds and then closes automatically.
 *
 * The servos are detached after each movement to reduce control-signal
 * jitter while they are stationary.
 */

#include <Servo.h>

// Pin assignments
const int TRIG_PIN = 2;
const int ECHO_PIN = 4;
const int RAIN_SENSOR_PIN = A0;
const int GATE_SERVO_PIN = 3;
const int RAIN_SERVO_PIN = 5;

// Servo angles calibrated for the physical model
const int GATE_CLOSED_ANGLE = 10;
const int GATE_OPEN_ANGLE = 100;
const int ROOF_OPEN_ANGLE = 120;
const int ROOF_CLOSED_ANGLE = 0;

// Detection thresholds and timing
const int OPEN_DISTANCE_CM = 20;
const unsigned long GATE_OPEN_TIME = 5000;
const int RAIN_THRESHOLD = 900;  // Lower readings indicate wet conditions

Servo rainServo;
Servo gateServo;

// System state
bool isGateOpen = false;
unsigned long gateTimer = 0;
bool isRainingState = false;

void setup() {
  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Move both mechanisms to safe initial positions.
  moveMotor(gateServo, GATE_SERVO_PIN, GATE_CLOSED_ANGLE);
  moveMotor(rainServo, RAIN_SERVO_PIN, ROOF_OPEN_ANGLE);
}

void loop() {
  const int distance = getDistance();
  const int rainValue = analogRead(RAIN_SENSOR_PIN);

  // Rain-protection state transition
  const bool isWet = rainValue < RAIN_THRESHOLD;

  if (isWet && !isRainingState) {
    moveMotor(rainServo, RAIN_SERVO_PIN, ROOF_CLOSED_ANGLE);
    isRainingState = true;
  } else if (!isWet && isRainingState) {
    moveMotor(rainServo, RAIN_SERVO_PIN, ROOF_OPEN_ANGLE);
    isRainingState = false;
  }

  // Open the gate when an object is detected within 20 cm.
  if (distance > 0 && distance < OPEN_DISTANCE_CM && !isGateOpen) {
    moveMotor(gateServo, GATE_SERVO_PIN, GATE_OPEN_ANGLE);
    isGateOpen = true;
    gateTimer = millis();
  }

  // Use a millis()-based timer so the gate does not require a five-second delay.
  if (isGateOpen && millis() - gateTimer >= GATE_OPEN_TIME) {
    moveMotor(gateServo, GATE_SERVO_PIN, GATE_CLOSED_ANGLE);
    isGateOpen = false;
  }

  delay(100);
}

// Attach the servo, command the calibrated angle, allow movement to finish,
// and detach the control signal to reduce stationary jitter.
void moveMotor(Servo &servo, int pin, int angle) {
  servo.attach(pin);
  servo.write(angle);
  delay(800);
  servo.detach();
}

// Return the measured distance in centimeters.
// A timeout is represented by 999 cm so it cannot trigger the gate.
int getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  const unsigned long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration == 0) {
    return 999;
  }

  return duration * 0.034 / 2;
}

