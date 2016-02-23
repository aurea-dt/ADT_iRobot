////////////////////////////////////////////////////////////////////////////////
/**
*	@file	ADT_iRobot_joystickControl.h
*	@author	Mario Chirinos Colunga, Daniel Bojórquez Rodríguez
*	@date	2016-22-02
*	@note	header template
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef ADT_iRobot_joystickControl_H
#define ADT_iRobot_joystickControl_H

#include <string>
#include <unistd.h>
#include <math.h>
#include "../ADT_iRobot.h"
#define MAX_SPEED_ROBOT 500
#define MIN_SPEED_ROBOT -500

/**
*	List of status of sensors. 
*/
typedef struct
{
	float batteryCharge;
	float current;
	float voltage;
	int temperature;
	int wall;
	int cliffLeft;
	int cliffFrontleft;
	int cliffFrontright;
	int cliffRight;
	int bumps;
	int dirtDetect;
	int velocityRight;
	int velocityLeft;
	int buttons;
	int infraredCharacterommi;
	int infraredCharacterleft;
	int infraredCharacterright;
}Status;

using namespace std;
// the declaration of your class...
//------------------------------------------------------------------------------
class ADT_iRobot_joystickControl: private ADT_iRobot
{
	private:
		Status sensor;

		void statusSensors(ADT_iRobot_Status p);
		void displayData() const;
	public: 
		void drive (int number, int value) ;
		void command(int number, int value) ;
		ADT_iRobot_joystickControl(const char* portName);
		~ADT_iRobot_joystickControl();
};
//------------------------------------------------------------------------------
#endif
