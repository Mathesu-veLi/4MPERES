#include <Motor.h>

class Motors {
  private:
    Motor* motor1;
    Motor* motor2;
  public:
    void setMotor1(int pinL, int pinR) {
      motor1 = new Motor(pinL, pinR);
    };

    void setMotor2(int pinL, int pinR) {
      motor2 = new Motor(pinL, pinR);
    };

    void forward() {
      motor1->forward();
      motor2->forward();
    };

    void left() {
      motor1->back();
      motor2->forward();
    }

    void right() {
      motor1->forward();
      motor2->back();
    }

    void back() {
      motor1->back();
      motor2->back();
    };

    void stop() {
      motor1->stop();
      motor2->stop();
    };
};

Motors frontalMotors;

void setup() {
  // Set motors pins
  frontalMotors.setMotor1(8, 9);
  frontalMotors.setMotor2(10, 11);
}

void loop() {
	// Makes the motors go to forward
  frontalMotors.forward();
  delay(1000);
  
  // Makes the motors go to back
  frontalMotors.back();
  delay(1000);
}
