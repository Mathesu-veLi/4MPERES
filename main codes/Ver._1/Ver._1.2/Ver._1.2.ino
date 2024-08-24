#include <DualMotor.h>

DualMotor* frontalMotors = new DualMotor(127);

void setup() {
  // put your setup code here, to run once:
  frontalMotors->setMotor1(8, 9);
  frontalMotors->setMotor2(10, 11);
}

void loop() {
  // put your main code here, to run repeatedly:
  frontalMotors->forward();
  delay(1000);
  frontalMotors->back();
  delay(1000);
}
