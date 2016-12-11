#include "ROKduino.h"
// Pointer to ROKduino lib
ROKduino* rok = ROKduino::getInstance();
byte sensorPort = 1;
byte lightModule = 1; 

int sensorValue;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  sensorValue = rok->sensorRead(sensorPort);
  Serial.println(sensorValue);
  delay(10);
  if (sensorValue < 512)
  {
    rok->motorWrite(lightModule, sensorValue*2, CLOCKWISE);
  }
  else
  {
    rok->motorWrite(lightModule, (1024-sensorValue)*2, COUNTER_CLOCKWISE);
  }
}