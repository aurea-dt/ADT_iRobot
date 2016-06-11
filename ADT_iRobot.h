////////////////////////////////////////////////////////////////////////////////
/**
*	@file	ADT_iRobot.h
*	@author	Mario Chirinos Colunga, Daniel Bojórquez Rodríguez
*	@date	2016/02/22 - 2016/06/09
*	@note	This code provides an API to control the iRobot create 2 platform
*		in form of an object ADT_iRobot.
		The code is based on the specifications described on 
*		the iRobot® Create® 2 Open Interface documentation [1] and our
*		serial port API [2]. It depends on glib for socket callbacks. 
*
*		[1] https://cdn-shop.adafruit.com/datasheets/create_2_Open_Interface_Spec.pdf
*		[2] https://github.com/aurea-dt/serialPortAPI
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef ADT_iRobot_H
#define ADT_iRobot_H

#include <string>
#include <unistd.h>
#include "ADT_SerialPort.h"
using namespace std;
/**
*	Command headers
*/
typedef enum
{
	ADT_iRobot_RESET 		= 7, 
	ADT_iRobot_NUMBER_SENSORS	= 17, 
	ADT_iRobot_STREAM_PACKET 	= 19, 
	ADT_iRobot_PASSIVE 		= 128,
	ADT_iRobot_BAUD 		= 129,
	ADT_iRobot_SAFE 		= 131, 
	ADT_iRobot_FULL 		= 132,
	ADT_iRobot_POWER_OFF 		= 133,
	ADT_iRobot_CLEAN_SPOT		= 134,
	ADT_iRobot_CLEAN 		= 135,
	ADT_iRobot_CLEAN_MAX 		= 136,
	ADT_iRobot_DRIVE 		= 137,
	ADT_iRobot_MOTORS 		= 138, 
	ADT_iRobot_LEDS 		= 139,
	ADT_iRobot_SONG 		= 140,
	ADT_iRobot_PLAY 		= 141,
	ADT_iRobot_SENSORS 		= 142,
	ADT_iRobot_DOCK 		= 143,
	ADT_iRobot_PWM_MOTORS 		= 144,
	ADT_iRobot_DRIVE_DIRECT 	= 145, 
	ADT_iRobot_DRIVE_PWM 		= 146,
	ADT_iRobot_STREAM 		= 148,
	ADT_iRobot_QUERY_LIST 		= 149,
	ADT_iRobot_CONTROL_STREAM 	= 150, 
	ADT_iRobot_SCHUDULE_LEDS	= 162,
	ADT_iRobot_DIGIT_LED_RAW	= 163,
	ADT_iRobot_LED_ASCII		= 164,
	ADT_iRobot_BUTTONS		= 165,
	ADT_iRobot_SCHUDULE		= 167,
	ADT_iRobot_DAYTIME		= 168,
	ADT_iRobot_STOP 		= 173,	
}ADT_iRobot_commands;
//------------------------------------------------------------------------------
/**
*	iRobot motors flags.
*/
typedef enum
{
	SIDE_BRUSH 		= 1,
	VACUUM 			= 2,
	MAIN_BRUSH		= 4,
	OPPOSITE_SIDE_BRUSH 	= 8,
	OPPOSITE_MAIN_BRUSH 	= 16,
}ADT_iRobot_MOTORS_COMMAND;
//------------------------------------------------------------------------------
/**
*	iRobot control modes .
*/
typedef enum
{
	STOP,
	PASSIVE,
	SAFE,
	FULL,
}ADT_iRobot_MODE_COMMAND;
//------------------------------------------------------------------------------
/**
*	LEDs flags .
*/
typedef enum
{
	DEBRIS_LED	= 1,
	SPOT_LED	= 2,
	DOCK_LED	= 4,
	CHECK_LED	= 8
}ADT_iRobot_LED_COMMAND;

//------------------------------------------------------------------------------
/**
*	 Request package id. 
*/
typedef enum
{
	ADT_iRobot_PACKETID_BUMPS = 7,
	ADT_iRobot_PACKETID_WALL,
	ADT_iRobot_PACKETID_CLIFT_LEFT,
	ADT_iRobot_PACKETID_CLIFT_FRONT_LEFT,
	ADT_iRobot_PACKETID_CLIFT_FRONT_RIGHT,
	ADT_iRobot_PACKETID_CLIFT_RIGHT,
	ADT_iRobot_PACKETID_VIRTUAL_WALL,
	ADT_iRobot_PACKETID_WHEEL_OVERCURRENT,
	ADT_iRobot_PACKETID_DIRT_DETECT,
	ADT_iRobot_PACKETID_UNUSEDBYTE,
	ADT_iRobot_PACKETID_INFRARED_CHARACTER_OMMI,
	ADT_iRobot_PACKETID_BUTTONS,
	ADT_iRobot_PACKETID_DISTANCE,
	ADT_iRobot_PACKETID_ANGLE,
	ADT_iRobot_PACKETID_CHARGING_STATE,
	ADT_iRobot_PACKETID_VOLTAGE,
	ADT_iRobot_PACKETID_CURRENT,
	ADT_iRobot_PACKETID_TEMPERATURE,
	ADT_iRobot_PACKETID_BATTERY_CHARGE,
	ADT_iRobot_PACKETID_BATTERY_CAPACITY,
	ADT_iRobot_PACKETID_WALL_SIGNAL,
	ADT_iRobot_PACKETID_CLIFF_SIGNAL_LEFT,
	ADT_iRobot_PACKETID_CLIFF_SIGNAL_FRONT_LEFT,
	ADT_iRobot_PACKETID_CLIFF_SIGNAL_FRONT_RIGHT,
	ADT_iRobot_PACKETID_CLIFF_SIGNAL_RIGHT,
	
	ADT_iRobot_PACKETID_CHARGING_SOURCES = 34,
	ADT_iRobot_PACKETID_IO_MODE,
	ADT_iRobot_PACKETID_SONG_NUMBER,
	ADT_iRobot_PACKETID_SONG_PLAYING,
	ADT_iRobot_PACKETID_N_STREAM_PACKETS,
	ADT_iRobot_PACKETID_REQUESTED_VELOCITY,
	ADT_iRobot_PACKETID_REQUESTED_RADIUS,
	ADT_iRobot_PACKETID_REQUESTED_VELOCITY_RIGHT,
	ADT_iRobot_PACKETID_REQUESTED_VELOCITY_LEFT,
	ADT_iRobot_PACKETID_ENCODER_COUNT_LEFT,
	ADT_iRobot_PACKETID_ENCODER_COUNT_RIGHT,
	ADT_iRobot_PACKETID_ENCODER_LIGHT_BUMPER,	
	ADT_iRobot_PACKETID_ENCODER_LIGHT_BUMPER_SIGNAL_LEFT,
	ADT_iRobot_PACKETID_ENCODER_LIGHT_BUMPER_SIGNAL_FRONT_LEFT,
	ADT_iRobot_PACKETID_ENCODER_LIGHT_BUMPER_SIGNAL_CENTER_LEFT,
	ADT_iRobot_PACKETID_ENCODER_LIGHT_BUMPER_SIGNAL_CENTER_RIGHT,
	ADT_iRobot_PACKETID_ENCODER_LIGHT_BUMPER_SIGNAL_FRONT_RIGHT,
	ADT_iRobot_PACKETID_ENCODER_LIGHT_BUMPER_SIGNAL_RIGHT,
	ADT_iRobot_PACKETID_INFRARED_CHARACTER_LEFT,
	ADT_iRobot_PACKETID_INFRARED_CHARACTER_RIGHT,
	ADT_iRobot_PACKETID_MOTOR_CURRENT_LEFT,
	ADT_iRobot_PACKETID_MOTOR_CURRENT_RIGHT,
	ADT_iRobot_PACKETID_MAINBRUSH_CURRENT,
	ADT_iRobot_PACKETID_SIDEBRUSH_CURRENT,
	ADT_iRobot_PACKETID_STASIS
}ADT_iRobot_SensorPackets;
//------------------------------------------------------------------------------
/**
*	ADT_iRobot class. 
*/
class ADT_iRobot: private ADT_SerialPort
{
 private:
	int sendCommand(unsigned char* command, int size) const;
	int rxStatus;  /**<Reception mode*/
	int buildPacketList(unsigned char* sensorsList);
	virtual void onGetData();

 protected:
	int sensors[60];

 public:
	void reset();
	void stop() const;
	void setMode(ADT_iRobot_MODE_COMMAND mode)const;
	void beep() const;
	void setMotors(ADT_iRobot_MOTORS_COMMAND motors) const;
	void setDigitLED(const char digit[4]) const;
	void drive(int velocity, int radius);
	void setLEDs(ADT_iRobot_LED_COMMAND ledbits, unsigned char color,unsigned char intensity) const;
	void startStream(const char* sensorsList, unsigned char nSensors);
	void getQueryList(const char* sensorsList, unsigned char nSensors);
	void getSensor(ADT_iRobot_SensorPackets sensor);
	void pauseStream();
	ADT_iRobot(const char* portName);
	~ADT_iRobot(); 
};
//------------------------------------------------------------------------------

#endif

