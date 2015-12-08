#include "ROKduino.h"
// Pointer to ROKduino lib
ROKduino* rok;
int proxTX = 5;      // prox TX connected to sensor port 5 (battery power)
int proxRX = 8;      // prox RX connected to sensor port 8

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  // Get singleton reference to ROKduino
  rok = ROKduino::getInstance();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(rok->proximityRead(proxTX, proxRX));
}