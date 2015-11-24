#include "RokDuino.h"
byte command1;

void setup() {
  Serial.begin(115200);
}

void loop() {
  command1 = ROKDuino::getInstance()->irRead();
  
  Serial.print(ROKDuino::getInstance()->addressRead());
  Serial.print("\t");
  Serial.println(command1, BIN);
  
  delay(250);
}