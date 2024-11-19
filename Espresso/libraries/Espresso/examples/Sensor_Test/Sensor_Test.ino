#include "Espresso.h"

const int irPinLeft = 14;  
const int irPinRight = 27; 

void setup() {
  Serial.begin(9600);   // initialize serial communication
  pinMode(irPinLeft, INPUT);
  pinMode(irPinRight, INPUT);
  init();
}

void loop() {
  
  updateEyes();
  
  int irValueLeft = digitalRead(irPinLeft);
  int irValueRight = digitalRead(irPinRight);

  if (irValueLeft == HIGH && irValueRight == LOW) { // Object detected on the right
    Serial.println("Object detected on the right");
  } else if (irValueLeft == LOW && irValueRight == HIGH) { // Object detected on the left
    Serial.println("Object detected on the left");
  } else { // No object detected
    Serial.println("No object detected");
  }
  delay(500);  // wait for half a second before reading again

}
