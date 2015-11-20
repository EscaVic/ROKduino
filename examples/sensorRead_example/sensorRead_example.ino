#include "RokDuino.h"
RokDuino rok;  // Declare RokDuino object

byte angleSensor = 8;  // bump sensor connected to sensor port 8
byte lightModule = 4; 

int sensor;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  sensor = rok.sensorRead(angleSensor);
  Serial.println(sensor);
  delay(10);
  if (sensor < 512)
    rok.motorWrite(lightModule, sensor*2, CLOCKWISE);
   else
    rok.motorWrite(lightModule, (sensor-512)*2, COUNTER_CLOCKWISE);
}
