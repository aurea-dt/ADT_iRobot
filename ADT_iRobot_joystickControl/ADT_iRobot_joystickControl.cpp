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
const char nSensorsToRead = 2;
char  sensorToReadIndex = 0;
const ADT_iRobot_SensorPackets sensorsToRead[nSensorsToRead]={ADT_iRobot_PACKETID_BATTERY_CHARGE,ADT_iRobot_PACKETID_BATTERY_CAPACITY};


using namespace std;
//------------------------------------------------------------------------------
/**
*	ADT_iRobot_joystickControl Class Constructor.
*
*	@param portName Serial port name.
*/
ADT_iRobot_joystickControl::ADT_iRobot_joystickControl(const char* portName):ADT_iRobot(portName)
{
	//reset();
	setMode(PASSIVE);
	setMode(FULL);
	g_timeout_add(2000,timeOut_callback, this);

}
//------------------------------------------------------------------------------
/**
*	ADT_iRobot_joystickControl Class Destructor.
*/
ADT_iRobot_joystickControl::~ADT_iRobot_joystickControl()
{

}
//void ADT_iRobot_joystickControl::onGetData()
//{
//	cout << "ADT_iRobot_joystickControl::onGetData()" << endl;
//}
//------------------------------------------------------------------------------
int ADT_iRobot_joystickControl::timeOut_callback (void* userdata)
{
	cout << "timeOut_callback" << endl;

//	char list[3] = {ADT_iRobot_PACKETID_IO_MODE, ADT_iRobot_PACKETID_BATTERY_CHARGE,ADT_iRobot_PACKETID_BATTERY_CAPACITY};
//	((ADT_iRobot_joystickControl*)userdata)->getQueryList(list,3);

	((ADT_iRobot_joystickControl*)userdata)->getSensor(sensorsToRead[sensorToReadIndex]);
	sensorToReadIndex++;
	if(sensorToReadIndex>=nSensorsToRead)
		sensorToReadIndex=0;


//	((ADT_iRobot_joystickControl*)userdata)->getSensor(ADT_iRobot_PACKETID_BATTERY_CHARGE);
	return true;
}
//------------------------------------------------------------------------------
/**
*	Drive ADT_iRobot_joystickControl.
*
*	@param number number of axis of the joystick.
*	@param value value of axis of the joystick.
*/
void ADT_iRobot_joystickControl::move (float xx, float yy) 
{
	int speed = sqrt(xx*xx+yy*yy)*500;
	speed = (signbit(yy)? speed*-1:speed);
	float angle = 0;

	if(yy!=0)
		angle= atan (yy/xx) * 180 / M_PI;

	angle=(signbit(xx)? abs(angle):-1*abs(angle));

	int radius = angle/90 * 2000;

	if(abs(angle)==90)
		radius = SHRT_MAX;
	if(angle==0)
		radius = (xx<0?-1:1);
	setMode(FULL);
	drive(speed, radius);
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
					reset();
				break;
			case 1: 
				if(value == 1)
					setMode(PASSIVE);
				break;
			case 2: 
				if(value == 1)
					setMode(SAFE);
				break;
			case 3: 
				if(value == 1)
					setMode(FULL);
				break;

			case 4: 
				if(value == 1)
					stop();
				break;
			case 5: 
				if(value == 1)
					setDigitLED("1234");
				break;
//			case 3: 
//				if(value == 1)
//					setMotors((ADT_iRobot_MOTORS_COMMAND)(SIDE_BRUSH|VACUUM));
//				else
//					setMotors((ADT_iRobot_MOTORS_COMMAND)(0));
//				break;
//			case 4: 
//				if(value == 1)
////					pauseStream();
//				break;
//			case 5: 
//				if(value == 1)
//					setSegments("AURE");
//				else
//					setSegments("    ");
//				break;
//			case 6: 
//				if(value == 1)
//				{
//					statusSensors(getStatus());
//					displayData();
//				}
//				break;
//			case 7: 
//				if(value == 1)
//					reset();
//				break;
		}
}
//------------------------------------------------------------------------------
/**
*	Displays the status of the sensors.
*/
void ADT_iRobot_joystickControl::displayData() const
{

}


