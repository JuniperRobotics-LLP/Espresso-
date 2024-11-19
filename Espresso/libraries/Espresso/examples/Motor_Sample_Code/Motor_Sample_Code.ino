#include <PololuMaestro.h>
#include "Espresso.h"

#define maestroSerial Serial2


// Define pin numbers for the Piezo Buzzer and the two DC motors
const int LEFT_MOTOR_IN1_PIN = 25;
const int LEFT_MOTOR_IN2_PIN = 26;
const int RIGHT_MOTOR_IN3_PIN = 33;
const int RIGHT_MOTOR_IN4_PIN = 32;

MicroMaestro maestro(maestroSerial);

void setup() {
  // Set pin modes
  pinMode(LEFT_MOTOR_IN1_PIN, OUTPUT);
  pinMode(LEFT_MOTOR_IN2_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_IN3_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_IN4_PIN, OUTPUT);
  maestroSerial.begin(9600);
  init();
}

void loop() {

  updateEyes();
  
// Run the two DC motors in clockwise direction for 7 second
  digitalWrite(LEFT_MOTOR_IN1_PIN, HIGH);
  digitalWrite(LEFT_MOTOR_IN2_PIN, LOW);
  digitalWrite(RIGHT_MOTOR_IN3_PIN, LOW);
  digitalWrite(RIGHT_MOTOR_IN4_PIN, HIGH);
  delay(7000);
 
  // Stop the two DC motors for 0.5 second
  digitalWrite(LEFT_MOTOR_IN1_PIN, LOW);
  digitalWrite(LEFT_MOTOR_IN2_PIN, LOW);
  digitalWrite(RIGHT_MOTOR_IN3_PIN, LOW);
  digitalWrite(RIGHT_MOTOR_IN4_PIN, LOW);
  delay(500);
 
  // Run the two DC motors in counter-clockwise direction for 7 second
  digitalWrite(LEFT_MOTOR_IN1_PIN, LOW);
  digitalWrite(LEFT_MOTOR_IN2_PIN, HIGH);
  digitalWrite(RIGHT_MOTOR_IN3_PIN, HIGH);
  digitalWrite(RIGHT_MOTOR_IN4_PIN, LOW);
  delay(7000);
 
  // Stop the two DC motors for 0.5 second
  digitalWrite(LEFT_MOTOR_IN1_PIN, LOW);
  digitalWrite(LEFT_MOTOR_IN2_PIN, LOW);
  digitalWrite(RIGHT_MOTOR_IN3_PIN, LOW);
  digitalWrite(RIGHT_MOTOR_IN4_PIN, LOW);
  delay(500);

  // Head Bobbing
  maestro.restartScript(6);
  delay(1000);
  
  maestro.restartScript(7);
  delay(1000);

  maestro.stopScript();
}
