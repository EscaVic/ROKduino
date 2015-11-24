#include "RokDuino.h"

int proxTX = 5;      // prox TX connected to sensor port 5 (battery power)
int proxRX = 8;      // prox RX connected to sensor port 8

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(ROKDuino::getInstance()->proximityRead(proxTX, proxRX));
}