////////////////////////////////////////////////////////////////////////////////
/**
*	@file	main.cpp
*	@author	Mario Chirinos Colunga, Daniel Bojórquez
*	@date	2016-23-02
*	@note	main file template
*/
////////////////////////////////////////////////////////////////////////////////
#include "ADT_iRobot.h"
#include <iostream>

#include <cstdlib>
using namespace std;
//------------------------------------------------------------------------------
int main(int argc, char *argv[])
{	

	if(argc < 2)
	{
		cerr << "too few arguments" << endl;
		cerr << "usage "<<argv[0]<<" serial_port_name"<< endl;
		return EXIT_FAILURE;
	}
	
	ADT_iRobot robot(argv[1]);

	GMainLoop* main_loop = NULL;
	main_loop = g_main_loop_new (NULL, FALSE);
	g_main_loop_run(main_loop);
 	return 0;
}

//------------------------------------------------------------------------------
