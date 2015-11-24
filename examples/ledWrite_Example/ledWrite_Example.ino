#include "RokDuino.h"

void setup() {
  // put your setup code here, to run once:
  ROKDuino::getInstance()->ledWrite(LED_LEFT, LED_ON);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
  ROKDuino::getInstance()->ledWrite(LED_BOTH, LED_TOGGLE);
}