#include <DualMotor.h>

#define CENTER 4

const int liners[] = {2, 3, 4, 5, 6};

DualMotor* frontalMotors = new DualMotor();

void setup() {
  // put your setup code here, to run once:
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
  bool hasLineInVeryLeft = hasLine(liners[0]) ? true : false;
  bool hasLineInLeft = hasLine(liners[1]) ? true : false;
  bool hasLineInCenter = hasLine(liners[2]) ? true : false;
  bool hasLineInRight = hasLine(liners[3]) ? true : false;
  bool hasLineInVeryRight = hasLine(liners[4]) ? true : false;
  bool hasNoLine = !hasLineInVeryLeft && !hasLineInLeft && !hasLineInCenter && !hasLineInRight && !hasLineInVeryRight;

  if (hasLineInLeft || hasLineInVeryLeft) {
    frontalMotors->left();
  }

  if(hasLineInCenter || hasNoLine) {
    frontalMotors->forward();
  }

  if (hasLineInRight || hasLineInVeryRight) {
    frontalMotors->right();
  }
  
  delay(100);
}
