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
#define MAX_SPEED_ROBOT 200


using namespace std;
// the declaration of your class...
//------------------------------------------------------------------------------
class ADT_iRobot_joystickControl: private ADT_iRobot
{
	private:
		void displayData() const;
		static int timeOut_callback(void* userdata);

/*		void onGetData();*/
	public: 
		int axis[6];
		void move (float x, float y) ;
		void command(int number, int value) ;
		ADT_iRobot_joystickControl(const char* portName);
		~ADT_iRobot_joystickControl();
};
//------------------------------------------------------------------------------

#endif
