////////////////////////////////////////////////////////////////////////////////
/**
*	@file	main.cpp
*	@author	Mario Chirinos Colunga, Daniel Bojórquez
*	@date	2016-23-02
*	@note	main file template
*/
////////////////////////////////////////////////////////////////////////////////
#include "ADT_iRobot.h"
#include<iostream>

#include <cstdlib>
using namespace std;
//------------------------------------------------------------------------------
int main(int argc, char *argv[])
{	
	int e=1;
	char enviar;



	if(argc < 2)
	{
		cerr << "too few arguments" << endl;
		cerr << "usage "<<argv[0]<<" serial_port_name"<< endl;
		return EXIT_FAILURE;
	}
	
	ADT_iRobot robot(argv[1]);

	while(e)
	{
		cout<< "Push c for exit, or w-x-s-a-d for move"<<endl;
		cin>> enviar; 
		switch(enviar) 
		{
		case 'p': 
			robot.setMode(PASSIVE);
			break;
		case 'f': 
			robot.setMode(FULL);
			break;
		case 'r': 
			robot.reset();
			break;
		case 'w': 
			robot.setSpeed(100,100);
			break;
		case 'x': 
			robot.setSpeed(-100,-100);
			break;
		case 'a': 
			robot.setSpeed(-100,100);
			break;
		case 'd': 
			robot.setSpeed(100,-100);
			break;
		case 's': 	
			robot.setSpeed(0,0);
			break;
		case 'b': 
			robot.beep();
			break;
		case 'c': 
			e=0;
			break;
		default:
			break;
		}
	}
	GMainLoop* main_loop = NULL;
	main_loop = g_main_loop_new (NULL, FALSE);
	g_main_loop_run(main_loop);
 	return 0;
}

//------------------------------------------------------------------------------
