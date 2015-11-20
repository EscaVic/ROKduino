#include "RokDuino.h"
RokDuino rok;  // Declare RokDuino object

void setup() {
  // put your setup code here, to run once:
  rok.LED_Write(LED_LEFT, LED_ON);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
  rok.LED_Write(LED_BOTH, LED_TOGGLE);
}
