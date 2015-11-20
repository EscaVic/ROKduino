#include "RokDuino.h"
RokDuino rok;  // Declare RokDuino object

byte motorModule = 1;   // motor connected to motor port 1
int speed = 0;
int i;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  // specify speed and direction separately
  for (speed = 0; speed <= 1023; speed++)
  {
     rok.motorWrite(motorModule, speed, CLOCKWISE);
    Serial.println(speed);
    delay(2);
  }
  for (speed = 1023; speed >= 0; speed--)
  {
    rok.motorWrite(motorModule, speed, CLOCKWISE);
    Serial.println(speed);
    delay(2);
  }
  
  // specify direction with positive or negative speed
  for (speed = 0; speed >= -1023; speed--)
  {
     rok.motorWrite(motorModule, speed);
    Serial.println(speed);
    delay(2);
  }
  for (speed = -1023; speed <= 1023; speed++)
  {
    rok.motorWrite(motorModule, speed);
    Serial.println(speed);
    delay(2);
  }
  for (speed = 1023; speed >= 0; speed--)
  {
    rok.motorWrite(motorModule, speed);
    Serial.println(speed);
    delay(2);
  }
}
