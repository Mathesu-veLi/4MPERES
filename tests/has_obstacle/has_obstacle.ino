#include <HC_SR04.h>

#define TRIGGER 13
#define ECHO 14

HC_SR04 sensor(TRIGGER, ECHO);

void setup() {
  Serial.begin(9600);
}

void loop()
{
  double obstacleDistance = sensor.cm_distance();

  Serial.print("Distance: ");
  Serial.println(obstacleDistance);
  Serial.println("")

  delay(500);
}