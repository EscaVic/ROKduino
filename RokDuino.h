//Rokduino.h header file 2.0.0
//Matthew Woodley, Nick Morozovsky and Victor Wang
// 11/18/2015
 
 
#ifndef ROKDUINO_H
#define ROKDUINO_H
 
#include "Arduino.h"
#include "RokDuinoConstants.h" 
 
class ROKDuino
{
   public:

      ROKDuino();
      static void speakerWrite(unsigned long frequency, unsigned long duration = 0);
   
      void motorWrite(byte motor, int mtr_speed, boolean dir);
      void motorWrite(byte motor, int mtr_velocity);
 
      void ledWrite(byte which, byte mode);
  
      int sensorRead(byte sensor);
 
      float batteryRead();

      static void irRX(); 
 
      static void receiveCmd();
      void addressWrite(byte address);
      byte addressRead();
      byte irRead();
  
      void irWrite(byte sensor, byte command, byte address = 0);
      void cycle(byte pin, int duration);
      static byte checkSumCalc(byte address, byte command);
 
 
      //===================== Proximity Sensor============================================//
 
      int proximityRead(byte TXpin, byte RXpin);

      static void togglePinState();
      static unsigned long getEndNoteTime();

      // Singleton
      static ROKDuino* getInstance(); 
 
private:
 
      boolean _rightLEDstate = 0;
      boolean _leftLEDstate = 0;  
 
      int SENSOR_PINS[9] = {0, SENSOR_1, SENSOR_2, SENSOR_3, SENSOR_4, SENSOR_5, SENSOR_6, SENSOR_7, SENSOR_8};

 
      static ROKDuino* instance;
      static unsigned long lastTimestamp;
      static byte count;
      static unsigned long timestamp;
      static unsigned long dt;
      static unsigned long message;
      static volatile unsigned long cmdTimestamp;
      static volatile byte address;
      static volatile byte command;
      static uint8_t* _pinMode1;
      static uint8_t* _pinMode2; // Pin modes.
      static uint8_t _pinMask1; // Bitmask for pins.
      static uint8_t _pinMask2; // Bitmask for pins.
      static volatile uint8_t* _pinOutput1;
      static volatile uint8_t* _pinOutput2; // Output port registers for each pin.
      static uint8_t _speakerOn;
      static unsigned long _nt_time;       // Time note should end.
 
 
 
};//End header declarations
#endif
