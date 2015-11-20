#include "RokDuino.h"
RokDuino rok;  // Declare RokDuino object
byte command1;

void setup() {
  Serial.begin(115200);
}

void loop() {
  command1 = rok.IR_Read();
  
  Serial.print(rok.addressRead());
  Serial.print("\t");
  Serial.println(command1, BIN);
  
  delay(250);
}
