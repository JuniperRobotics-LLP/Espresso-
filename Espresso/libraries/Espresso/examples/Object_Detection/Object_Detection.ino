#include "Espresso.h"

#define LEFT_IR_SENSOR_PIN 14
#define RIGHT_IR_SENSOR_PIN 27
#define LEFT_MOTOR_IN1_PIN 25
#define LEFT_MOTOR_IN2_PIN 26
#define RIGHT_MOTOR_IN3_PIN 33
#define RIGHT_MOTOR_IN4_PIN 32

int leftIRSensorValue;
int rightIRSensorValue;
int threshold = 500;

void setup() {
  Serial.begin(9600);
  pinMode(LEFT_IR_SENSOR_PIN, INPUT);
  pinMode(RIGHT_IR_SENSOR_PIN, INPUT);
  pinMode(LEFT_MOTOR_IN1_PIN, OUTPUT);
  pinMode(LEFT_MOTOR_IN2_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_IN3_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_IN4_PIN, OUTPUT);
  init();
}

void loop() {
  // read IR sensor values
  leftIRSensorValue = analogRead(LEFT_IR_SENSOR_PIN);
  rightIRSensorValue = analogRead(RIGHT_IR_SENSOR_PIN);
  
  // check for obstacles and adjust motor speed accordingly
  if (leftIRSensorValue < threshold && rightIRSensorValue < threshold) { // obstacle in front
    motorStop();
    delay(1000);
    motorBackward();
    delay(1000);
    motorLeft();
    delay(1000);
  } else if (leftIRSensorValue < threshold) { // obstacle on left
    motorStop();
    delay(1000);
    motorRight();
    delay(1000);
  } else if (rightIRSensorValue < threshold) { // obstacle on right
    motorStop();
    delay(1000);
    motorLeft();
    delay(1000);
  } else { // no obstacle detected
    motorForward();
  }
}

void motorStop() {
  digitalWrite(LEFT_MOTOR_IN1_PIN, LOW);
  digitalWrite(LEFT_MOTOR_IN2_PIN, LOW);
  digitalWrite(RIGHT_MOTOR_IN3_PIN, LOW);
  digitalWrite(RIGHT_MOTOR_IN4_PIN, LOW);
}

void motorForward() {
  digitalWrite(LEFT_MOTOR_IN1_PIN, LOW);
  digitalWrite(LEFT_MOTOR_IN2_PIN, HIGH);
  digitalWrite(RIGHT_MOTOR_IN3_PIN, LOW);
  digitalWrite(RIGHT_MOTOR_IN4_PIN, HIGH);
}


void motorBackward() {
  digitalWrite(LEFT_MOTOR_IN1_PIN, HIGH);
  digitalWrite(LEFT_MOTOR_IN2_PIN, LOW);
  digitalWrite(RIGHT_MOTOR_IN3_PIN, HIGH);
  digitalWrite(RIGHT_MOTOR_IN4_PIN, LOW);
}

void motorLeft() {
  digitalWrite(LEFT_MOTOR_IN1_PIN, LOW);
  digitalWrite(LEFT_MOTOR_IN2_PIN, HIGH);
  digitalWrite(RIGHT_MOTOR_IN3_PIN, HIGH);
  digitalWrite(RIGHT_MOTOR_IN4_PIN, LOW);
}

void motorRight() {
  digitalWrite(LEFT_MOTOR_IN1_PIN, HIGH);
  digitalWrite(LEFT_MOTOR_IN2_PIN, LOW);
  digitalWrite(RIGHT_MOTOR_IN3_PIN, LOW);
  digitalWrite(RIGHT_MOTOR_IN4_PIN, HIGH);

  updateEyes();
}
