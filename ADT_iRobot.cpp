////////////////////////////////////////////////////////////////////////////////
/**
 *	@file	ADT_iRobot.cpp
 *	@author	Mario Chirinos Colunga, Daniel Bojórquez Rodríguez
 *	@date	2016/02/22
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
#include "ADT_iRobot.h"
#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;
/**
*	ADT_iRobot constructor.
*	@param portName Serial port name. 
*/
ADT_iRobot::ADT_iRobot(const char* portName):ADT_SerialPort(portName, 115200, "8N1")
{
	rxStatus = -1;
}
//------------------------------------------------------------------------------
/**
*	ADT_iRobot destructor.
*/
ADT_iRobot::~ADT_iRobot()
{
	cout << "~ADT_iRobot()" << endl;
	stop();
}
//------------------------------------------------------------------------------
/**
*	Serial port reception callback.
*/
void ADT_iRobot::onGetData()
{	
	cout << "ADT_iRobot::onGetData()" << endl;

	cout << "Message("<<bufferLength<<"): ";
	for(unsigned int i=0; i<bufferLength; i++)
		cout  << buffer[i] ;
	cout << endl;

	cout << "Message("<<bufferLength<<"): ";
	for(unsigned int i=0; i<bufferLength; i++)
		cout << "<" << hex << (int)buffer[i]<< dec << ">" ;
	cout << endl;

	if(rxStatus != -1)
	{
		cout << "rxStatus != -1" << endl;
		if(bufferLength<=4)
		{
			int sensor = 0;
			memcpy(&sensor, buffer, bufferLength);
			sensors[rxStatus] = sensor;
			cout << "Sensor ("<< rxStatus << "): " << sensors[rxStatus] << endl;
		}
		rxStatus = -1;
	}
}
//------------------------------------------------------------------------------
/**
*	Send command to iRobot.	  
*
*	@param commad command string.
*	@param size command string length.
*	@return number of bytes sent.
*/
int ADT_iRobot::sendCommand(unsigned char* command, int size) const
{ 
	for(int i=0; i<size; i++)
		cout << "<" <<(int)command[i]<<">";
	cout << endl;
	return sendData(command,size);
}
//------------------------------------------------------------------------------
/**
*	Reset iRobot.
*/
void ADT_iRobot::reset() 
{	
	rxStatus = -1;

	unsigned char command[1];
	command[0] = ADT_iRobot_RESET;
	sendCommand(command,1);
}
//------------------------------------------------------------------------------
/**
*	Play Beep on iRobot.
*/
void ADT_iRobot::beep() const
{
	unsigned char command[15] = {ADT_iRobot_SONG,0,6,88,20,91,20,88,20,96,20,86,20,91,20};

	sendCommand(command,15);
	unsigned char command2[2] = {ADT_iRobot_PLAY,0};
	sendCommand(command2,2);
}
//------------------------------------------------------------------------------
/**
*	Stop ADT_iRobot.
*/
void ADT_iRobot::stop() const
{ 	
	unsigned char command[1];
	command[0] = ADT_iRobot_STOP;
	sendCommand(command,1);
}
//------------------------------------------------------------------------------
/**
*	Set iRobot operation mode.
*	@param mode ADT_iRobot_MODE_COMMAND.
*/
void ADT_iRobot::setMode(ADT_iRobot_MODE_COMMAND mode)const
{	
	unsigned char command[1];
	switch(mode)
	{
		case STOP:	
			command[0] = ADT_iRobot_STOP;
			sendCommand(command,1);
			break;
		case PASSIVE:	
			command[0] = ADT_iRobot_PASSIVE;
			sendCommand(command,1);
			break;
		case SAFE:	
			command[0] = ADT_iRobot_SAFE;
			sendCommand(command,1);
			break;
		case FULL:	
			command[0] = ADT_iRobot_FULL;
			sendCommand(command,1);
			break;
		 default:
			command[0] = ADT_iRobot_STOP;
			sendCommand(command,1);
			break;
	}
}
//------------------------------------------------------------------------------
/**
*	iRobot drive with radius and velocity.
* 	
*	@param velocity Velocity in mm/s.
*	@param radius Turn radius in mm.
*/	
void ADT_iRobot::drive(int velocity, int radius)
{
	short v = ((short)velocity);
	short r = ((short)radius);
	unsigned char command[5]={ADT_iRobot_DRIVE, 0x00FF & (v >> 8), 0x00FF & v, 0x00FF & (r >> 8), 0x00FF & r};
	sendCommand(command,5);
}
//------------------------------------------------------------------------------
/**
*	Turn on/off vacum and brush motors.
*	Turn on or off main brush, side brush or vacuum independently.
*	@param motors ADT_iRobot_MOTORS_COMMAND as OR flags of motors to enble.
*/
void ADT_iRobot::setMotors(ADT_iRobot_MOTORS_COMMAND motors) const
{
	unsigned char command[2];
	command[0] = ADT_iRobot_MOTORS;
	command[1] = motors;
	sendCommand(command,2);
}
//------------------------------------------------------------------------------
/**
*	Set seven segments display.
*	Controls the four 7 segments digits, using ASCII codes.
*
*	@param digit[4] Four digits to display.
*/
void ADT_iRobot::setDigitLED(const char digit[4]) const
{
	unsigned char command[5];
	command[0] = ADT_iRobot_LED_ASCII;
	command[1] = digit[0];
	command[2] = digit[1];
	command[3] = digit[2];
	command[4] = digit[3];
	sendCommand(command,5);
}
//------------------------------------------------------------------------------
/**
*	Control iRobot LEDs.
*
*	@param ledbits ADT_iRobot_LED_COMMAND Leds of the ADT_iRobot.
*	@param color LEDs color.
*	@param intensity LEDs intensity. 
*/
void ADT_iRobot::setLEDs(ADT_iRobot_LED_COMMAND ledbits, unsigned char color,unsigned char intensity) const
{
	unsigned char command[4];	
	command[0] = ADT_iRobot_LEDS;
	command[1] = ledbits;
	command[2] = color;
	command[3] = intensity;
	sendCommand(command,4);
}
//------------------------------------------------------------------------------
/**
*	Pause the data stream.
*/
void ADT_iRobot::pauseStream()
{
	rxStatus = -1;

	unsigned char command[2];
	command[0] = ADT_iRobot_CONTROL_STREAM;
	command[1] = 0;
	sendCommand(command,2);
}
//------------------------------------------------------------------------------
/**
*	Start data stream.
*
* 	@param sensors ADT_iRobot_Sensors Sensors to read.	
*/
void ADT_iRobot::startStream(const char* sensorsList, unsigned char nSensors)
{	
	unsigned char data[nSensors+2];
	data[0] = ADT_iRobot_STREAM;
	data[1] = nSensors;
	memcpy(data+2, sensorsList, nSensors);


	sendCommand(data,nSensors+2);
}
//------------------------------------------------------------------------------
/**
*	Ask for a list of sensor packets.
*
* 	@param sensorsList List sensors to read.
* 	@param nSensors Total number of sensors to read		
*/
void ADT_iRobot::getQueryList(const char* sensorsList, unsigned char nSensors)
{
	unsigned char data[nSensors+2];
	data[0] = ADT_iRobot_QUERY_LIST;
	data[1] = nSensors;
	memcpy(data+2, sensorsList, nSensors);

	sendCommand(data,nSensors+2);
}
//------------------------------------------------------------------------------
/**
*	Ask for a single sensor value.
*
* 	@param sensor Sensor to read.
*/
//------------------------------------------------------------------------------
void ADT_iRobot::getSensor(ADT_iRobot_SensorPackets sensor)
{
	unsigned char data[2];
	data[0] = ADT_iRobot_SENSORS;
	data[1] = sensor;
	rxStatus = sensor;
	sendCommand(data,2);
}
//------------------------------------------------------------------------------

