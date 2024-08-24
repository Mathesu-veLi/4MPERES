#include <DualMotor.h>

const int liners[] = {2, 3, 4, 5, 6};

//p-only control
const int Ki = 127;
const int Kp = 0.5;

const int targetValue = 0;

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

double calculateCorrection(double actualValue) {
  double error = actualValue - targetValue;
  double correction = error * Kp;
  return correction;
}

void loop() {
  bool hasLineInVeryLeft = hasLine(liners[0]);
  bool hasLineInLeft = hasLine(liners[1]);
  bool hasLineInCenter = hasLine(liners[2]);
  bool hasLineInRight = hasLine(liners[3]);
  bool hasLineInVeryRight = hasLine(liners[4]);
  bool hasNoLine = !hasLineInVeryLeft && !hasLineInLeft && !hasLineInCenter && !hasLineInRight && !hasLineInVeryRight;

  if(hasLineInCenter || hasNoLine) {
    frontalMotors->forward();
  } else {
    double correction;

    if(hasLineInVeryLeft) {
      correction = calculateCorrection(-2);
    }

    if(hasLineInLeft) {
      correction = calculateCorrection(-1);
    }

    if(hasLineInRight) {
      correction = calculateCorrection(1);
    }

    if(hasLineInVeryRight) {
      correction = calculateCorrection(2);
    }

    frontalMotors->custom(round(Ki + correction), round(Ki - correction));
  }
  
  delay(100);
}