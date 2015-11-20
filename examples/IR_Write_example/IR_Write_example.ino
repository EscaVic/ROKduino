#include "RokDuino.h"
RokDuino rok;  // Declare RokDuino object

byte commTX = 6;      // comm TX connected to sensor port 6 (battery power)

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  rok.IR_Write(commTX, CMD_SPIN_RIGHT); // address 0 by default
  delay(200);
}
