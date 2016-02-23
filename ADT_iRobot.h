////////////////////////////////////////////////////////////////////////////////
/**
*	@file	ADT_iRobot.h
*	@author	Mario Chirinos Colunga, Daniel Bojórquez Rodríguez
*	@date	2016-22-02
*	@note	header template
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef ADT_iRobot_H
#define ADT_iRobot_H

#include <string>
#include <unistd.h>
#include "ADT_SerialPort.h"

/**
*	Headers of commands.
*/
typedef enum
{
	ADT_iRobot_RESET = 7, 
	ADT_iRobot_NUMBER_SENSORS = 17, 
	ADT_iRobot_STREAM_PACKET = 19, 
	ADT_iRobot_PASSIVE = 128,
	ADT_iRobot_SAFE = 131, 
	ADT_iRobot_FULL = 132, 
	ADT_iRobot_MOTORS = 138, 
	ADT_iRobot_LEDS = 139,
	ADT_iRobot_SONG = 140, 
	ADT_iRobot_DRIVEDIRECT = 145, 
	ADT_iRobot_STREAM =148, 
	ADT_iRobot_CONTROL_STREAM = 150, 
	ADT_iRobot_SEGMENTS = 164, 
	ADT_iRobot_STOP = 173,	
}ADT_iRobot_commands;
//------------------------------------------------------------------------------
/**
*	Control of main brush,side brush and vacuum.
*/
typedef enum
{
	SIDE_BRUSH = 1,
	VACUUM = 2,
	MAIN_BRUSH = 4,
	OPPOSITE_SIDE_BRUSH = 8,
	OPPOSITE_MAIN_BRUSH = 16,
}ADT_iRobot_MOTORS_COMMAND;
//------------------------------------------------------------------------------
/**
*	Modes control ADT_iRobot.
*/
typedef enum
{
	PASSIVE = 1,
	SAFE = 2,
	FULL = 4,
}ADT_iRobot_MODE_COMMAND;
//------------------------------------------------------------------------------
/**
*	Leds control ADT_iRobot.
*/
typedef enum
{
	DEBRIS_LED=1,
	SPOT_LED=2,
	DOCK_LED=4,
	CHECK_LED=8
}ADT_iRobot_LED_COMMAND;
//------------------------------------------------------------------------------
/**
*	List of status of sensors. 
*/
using namespace std;
typedef struct
{
	unsigned short int batteryCharge;
	short int current;
	unsigned short int voltage;
	char temperature;
	bool wall;
	unsigned short int cliffLeft;
	unsigned short int cliffFrontleft;
	unsigned short int cliffFrontright;
	unsigned short int cliffRight;
	unsigned char bumps;
	unsigned char dirtDetect;
	short int velocityRight;
	short int velocityLeft;
	unsigned char buttons;
	unsigned char infraredCharacterommi;
	unsigned char infraredCharacterleft;
	unsigned char infraredCharacterright;
}ADT_iRobot_Status;
//------------------------------------------------------------------------------
/**
*	List of sensors of the ADT_iRobot.
*/
typedef enum
{
	BUMPS = 1,
	WALL = 2,
	CLIFF_LEFT = 4,
	CLIFF_FRONT_LEFT = 8,
	CLIFF_FRONT_RIGHT = 16,
	CLIFF_RIGHT = 32,
	DIRT_DETECT = 64,
	BUTTONS = 128,
	VOLTAGE = 256,
	CURRENT = 512,
	TEMPERATURE = 1024 ,
	BATTERYCHARGE = 2048,
	VELOCITY_RIGHT = 4096,
	VELOCITY_LEFT = 8192,
	INFRARED_CHARACTER_OMMI = 16384,
	INFRARED_CHARACTER_LEFT = 32768,
	INFRARED_CHARACTER_RIGHT = 65536,
}ADT_iRobot_Sensors;
//------------------------------------------------------------------------------
/**
*	Numbers packets of sensors. 
*/
typedef enum
{
	ADT_iRobot_PACKETID_BUMPS = 7,
	ADT_iRobot_PACKETID_WALL = 8,
	ADT_iRobot_PACKETID_DIRT_DETECT = 15,
	ADT_iRobot_PACKETID_INFRARED_CHARACTER_OMMI = 17,
	ADT_iRobot_PACKETID_BUTTONS = 18,
	ADT_iRobot_PACKETID_VOLTAGE = 22,
	ADT_iRobot_PACKETID_CURRENT = 23,
	ADT_iRobot_PACKETID_TEMPERATURE = 24 ,
	ADT_iRobot_PACKETID_BATTERYCHARGE = 25,
	ADT_iRobot_PACKETID_CLIFF_LEFT = 28,
	ADT_iRobot_PACKETID_CLIFF_FRONT_LEFT = 29,
	ADT_iRobot_PACKETID_CLIFF_FRONT_RIGHT = 30,
	ADT_iRobot_PACKETID_CLIFF_RIGHT = 31,
	ADT_iRobot_PACKETID_VELOCITY_RIGHT = 41,
	ADT_iRobot_PACKETID_VELOCITY_LEFT = 42,
	ADT_iRobot_PACKETID_INFRARED_CHARACTER_LEFT = 52,
	ADT_iRobot_PACKETID_INFRARED_CHARACTER_RIGHT = 53,
}ADT_iRobot_packets;
//------------------------------------------------------------------------------
class ADT_iRobot: private ADT_SerialPort
{
 private:
	int sendCommand(unsigned char* command, int size) const;
	ADT_iRobot_Status readStatus(unsigned char* streamBuffer, int streamLength);
	virtual void onGetData();
	ADT_iRobot_Status status;
	int RxStatus = 0;  /**<RxStatus mode of reception*/

 public:
	void reset();
	void beep() const;
	void stop() const;
	void setMode(ADT_iRobot_MODE_COMMAND mode)const;
	void setMotors(ADT_iRobot_MOTORS_COMMAND motors) const;
	void setSpeed(int speed_right,int speed_left) const;
	void setSegments(const char digit[4]) const;
	void setLEDs(ADT_iRobot_LED_COMMAND ledbits, unsigned char color,unsigned char intensity) const;
	ADT_iRobot_Status getStatus() const;
	void starStream(ADT_iRobot_Sensors sensors);
	void pauseStream();
	ADT_iRobot(const char* portName);
	~ADT_iRobot(); 
};
//------------------------------------------------------------------------------
#endif
