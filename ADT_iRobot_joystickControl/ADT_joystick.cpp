////////////////////////////////////////////////////////////////////////////////
// 	ADT_joystick.h
// 	Mario Chirinos Colunga
// 	Aurea Desarrollo Tecnológico.
//	16 de Diciembre del 2010
//------------------------------------------------------------------------------
// Notes:
//	c++ Joystick API
//
////////////////////////////////////////////////////////////////////////////////
#include "ADT_joystick.h"
#include <glib.h>
#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
using namespace std;
//------------------------------------------------------------------------------
JsData::JsData()
{
	nAxis = 0;
	nButtons = 0;
}
//------------------------------------------------------------------------------
ADT_joystick::ADT_joystick()
{
	nAxis = 0;
	nButtons = 0;
	version = 0;
	vAxis = NULL;
	vButton = NULL;
	axisCallback=NULL;
	buttonCallback=NULL;
}
//------------------------------------------------------------------------------
ADT_joystick::~ADT_joystick()
{
	close(fd);
	delete []vAxis;
	delete []vButton;
}
//------------------------------------------------------------------------------
int ADT_joystick::enumJoysticks()
{
	DIR* Dir = opendir("/dev/input");
	dirent* DirEntry;
	while((DirEntry=readdir(Dir)))
	{
		int fdTemp;
		string fname=string(DirEntry->d_name);
		if(fname.length()>=2)
			if(fname.substr(0,2)=="js")
			{				
				string filename = "/dev/input/"+fname;
				if ((fdTemp = open(filename.c_str(), O_RDONLY)) < 0)
				{
					cerr << "could not open Joystick: " << filename << endl;
				}
				else
				{
					JsData jsdTemp;
					ioctl(fdTemp, JSIOCGNAME(80), &jsdTemp.name);
					ioctl(fdTemp, JSIOCGAXES, &jsdTemp.nAxis);
					ioctl(fdTemp, JSIOCGBUTTONS, &jsdTemp.nButtons);
					jsList.push_back(jsdTemp);
				}
				close(fdTemp);
			}
	}
	closedir(Dir);
	return jsList.size();
}
//------------------------------------------------------------------------------
vector<JsData> ADT_joystick::getList() const
{
	return jsList;
}
//------------------------------------------------------------------------------
const char* ADT_joystick::getDevName() const
{
	return devName;
}
//------------------------------------------------------------------------------
const char* ADT_joystick::getName() const
{
	return name;
}
//------------------------------------------------------------------------------
unsigned int ADT_joystick::getAxisCount()const
{
	return nAxis;
}
//------------------------------------------------------------------------------
unsigned int ADT_joystick::getButtonCount() const
{
	return nButtons;
}
//------------------------------------------------------------------------------
int ADT_joystick::getAxis(unsigned int i) const
{
	if(i >= nAxis)
		return NULL;
	return vAxis[i];
}
//------------------------------------------------------------------------------
bool ADT_joystick::getButton(unsigned int i) const
{
	if(i >= nButtons)
		return NULL;
	return vButton[i];
}
//------------------------------------------------------------------------------
int ADT_joystick::connect(const char *filename)
{
	if ((fd = open(filename, O_RDONLY)) < 0)
	{
		cerr << "could not open Joystick: " << filename << endl;
		return 1;
	}
	else
	{
		devName = (char*)filename;
		ioctl(fd, JSIOCGNAME(80), &name);
		ioctl(fd, JSIOCGAXES, &nAxis);
		ioctl(fd, JSIOCGBUTTONS, &nButtons);
		ioctl(fd, JSIOCGVERSION, &version);
		
		cout << "nAxis: " << nAxis << endl;
		vAxis = new int[nAxis];
		vButton = new bool[nButtons];
		for(int i=0; i<nAxis; i++)
		{
			vAxis[i]=0;
		}
		channel = g_io_channel_unix_new (fd);
		g_io_add_watch(channel, G_IO_IN, &jscallback, this);
		cout << "Conected to: " << name << endl;
		cout << "\tAxis: " << (int)nAxis << ", Buttons: " << (int)nButtons << endl;
		cout << "\tDriver version " << (int)version << endl;
	}
	return 0;
}
//------------------------------------------------------------------------------
int ADT_joystick::jscallback(GIOChannel *source, GIOCondition condition, void *data)
{
		/* read the joystick state */
	return ((ADT_joystick*)data)->readJs();
}
//------------------------------------------------------------------------------
int ADT_joystick::readJs()
{
	struct js_event js;
	read(fd, &js, sizeof(struct js_event));
	int number = (int)js.number;
	int value = (int)js.value;
	int event = js.type & ~JS_EVENT_INIT;
	switch (event)
	{
		case JS_EVENT_AXIS:
			vAxis[number] = value;
			if(axisCallback!=NULL)
				axisCallback(number, value, this);
			break;
		case JS_EVENT_BUTTON:
			vButton[number] = value;
			if(buttonCallback!=NULL)
				buttonCallback(number, value, this);
			break;
		default:
			break;
	}
return event;
}
//------------------------------------------------------------------------------
void ADT_joystick::setAxisCallback(jsPt2Function _fpt)
{
	axisCallback = _fpt;
}
//------------------------------------------------------------------------------
void ADT_joystick::unsetAxisCallback()
{
	axisCallback = NULL;
}
//------------------------------------------------------------------------------
void ADT_joystick::setButtonCallback(jsPt2Function _fpt)
{
	buttonCallback = _fpt;
}
//------------------------------------------------------------------------------
void ADT_joystick::unsetButtonCallback()
{
	buttonCallback = NULL;
}
//------------------------------------------------------------------------------
