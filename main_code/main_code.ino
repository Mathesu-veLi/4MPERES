#include <DualMotor.h>
#include <QTRSensors.h>

#define DEFAULT_SPEED 127
#define MAX_SPEED 255

// Creates an instance of motors class with their default speed
DualMotor* frontalMotors = new DualMotor(DEFAULT_SPEED);

// Creates an intance of sensors class
QTRSensors qtr;

const uint8_t SensorCount = 5;
uint16_t sensorValues[SensorCount];

// PID
int lastError = 0;
int P;
int I;
int D;

float Kp = 55;
float Kd = 30;
float Ki = 0.00;

void setup() {
	// Set motors pins
  frontalMotors->setMotor1(8, 9);
  frontalMotors->setMotor2(10, 11);
	
	// Set line sensors pins
	qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){A1, A2, A3, A4, A5}, SensorCount);
  
  calibrateSensors();
  delay(7000);
}

void calibrateSensors() {
	for (uint16_t i = 0; i < 50; i++)
  {
    qtr.calibrate();
  }
}

void loop() {
	int correctionSpeed = calculateCorrection();
	
	int speedA = DEFAULT_SPEED + correctionSpeed;
  int speedB = DEFAULT_SPEED - correctionSpeed;
  speedConstrains(speedA, speedB);
	
  frontalMotors->custom(speedA, speedB);
  delay(100);
}

int calculateCorrection(){
  uint16_t position = qtr.readLineBlack(sensorValues);
  int error = 2500 - position;

  P = error;
  I = I + error;
  D = error - lastError;
  lastError = error;

	return (Kp * P) + (Ki * I) + (Kd * D);  
}

void speedConstraints(int speedA, int speedB) {
	if(speedA > MAX_SPEED){
    speedA = MAX_SPEED;
  }

  if(speedB > MAX_SPEED){
    speedB = MAX_SPEED;
  }

  if(speedA < 0){
    speedA = 0;
  }

  if(speedB < 0){
    speedB = 0;
  }	
}
