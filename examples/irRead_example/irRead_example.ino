#include "ROKduino.h"
// Pointer to ROKduino lib
ROKduino* rok = ROKduino::getInstance();
byte command1;

void setup() {
  Serial.begin(115200);}

void loop() {
  command1 = rok->irRead();
  
  Serial.print(rok->addressRead());
  Serial.print("\t");
  Serial.println(command1, BIN);
  
  delay(250);
}
