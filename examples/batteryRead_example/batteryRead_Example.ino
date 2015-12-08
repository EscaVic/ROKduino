#include "ROKduino.h"
// Pointer to ROKduino lib
ROKduino* rok = ROKduino::getInstance();

void setup() {
  Serial.begin(115200);
}

void loop() {
  unsigned int batteryLevel = rok->batteryRead();
  Serial.print(batteryLevel);  
  delay(2000);

  if (batteryLevel < 2)
  {
    // Battery Level low - make speaker noise
    rok->speakerWrite(100, 250);
  }
}
