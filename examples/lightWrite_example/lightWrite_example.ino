#include "ROKduino.h"
// Pointer to ROKduino lib
ROKduino* rok = ROKduino::getInstance();

byte lightModule = 1;   // light module connected to motor port 1
int brightness;
boolean color = GREEN;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  // ramp up brightness
  for (brightness = 0; brightness <= 1023; brightness++)
  {
    rok->lightWrite(lightModule, brightness, color);
    Serial.println(brightness);
    delay(2);
  }
  
  // ramp down brightness
  for (brightness = 1023; brightness >= 0; brightness--)
  {
    rok->lightWrite(lightModule, brightness, color);
    Serial.println(brightness);
    delay(2);
  }

  // alternate colors
  if (color == GREEN)
    color = RED;
  else
    color = GREEN;

}