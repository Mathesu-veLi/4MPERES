#include <DualMotor.h>

// Line sensors pins
const int liners[] = {2, 3};

// Creates an instance of motors class with their default speed
DualMotor* frontalMotors = new DualMotor(127);

void setup() {
	// Set motors pins
  frontalMotors.setMotor1(8, 9);
  frontalMotors.setMotor2(10, 11);
	
	// Set line sensors as input
  for (int ls : liners) {
    pinMode(ls, INPUT);
  }
}

bool hasLine(int liner) {
  return digitalRead(liner);
}

void loop() {
  bool hasLineInLeft = hasLine(liners[0]);
  bool hasLineInRight = hasLine(liners[1]);
  bool hasLineInCenter = !hasLineInLeft && !hasLineInRight;
  
  if(hasLineInCenter) {
    // Makes motors go to forward
    frontalMotors.forward();
  }
  
  delay(100);
}

