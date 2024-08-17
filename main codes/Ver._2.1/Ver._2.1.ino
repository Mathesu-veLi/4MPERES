#include <DualMotor.h>

const int liners[] = {2, 3};

// Define classe para controlar os motores simultaneamente
DualMotor* frontalMotors = new DualMotor(127);

void setup() {
  frontalMotors.setMotor1(8, 9);
  frontalMotors.setMotor2(10, 11);

  for (int ls : liners) {
    pinMode(ls, INPUT);
  }

  Serial.begin(9600);
}

bool hasLine(int liner) {
  return digitalRead(liner) == 0 ? true : false;
}

void loop() {
  bool hasLineInLeft = hasLine(liners[0]);
  bool hasLineInRight = hasLine(liners[1]);
  
  if(!hasLineInLeft && !hasLineInRight) {
    frontalMotors.forward();
  }
  
  delay(100);
}
