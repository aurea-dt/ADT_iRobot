//////////////////////////////////////////////////////////////////////////////
//	main.cpp
//	Mario Chirinos Colunga
//	Aurea Desarrollo Tecnológico.
//	16 de Diciembre del 2010
//----------------------------------------------------------------------------
//	DESCRIPCIÓN
//	Notas:	
//		
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "ADT_joystick.h"
#include "ADT_iRobot_joystickControl.h"
#include <math.h>

ADT_iRobot_joystickControl* control;

using namespace std;
//------------------------------------------------------------------------------
void axis_callback(unsigned int number, int value, void *userdata)
{
	cout << ((ADT_joystick*)userdata)->getDevName() << " axis event #"<< number << " : " << value << endl;
	control->drive(number,value);
}
//------------------------------------------------------------------------------
void button_callback(unsigned int number, int value, void *userdata)
{
	cout << ((ADT_joystick*)userdata)->getDevName() << " button event #"<< number << " : " << value << endl;
	control->command(number,value);
}
//------------------------------------------------------------------------------
int main (int argc, char *argv[])
{	
	control = new ADT_iRobot_joystickControl(argv[1]);
	ADT_joystick joystick;
	joystick.enumJoysticks();
	joystick.connect("/dev/input/js1");
	joystick.setAxisCallback(&axis_callback);
	joystick.setButtonCallback(&button_callback);

	GMainLoop* main_loop = NULL;
	main_loop = g_main_loop_new (NULL, FALSE);
	g_main_loop_run(main_loop);

 return 0;
}

//gcc -Wall -g -o tutorial main.c -export-dynamic `pkg-config --cflags --libs gtk+-2.0`
