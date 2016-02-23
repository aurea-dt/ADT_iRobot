////////////////////////////////////////////////////////////////////////////////
/**
*	@file	main.cpp
*	@author	Mario Chirinos Colunga, Daniel Bojórquez Rodríguez
*	@date	2016-22-02
*	@note	main file template
*/
////////////////////////////////////////////////////////////////////////////////
#include "ADT_iRobot_joystickControl.h"
#include<iostream>
#include<cstring>
#include <stdlib.h>

using namespace std;
/**
*	ADT_iRobot_joystickControl Class Constructor.
*
*	@param portName Serial port name.
*/
ADT_iRobot_joystickControl::ADT_iRobot_joystickControl(const char* portName):ADT_iRobot(portName)
{

}
//------------------------------------------------------------------------------
/**
*	ADT_iRobot_joystickControl Class Destructor.
*	to be implement. 
*/
ADT_iRobot_joystickControl::~ADT_iRobot_joystickControl()
{

}
//------------------------------------------------------------------------------
/**
*	Drive ADT_iRobot_joystickControl.
*	Receives the data for the joystick and send data processing 
*	to the robot.
*
*	@param number number of axis of the joystick.
*	@param value value of axis of the joystick.
*/
void ADT_iRobot_joystickControl::drive (int number, int value) 
{
	int left,right,move,turn,tcoeff,angle;
	float x=0,y=0,z,rad;

	switch(number) 
		{
			case 0: 
				x = value;
				break;
			case 1: 
				y=(-1*value);
				break;
		}
	
	x = x * (MAX_SPEED_ROBOT / (float)SHRT_MAX);
	y = y * (MAX_SPEED_ROBOT / (float)SHRT_MAX);

     	z = sqrt ((x*x)+(y*y));

    	rad = acos(((abs(x))/z));

     	angle = rad*(180/M_PI);
	
	tcoeff = -1 + (angle/90)*2;
    	turn = tcoeff * abs(abs(y) - abs(x));
		
	if(abs(x) > abs(y))
		move = abs(x);
	else if (abs(x) < abs(y))
		move = abs(y);
	else if  (abs(x) == abs(y))
		move = abs(y);


	if ( (x >= 0 && y >= 0) || (x < 0 &&  y < 0) ) 
	{
        	left = move;
        	right = turn;
	} 
	else 
	{
        	right = move;
        	left = turn;
	}

   	if(y < 0)
	{
		left = 0 - left;
        	right = 0 - right;
	}
	
	if(left > MAX_SPEED_ROBOT)
		left = MAX_SPEED_ROBOT;
	if(left < MIN_SPEED_ROBOT)
		left = MIN_SPEED_ROBOT;
	if(right > MAX_SPEED_ROBOT)
		right = MAX_SPEED_ROBOT;
	if(right < MIN_SPEED_ROBOT)
		right = MIN_SPEED_ROBOT;

	setSpeed(right,left);
}
//------------------------------------------------------------------------------
/**
*	Command ADT_iRobot_joystickControl.
*	Receives the data for the joystick and send commands 
*	to the robot.
*
*	@param number Number of button of the joystick.
*	@param value value of button of the joystick.
*/
void ADT_iRobot_joystickControl::command(int number, int value)
{
	switch(number) 
		{
			case 0: 
				if(value == 1)
					setMode(PASSIVE);
				break;
			case 1: 
				if(value == 1)
					setMode(FULL);
				break;
			case 2: 
				if(value == 1)
					starStream((ADT_iRobot_Sensors)(INT_MAX));
				break;
			case 3: 
				if(value == 1)
					setMotors((ADT_iRobot_MOTORS_COMMAND)(SIDE_BRUSH|VACUUM));
				else
					setMotors((ADT_iRobot_MOTORS_COMMAND)(0));
				break;
			case 4: 
				if(value == 1)
					pauseStream();
				break;
			case 5: 
				if(value == 1)
					setSegments("AURE");
				else
					setSegments("    ");
				break;
			case 6: 
				if(value == 1)
				{
					statusSensors(getStatus());
					displayData();
				}
				break;
			case 7: 
				if(value == 1)
					reset();
				break;
		}
}
//------------------------------------------------------------------------------
/**
*	Function display Data.
*	Displays the status of the sensors.
*/
void ADT_iRobot_joystickControl::displayData() const
{
	cout << "---------------------------------------------------------------" << endl;
	cout << "Sensors" << endl;
	cout << "TEMPERATURE: "<< sensor.temperature <<"°C"<<endl;
	cout <<"VOLTAGE: " << sensor.voltage << " V"<<endl;
	cout << "BUMPS: " << sensor.bumps <<endl;
	cout <<"CURRENT: " << sensor.current<< " A"<<endl;
	cout << "BUTTONS: " << sensor.buttons <<endl;
	cout << "WALL: " << sensor.buttons <<endl;
	cout << "BATTERYCHARGE: " << sensor.batteryCharge <<" Ah"<<endl;
	cout << "DIRT_DETECT: " << sensor.dirtDetect<<endl;
	cout << "CLIFF_LEFT: "<< sensor.cliffLeft<<endl;
	cout << "CLIFF_FRONT_LEFT: "<< sensor.cliffFrontleft<<endl;
	cout << "CLIFF_FRONT_RIGHT: "<< sensor.cliffFrontright<<endl;
	cout << "CLIFF_RIGHT: "<< sensor.cliffRight<<endl;
	cout << "INFRARED_CHARACTER_OMMI: " << sensor.infraredCharacterommi<<endl;
	cout << "INFRARED_CHARACTER_LEFT: " << sensor.infraredCharacterleft<<endl;
	cout << "INFRARED_CHARACTER_RIGHT: " << sensor.infraredCharacterright<<endl;
	cout << "VELOCITY_LEFT: " << sensor.velocityLeft<<endl;
	cout << "VELOCITY_RIGHT: " << sensor.velocityRight<<endl;
}
//------------------------------------------------------------------------------
/**
*	Status sensors.
*	Receives status sensors.
*
*	@param read ADT_iRobot_Status Read status sensors.
*/
void ADT_iRobot_joystickControl::statusSensors(ADT_iRobot_Status read)
{
	sensor.temperature = (int)read.temperature;
	sensor.voltage = ((float)(read.voltage))/1000;
	sensor.bumps = (int)read.bumps;
	sensor.current = ((float)(read.current))/1000;
	sensor.buttons = (int)read.buttons;
	sensor.wall = (int)read.wall;
	sensor.batteryCharge = ((float)(read.batteryCharge))/1000;
	sensor.dirtDetect= (int)read.dirtDetect;
	sensor.cliffLeft = read.cliffLeft;
	sensor.cliffFrontleft = read.cliffFrontleft;
	sensor.cliffFrontright = read.cliffFrontright;
	sensor.cliffRight = read.cliffRight;
	sensor.infraredCharacterommi = (int)read.infraredCharacterommi;
	sensor.infraredCharacterleft = (int)read.infraredCharacterleft;
	sensor.infraredCharacterright= (int)read.infraredCharacterright;
	sensor.infraredCharacterright = read.velocityLeft;
	sensor.infraredCharacterright = read.velocityRight;
}
