const int lineSensors[] = {3, 2};

void setup()
{
  // put your setup code here, to run once:
  for (int ls : lineSensors)
  {
    pinMode(ls, INPUT);
  }

  Serial.begin(9600);
}

bool hasLine(int liner)
{
  return digitalRead(liner) == 0 ? true : false;
}

void loop()
{
  // put your main code here, to run repeatedly:
  Serial.print("Line Sensor ");
  bool hasLineInLeft = hasLine(lineSensors[0]);
  bool hasLineInRight = hasLine(lineSensors[1]);
  Serial.print(hasLineInLeft);
  Serial.print(" | ");
  Serial.println(hasLineInRight);

  delay(1000);
}
