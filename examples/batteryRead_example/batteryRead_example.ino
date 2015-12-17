#include "ROKduino.h"
// Pointer to ROKduino lib
ROKduino* rok = ROKduino::getInstance();
float batteryLevel;

void setup() {
  Serial.begin(115200);
}

void loop() {
  batteryLevel = rok->batteryRead();
  Serial.println(batteryLevel);  
  delay(1000);

  if (batteryLevel < 3.0)
  {
    // Battery Level low - make speaker noise
    rok->speakerWrite(100, 250);
  }
}
