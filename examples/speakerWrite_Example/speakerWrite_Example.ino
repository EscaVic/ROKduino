#include "ROKduino.h"
// Pointer to ROKduino lib
ROKduino* rok;

// Melody (liberated from the toneMelody Arduino example sketch by Tom Igoe).
int melody[] = { 262, 196, 196, 220, 196, 0, 247, 262 };
int noteDurations[] = { 4, 8, 8, 4, 4, 4, 4, 4 };
int numNotes = 8;

void setup() {
  // put your setup code here, to run once:
  // Get singleton reference to ROKduino
  rok = ROKduino::getInstance();

  for (int thisNote = 0; thisNote < numNotes; thisNote++)
  { // Loop through the notes in the array.
    int noteDuration = 1000/noteDurations[thisNote];
    rok->speakerWrite(melody[thisNote], noteDuration); // Play thisNote for noteDuration.
    delay(noteDuration * 4 / 3); // Wait while the tone plays in the background, plus another 33% delay between notes.
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}