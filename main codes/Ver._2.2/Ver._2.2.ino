#include <DualMotor.h>

const int liners[] = {2, 3};

DualMotor* frontalMotors = new DualMotor();

void setup() {
  frontalMotors->setMotor1(8, 9);
  frontalMotors->setMotor2(10, 11);

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
  
  Serial.print(hasLineInLeft);
  Serial.print(" | ");
  Serial.println(hasLineInRight);
  
  if(!hasLineInLeft && !hasLineInRight) {
    frontalMotors->forward();
  }

  if (hasLineInLeft) {
    frontalMotors->left();
  }

  if (hasLineInRight) {
    frontalMotors->right();
  }
  
  delay(100);
}
