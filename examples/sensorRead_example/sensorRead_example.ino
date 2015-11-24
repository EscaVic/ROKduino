#include "RokDuino.h"

byte angleSensor = 8;  // bump sensor connected to sensor port 8
byte lightModule = 4; 

int sensor;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  sensor = ROKDuino::getInstance()->sensorRead(angleSensor);
  Serial.println(sensor);
  delay(10);
  if (sensor < 512)
  {
    ROKDuino::getInstance()->motorWrite(lightModule, sensor*2, CLOCKWISE);
  }
  else
  {
    ROKDuino::getInstance()->motorWrite(lightModule, (sensor-512)*2, COUNTER_CLOCKWISE);
  }
}