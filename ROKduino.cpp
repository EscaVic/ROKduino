//Rokduino.h header file 2.0.0
//Matthew Woodley, Nick Morozovsky and Victor Wang
// 11/29/2015
 
 
#include "ROKduino.h"
 
 
/* Index
 
0. Constructor 
   a. Sensors (digital/analog)
   b. Motors
   c. Interrupt
 
1. motorWrite()
 
2. LED
   a. ledWrite()
   a. getLEDSstatus()
 
3. readSensor()
 
4. batteryRead()
 
5. IR_TX 
 
6. IR_RX
 
*/
 

// Static member declarations
ROKduino* ROKduino::instance = 0;
unsigned long ROKduino::lastTimestamp = micros();
byte ROKduino::count = 0;
unsigned long ROKduino::timestamp = 0;
unsigned long ROKduino::dt = 0;
unsigned long ROKduino::message = 0;
volatile unsigned long ROKduino::cmdTimestamp = 0;
volatile byte ROKduino::address = 0;
volatile byte ROKduino::command = 0;
uint8_t* ROKduino::_pinMode1 = 0;
uint8_t* ROKduino::_pinMode2 = 0;
volatile uint8_t* ROKduino::_pinOutput1 = 0;
volatile uint8_t* ROKduino::_pinOutput2 = 0;
uint8_t ROKduino::_pinMask1 = 0;
uint8_t ROKduino::_pinMask2 = 0;
uint8_t ROKduino::_speakerOn = 0;
unsigned long ROKduino::_nt_time = 0;

 
// ====================== Constructor ==================================================//
//=====================================================================================//
 
ROKduino::ROKduino()
{
   //======================== Sensor pins assignments ==================================// 
   // Define sensor by type. 
 
   //Sensors 1-3 are digital inputs. Internal pullup resistors are enabled 
   pinMode(SENSOR_1, INPUT_PULLUP);  
   pinMode(SENSOR_2, INPUT_PULLUP);  
   pinMode(SENSOR_3, INPUT_PULLUP);
 
   //Sensors 4-8 are analog input. 
   pinMode(SENSOR_4, INPUT);       
   pinMode(SENSOR_5, INPUT);
   pinMode(SENSOR_6, INPUT);
   pinMode(SENSOR_7, INPUT);
   pinMode(SENSOR_8, INPUT);  
 
   //========================= MotorPins Speed/Dir assignments ==========================//
   // Two parameters, speed and direction for each.
   // Direction is defined are boolean defined as CLOCKWISE(0) and COUNTERCLOCKWISE(1)
   // Speed is mapped to an 8 bit PWM function (0-255).  ?? three constant speeds
 
   //Motor 1-
   pinMode(MOTOR_1_DIR, OUTPUT);      
   pinMode(MOTOR_1_SPEED, OUTPUT);
   
   //Motor 2- 
   pinMode(MOTOR_1_DIR, OUTPUT);
   pinMode(MOTOR_2_SPEED, OUTPUT);
  
   //Motor 3-
   pinMode(MOTOR_3_DIR, OUTPUT);
   pinMode(MOTOR_3_SPEED, OUTPUT);
  
   //Motor 4-
   pinMode(MOTOR_4_DIR, OUTPUT);
   pinMode(MOTOR_4_SPEED, OUTPUT);
 
 
   //========Interrupt
    attachInterrupt(1, irRX, FALLING);
     
   //_pinMask2   = digitalPinToBitMask(SPEAKER_DOWN);
   // Get the port register bitmask for pin 2.
 
}//END CONSTRUCTOR==================================//
//=================================================//
 
 
 
// 1.
//======================= motorWrite() Function ========================================//
//======================================================================================//
 
 
//motorWrite() three parameters
//void functions selects motor to set direction and speed via PWM
//motor selected from motor 1-4
//mtr_speed selects speed of motor 10 bit (0-1023) mapped to PWM output
//direction boolean value of CLOCKWISE(0) or COUNTER_CLOCKWISE(1) 
//Switch statement selects motor number where the corresponding speed and direction are assigned
 
void ROKduino::motorWrite(byte motor, int mtr_speed, boolean dir)
{
   switch(motor)
   { 
      case 1:
         analogWrite(MOTOR_1_SPEED, abs(mtr_speed)/4);
         digitalWrite(MOTOR_1_DIR, dir);
         break;
      case 2:
         analogWrite(MOTOR_2_SPEED, abs(mtr_speed)/4);
         digitalWrite(MOTOR_2_DIR, dir);
         break;
      case 3:
         analogWrite(MOTOR_3_SPEED, abs(mtr_speed)/4);
         digitalWrite(MOTOR_3_DIR, dir);
         break;
      case 4:
         analogWrite(MOTOR_4_SPEED, abs(mtr_speed)/4);
         digitalWrite(MOTOR_4_DIR, dir);
         break;

   }//END MOTOR SWITCH STATEMENT
}//END motorWrite() Functions ========================//
//===================================================//
 
void ROKduino::motorWrite(byte motor, int mtr_velocity)
{
   if (mtr_velocity > 0)
   {
       motorWrite(motor, mtr_velocity, COUNTER_CLOCKWISE);
   }
   else
   {
       motorWrite(motor, -mtr_velocity, CLOCKWISE);
   }
}
 
//---2.
//======================== ledWrite() Function========================================//
//====================================================================================// 
 
//Takes in two parameters
//Void function, sets LEDs ON/OFF and sets corresponding LED state variable
//which selects left LED(0), right LED(1) or both (2)
//mode selects ON(1), OFF(0) OR TOGGLE(2). Toggle changes from previous state.
//Used to turn selected LED(s) ON/OFF
//LEDs are TX/RX LEDs. Uses defined Arduino functions to control LEDs
//TXLED0(OFF)/ TXLED1(ON) left LED
//RXLED0(OFF)/ TXLED1(ON) right LED
 
 
void ROKduino::ledWrite(byte which, byte mode)
{
   switch(which)
   {
      case LED_LEFT:
         switch(mode)
         {
            case LED_OFF:
               TXLED0;
               _leftLEDstate = 0;
               break;
            case LED_ON:
               TXLED1;
               _leftLEDstate = 1;
               break;
            case LED_TOGGLE:
               ledWrite(LED_LEFT, !_leftLEDstate);
               break;
            default:
               break;
         }
         break;         
      case LED_RIGHT:
         switch(mode)
         {
            case LED_OFF:
               RXLED0;
               _rightLEDstate = 0;
               break;
            case LED_ON:
               RXLED1;
               _rightLEDstate = 1;
               break;
            case LED_TOGGLE:
               ledWrite(LED_RIGHT, !_rightLEDstate);
               break;
            default:
               break;
         }
         break;
     
      case LED_BOTH:
         ledWrite(LED_LEFT, mode);
         ledWrite(LED_RIGHT, mode);
         break;
      default:
         break;
     
   } //END LED SWTICH STATEMENT
}//End ledWrite() Function ====================//
//============================================//
 
 
//---3.
// ==============================sensorRead() Function============================================//
//===============================================================================================//
 
//Takes in one parameter
//Returns a integer value constrained between 0-1023
//sensor selects sensor 1-8
//Sensors 1-3 are digital inputs
//digital inputs use digitalRead function and maps logic 0 = 0 and logic 1 = 1023
//Sensors 4-8 are analog inputs  
//analog inputs that read 10 bits of resolution and assigns any value between 0 and 1023
 
int ROKduino::sensorRead(byte sensor)
{
   int senseIn;

   switch(sensor)
   {  
      case 1:
         senseIn = 1023*digitalRead(SENSOR_1);
         break;
      case 2:
         senseIn = 1023*digitalRead(SENSOR_2);
         break;
      case 3:
         senseIn = 1023*digitalRead(SENSOR_3);
         break;
      case 4:
         senseIn = analogRead(SENSOR_4);//maybe have to declare A2 instead of 20??
         break;
      case 5:
         senseIn = analogRead(SENSOR_5);
         break;
      case 6:
         senseIn = analogRead(SENSOR_6);
         break;
      case 7:
         senseIn = analogRead(SENSOR_7);
         break;
      case 8:
         senseIn = analogRead(SENSOR_8);
         break;
      default:
         senseIn = -1;  //BETTER ERROR PROTECTION???
         break;  
   }//END SENSOR READ SWTICH STATEMENT
   
   return senseIn;
 
}//END sensorRead() Function ==========================//
//====================================================//
 
 
 
//---4. 
// ==============================batteryRead() Function==========================================//
//===============================================================================================//
 
 
//Takes in no parameters
//returns float value of battery voltage scaled by factor
 
float ROKduino::batteryRead()
{
   return BATT_SCALE_FACTOR * analogRead(BATT_READ_PIN); 
}//END batteryRead()===================================//
 
 
 
//---6.
// ==============================addressRead() Function==========================================//
//===============================================================================================//
 
byte ROKduino::addressRead()
{
   return address;
}//END addressRead()======================================//
 
 
 
//---7.
// ==============================addressWrite() Function==========================================//
//===============================================================================================//
 
void ROKduino::addressWrite(byte newAddress)
{
   address = newAddress;
}//END addressWrite()=======================================//
 
 
 
//---8.
// ==============================irWrite() and supporting functions===============================//
//()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()//
//===============================================================================================//
 
//===================IR MESSAGE FORMAT================//
//startBits{0:1]
//command[3:9]
//address[10:18]
//stopBits[19]
//================================================//
 
 
 
//---8a.
// ============================== cycles() function ==================================================//
//Takes in three parameters 
//pin-pin number to be cycled
//duration-amount of microseconds delayed between ON/OFF cycles
//Pulses pins and returns nothing
 
void ROKduino::cycle(byte pin, int duration)
{ 
   digitalWrite(pin, HIGH);
   delayMicroseconds(duration);
   digitalWrite(pin, LOW);
   delayMicroseconds(duration);
}//END cycle()==============================//
 
 
//---8c.
// ==============================checkSumCalc() function==============================================//
 
byte ROKduino::checkSumCalc(byte address, byte command)
{ 
   return ( ((address>>4) & (1<<4)-1) + (address & (1<<4)-1) + ((command>>4) & (1<<4)-1) + (command & (1<<4)-1)  & (1<<3)-1); 
}//END checkSumCalc()=======================//
 
 
 
//---8d
// ==============================irWrite() function==============================================//
 
 
void ROKduino::irWrite(byte sensor, byte command, byte address)
{
   // disable interrupts
   detachInterrupt(1); // IR Comm RX - this does work, or compile at least
   
   // calculate checksum
   unsigned long message = (address<<10 | command<<3 | checkSumCalc(address, command)); // combine address, command, and checksum
 
   pinMode(SENSOR_PINS[sensor], OUTPUT);
 
   // 1 start bit
   //cycle(SENSOR_PINS[sensor], 2*PULSE);
   digitalWrite(SENSOR_PINS[sensor], HIGH);
   delayMicroseconds(START_BIT_ON);
   digitalWrite(SENSOR_PINS[sensor], LOW);
   delayMicroseconds(BIT_0_OFF);
   
   //RECS80 IR data format pulses consist of 3-4 cycles.  One HIGH cycle and either two HIGH cycles (bit=0) or three    
   //cycles (bit=1)

   for (int i = 0; i < BITS_OUT; i++)  
   {
      //cycle(SENSOR_PINS[sensor], PULSE);
      digitalWrite(SENSOR_PINS[sensor], HIGH);
      delayMicroseconds(BIT_ON);
      digitalWrite(SENSOR_PINS[sensor], LOW);
      
      // (bit=1 --> long pulse)
      if ((message>>(BITS_OUT-i-1)) & 1 )
      {
         delayMicroseconds(BIT_1_OFF);
         //delayMicroseconds(2*PULSE); 
      }
      else // (bit=0 --> short pulse)
      {
         delayMicroseconds(BIT_0_OFF);
         //delayMicroseconds(PULSE); // short delay
      }
     
   }//END for loop
   
   // 1 stop bit
   //cycle(SENSOR_PINS[sensor], PULSE);
   digitalWrite(SENSOR_PINS[sensor], HIGH);
   delayMicroseconds(STOP_BIT_ON);
   digitalWrite(SENSOR_PINS[sensor], LOW);
   delayMicroseconds(BIT_0_OFF);
   
   // re-attach interrupts
   attachInterrupt(1, irRX, FALLING);
 
}//END irWrite()===================================//
 
 
   
//---9.
// ==============================irRead() and supporting functions===============================//
//()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()//
//===============================================================================================//
 
//===================IR MESSAGE FORMAT================//
//startBits{0:1]
//command[3:9]
//address[10:18]
//stopBits[19]
//================================================//
 
// ==============================irRead() Function==========================================//
//===============================================================================================//
 
byte ROKduino::irRead()
{ 
   //check for timeout
   if ( ( (micros()) - cmdTimestamp ) > CMD_TIMEOUT )
   {
      command = 0;
   }
 
   return command;
}//END irRead()======================================//
 
 
//---9a.
// ==============================irRead() function==============================================//
 
 
void ROKduino::irRX()
{
   //Takes in no parameters and is triggered by interrupt #1 on pin 2.  Each time there is a falling edge, the 
   //it determines the length of pulse.  If it has been 600us or longer since last interrupt has been triggered
   //it will be considered a new incoming message.  
 
   // overflow may cause one missed message                              
   timestamp = micros();
   dt = timestamp - lastTimestamp;
   lastTimestamp = timestamp;
   
   // If time since last time diff 600us or greater it is a new packet count will be set to zero
   if (dt > 599)
   {
      count = 0;
   }
   //If value is less than 600us, values greater than 400us set current message bit to 1.  
   //if value is less, it is a zero. bits are shifted in as 1s. 
   else
   {
      // long dt is 1
      if (dt > 400)
      {
         message |= (ONE << (BITS_IN-count-1));
      }
      //else short dt is 0
      count++;
   }
 
   //if maxed bits are received, receiveCmd() is called then message and count are reset to zero
   if (count >= BITS_IN)
   {
      ROKduino::receiveCmd(); // TODO: make receiveCmd() static also?
      message = 0;
      count = 0;
   }
}//END irRX() function=============================//
 
 
 
//---9b.
// ================================receiveCmd() function==============================================//
 
 
void ROKduino::receiveCmd()
{
   //takes in no parameters takes incoming message captured in readIR
   //parses bit stream into a message (msgAddr), a command (ma
 
   //Serial.print(message, BIN);
   //Serial.print("\t");
   byte msgAddr = (message>>10) & (1<<8)-1;
   byte msgCmd = (message>>3) & (1<<7)-1;
   byte msgChk = message & (1<<3)-1;
   
   /*Serial.print(msgAddr, BIN);
   Serial.print("\t");
   Serial.print(msgCmd, BIN);
   Serial.print("\t");
   Serial.println(msgChk, BIN);//*/
   
   //byte chk = ( ((msgAddr>>4) & (1<<4)-1) + (msgAddr & (1<<4)-1) + ((msgCmd>>4) & (1<<4)-1) + (msgCmd & (1<<4)-1)  & (1<<3)-1);
   //Serial.print("\t");
   //Serial.println(chk, BIN);
   
   // checksum matches
   if (msgChk == ROKduino::checkSumCalc(msgAddr, msgCmd))
   {
      if (msgCmd == CMD_HEY_YOU)  // if "hey you" set address
      {
         address = msgAddr;
         command = 0;
         cmdTimestamp = timestamp;
         //Serial.print("Hey you \t");
         //Serial.println(msgAddr, BIN);
      }
      else if (msgAddr == address) // check address
      {
         command = msgCmd;
         cmdTimestamp = timestamp;
         //Serial.println(command, BIN);
      }
      //else // address doesn't match
      //Serial.println("address doesn't match");
   }
   //else // checksum doesn't match
    //Serial.println("checksum fail");
}//END receiveCmd() function=============================//
  
 
 
// =========================Proximity Sensor========================================================//
 
int ROKduino::proximityRead(byte TXpin, byte RXpin)
{
   if (TXpin != RXpin)
   {
      pinMode(SENSOR_PINS[TXpin], OUTPUT);
      digitalWrite(SENSOR_PINS[TXpin], HIGH);
      delay(1); 
      int ProxIn = 1023 * !digitalRead(SENSOR_PINS[RXpin]);   
      digitalWrite(SENSOR_PINS[TXpin], LOW);
      return ProxIn;
   }
   // error, TXpin cannot equal RXpin, should also check that both [1,8]?
   else 
   {
      return -1;
   }
}
 

void ROKduino::speakerWrite(unsigned long frequency, unsigned long duration)
{
   if (frequency > 0)
   {
      uint8_t prescaler = _BV(CS30);                 // Try using prescaler 1 first.
      unsigned long top = F_CPU / frequency / 4 - 1; // Calculate the top.
      if (top > 65535)                             // If not in the range for prescaler 1, use prescaler 256 (61 Hz and lower @ 16 MHz).
      {
         prescaler = _BV(CS32);                       // Set the 256 prescaler bit.
         top = top / 256 - 1;                         // Calculate the top using prescaler 256.
      }
 
      if (duration > 0)
      {
         _nt_time = millis() + duration; 
      }
      else
      {
         _nt_time = 0xFFFFFFFF; // Set when the note should end, or play "forever".
      }
 
      if (_speakerOn == 0) // This gets the port registers and bitmaps for the two pins and sets the pins to output mode.
      {
         // can make these all constants once it's tested?
         // Get the port register bitmask for pin 1.
         _pinMask1 = digitalPinToBitMask(SPEAKER_UP); 
         // Get the port register bitmask for pin 2.
         _pinMask2 = digitalPinToBitMask(SPEAKER_DOWN);                            
         // Get the output port register for pin 1.         
         _pinOutput1 = portOutputRegister(digitalPinToPort(SPEAKER_UP));
         // Get the output port register for pin 2.     
         _pinOutput2 = portOutputRegister(digitalPinToPort(SPEAKER_DOWN));           
         // Get the port mode register for pin 1.
         _pinMode1 = (uint8_t *) portModeRegister(digitalPinToPort(SPEAKER_UP)); 
         // Get the port mode register for pin 2.
         _pinMode2 = (uint8_t *) portModeRegister(digitalPinToPort(SPEAKER_DOWN)); 
             
         *_pinMode1 |= _pinMask1; // Set pin 1 to Output mode.
         *_pinMode2 |= _pinMask2; // Set pin 2 to Output mode.
      }
 
      ICR3    = top;                     // Set the top.
      if (TCNT3 > top)
      {
         TCNT3 = top;      // Counter over the top, put within range.
      }
      TCCR3B  = _BV(WGM33) | prescaler; // Set PWM, phase and frequency corrected (ICR1) and prescaler.
      TCCR3A  = _BV(COM3B0);
      if (*_pinOutput1 & _pinMask1)
      {
         *_pinOutput2 &= ~_pinMask2; // Be sure pins are reversed.
      }
      else
      {
         *_pinOutput2 |= _pinMask2;    // Other half of making sure pins are reversed.
      }
      TIMSK3 |= _BV(OCIE3A);             // Activate the timer interrupt.
   }
   else // stop tone
   {
      TIMSK3 &= ~_BV(OCIE3A);   // Remove the timer interrupt.
      TCCR3B  = _BV(CS31);      // Default clock prescaler of 8.
      TCCR3A  = _BV(WGM30);     // Set to defaults so PWM can work like normal (PWM, phase corrected, 8bit).
      *_pinMode1 &= ~_pinMask1;   // Set pin 1 to INPUT.
      *_pinMode2 &= ~_pinMask2;   // Set pin 2 to INPUT.
      _speakerOn= 0; // Flag so we know note is no longer playing.
   }
}

unsigned long ROKduino::getEndNoteTime()
{
   return _nt_time;
}


void ROKduino::togglePinState()
{
   *_pinOutput1 ^= _pinMask1; // Toggle the pin 1 state.
   *_pinOutput2 ^= _pinMask2; // Toggle the pin 2 state.   
}
 
ISR(TIMER3_COMPA_vect)
{ // Timer interrupt vector.
   if (millis() >= ROKduino::getInstance()->getEndNoteTime())
   {
      ROKduino::getInstance()->speakerWrite(0); // Check to see if it's time for the note to end.
   }
   ROKduino::getInstance()->togglePinState();
}//*/

// Singleton
ROKduino* ROKduino::getInstance()
{
   if (0 == instance)
   {
      // Create object for 1st time
      instance = new ROKduino();
   }

   return instance;
}

