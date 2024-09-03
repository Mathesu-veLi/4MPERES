#include <DualMotor.h>

// Creates an instance of motors class with their default speed 
DualMotor* frontalMotors = new DualMotor(127);

void setup() {
	// Set motors pins
  frontalMotors->setMotor1(8, 9);
  frontalMotors->setMotor2(10, 11);
}

void loop() {
	// Makes the motors go to forward
  frontalMotors->forward();
  delay(1000);
  
  // Makes the motors go to back
  frontalMotors->back();
  delay(1000);
}
