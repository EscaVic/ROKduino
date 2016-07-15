//RokduinoConstants.h header file 2.0.0
// Matthew Woodley, Nick Morozovsky, Victor Wang
// 11/29/2015
  
#ifndef ROKDUINOCONSTANTS_H
#define ROKDUINOCONSTANTS_H
 
 
//============================= MOTOR DECLARATIONS =====================================//
//Define motor ctrl pins to uC

//H-bride directional pin mapped to digital pin 23.  
#define MOTOR_1_DIR       23         
//PWM output mapped to digital pin 11
#define MOTOR_1_SPEED     11      
#define MOTOR_2_DIR       14
#define MOTOR_2_SPEED      6
#define MOTOR_3_DIR        4
#define MOTOR_3_SPEED      3
#define MOTOR_4_DIR       12     
#define MOTOR_4_SPEED     13
 
#define CLOCKWISE 0
#define COUNTER_CLOCKWISE 1
#define GREEN CLOCKWISE
#define RED COUNTER_CLOCKWISE
   
//============================= LED CONTROL/SENSE DECLARATIONS =========================//
 
#define LED_OFF     0
#define LED_ON      1
#define LED_TOGGLE  2 
#define LED_LEFT    0
#define LED_RIGHT   1
#define LED_BOTH    2 
 
//============================ SENSOR DECLARATIONS =====================================//
 
#define SENSOR_1    21	//analog A3
#define SENSOR_2    22	//analog A4
#define SENSOR_3    19  //analog A1
#define SENSOR_4   	20	//analog A2
#define SENSOR_5    9   //
#define SENSOR_6  	10   //
#define SENSOR_7  	18   //analog A0
#define SENSOR_8  	2   //
 
//============================ BATTERY READ DECLARATIONS===============================//
 
//battery read scaling factor
#define BATT_SCALE_FACTOR  5.0/1023.0 
//analog A8
#define BATT_READ_PIN      8
 
//========================== READ IR ==============================================//
 
#define IR_RX_PIN     2     // maps to sensor port 3
#define BITS_IN       19 
 
//========================== WRITE IR ==============================================//
#define PULSE           107 // can try tuning this parameter for more reliable messaging
#define START_BIT_ON    368-7
#define BIT_ON          105-7
#define BIT_0_OFF       211-7
#define BIT_1_OFF       399-7
#define STOP_BIT_ON     200-7
#define BITS_OUT        BITS_IN - 1
 
// commands
#define CMD_STOP 0x00
 
// directional pad
#define CMD_FORWARD 0x0F
#define CMD_FORWARD_RIGHT 0x3F
#define CMD_FORWARD_LEFT 0x37
#define CMD_BACKWARD 0x0E
#define CMD_BACKWARD_RIGHT 0x3E
#define CMD_BACKWARD_LEFT 0x36
#define CMD_SPIN_RIGHT 0x39
#define CMD_SPIN_LEFT 0x31
 
// right forefinger button + directional pad
#define CMD_FORWARD_SLOW 0x0B
#define CMD_FORWARD_RIGHT_SLOW 0x3B
#define CMD_FORWARD_LEFT_SLOW 0x33
#define CMD_BACKWARD_SLOW 0x0A
#define CMD_BACKWARD_RIGHT_SLOW 0x3A
#define CMD_BACKWARD_LEFT_SLOW 0x32
#define CMD_SPIN_RIGHT_SLOW 0x3D
#define CMD_SPIN_LEFT_SLOW 0x35
 
// Legacy commands for compatibility with ROK star vehicles
#define CMD_MOTOR_3_FORWARD 0x47
#define CMD_MOTOR_3_BACKWARD 0x46
#define CMD_MOTOR_3_STOP 0x44
#define CMD_MOTOR_4_FORWARD 0x4F
#define CMD_MOTOR_4_BACKWARD 0x4E
#define CMD_MOTOR_4_STOP 0x4C

// Maker ROK-Bot Motor Modules Commands
#define CMD_XY_MOTOR_CLOCKWISE CMD_MOTOR_3_BACKWARD			// Y button
#define CMD_XY_MOTOR_COUNTER_CLOCKWISE CMD_MOTOR_3_FORWARD	// X button
#define CMD_AB_MOTOR_CLOCKWISE CMD_MOTOR_4_BACKWARD			// B button
#define CMD_AB_MOTOR_COUNTER_CLOCKWISE CMD_MOTOR_4_FORWARD	// A button

#define CMD_Y_BUTTON CMD_MOTOR_3_BACKWARD			// Y button
#define CMD_X_BUTTON CMD_MOTOR_3_FORWARD	// X button
#define CMD_B_BUTTON CMD_MOTOR_4_BACKWARD			// B button
#define CMD_A_BUTTON CMD_MOTOR_4_FORWARD	// A button
 
#define CMD_TRIM_RIGHT 0x67     // left forefinger + right buttons
#define CMD_TRIM_LEFT 0x66      // left forefinger + left buttons
#define CMD_HORN 0x65           // what button combination?
#define CMD_CRUISE_CONTROL 0x64 // left forefinger + X buttons
#define CMD_FLASH_Y 0x63        // left forefinger + Y buttons
#define CMD_HORN_CHANGE 0x62    // left forefinger + A buttons
#define CMD_MUTE_TOGGLE 0x61    // left forefinger + B buttons
#define CMD_SIREN_TOGGLE 0x68   // button 1
#define CMD_SOUND_1 0x69        // button 2
#define CMD_SOUND_2 0x6B        // button 4 (?)
#define CMD_SOUND_3 0x6C        // left forefinger + button 1
#define CMD_SOUND_4 0x6D        // left forefinger + button 2
#define CMD_SOUND_5 0x6E        // left forefinger + button 3
#define CMD_SOUND_6 0x6F        // left forefinger + button 4
 
#define CMD_HEY_YOU 0x7F        // ROK star button

static const unsigned long ONE = 1;
const unsigned long CMD_TIMEOUT = 1000000; // microseconds, 1000000 = 1 sec

//=========================== SPEAKER ================================================//
#define SPEAKER_UP   15   //+SPEAKER Defines high pin for speaker
#define SPEAKER_DOWN 16       //-SPEAKER


#endif
