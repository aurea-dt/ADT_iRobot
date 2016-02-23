////////////////////////////////////////////////////////////////////////////////
/**
 *	@file	ADT_iRobot.cpp
 *	@author	Mario Chirinos Colunga, Daniel Bojórquez Rodríguez
 *	@date	2016-22-02
 *	@note	cpp template
 */
////////////////////////////////////////////////////////////////////////////////
#include "ADT_iRobot.h"
#include<iostream>
#include<cstring>

using namespace std;
/**
*	ADT_iRobot Class Constructor.
*	@param portName Serial port name. 
*/
ADT_iRobot::ADT_iRobot(const char* portName):ADT_SerialPort(portName, 115200 , "8N1")
{
	pauseStream();
}
//------------------------------------------------------------------------------
/**
*	ADT_iRobot Class Destructor.
*	to be implement. 
*/
ADT_iRobot::~ADT_iRobot()
{

}
//------------------------------------------------------------------------------
/**
*	Serial port reception callback.
*	Callback to manipulate receive data.
*/
void ADT_iRobot::onGetData()
{	
	cout << "ADT_iRobot::onGetData()" << endl;

	static int nBytes = 0;
	static int bytesToRead=0;
	static unsigned char streamBuffer[255];
	static unsigned int streamLength;

	for(int i=0; i<bufferLength; i++)
		cout << buffer[i]<<dec;
	cout << endl;

	if(RxStatus == ADT_iRobot_STREAM)
	{	

		if(buffer[0] == ADT_iRobot_STREAM_PACKET && nBytes==0 && bufferLength >= 2)
		{
			bytesToRead=buffer[1]+3;
		}
		else
		{
			memcpy(streamBuffer + nBytes, buffer, bufferLength);
			
		}

		nBytes+=bufferLength;

		if(nBytes>=bytesToRead)
		{	
			streamLength=bytesToRead;
			nBytes=0;
			readStatus(streamBuffer,streamLength);
		}
	}
}
//------------------------------------------------------------------------------
/**
*	Send a command to ADT_iRobot.	  
*
*	@param commad String with command.
*	@param size Length of the string command.
*	@return number of bytes sent.
*/
int ADT_iRobot::sendCommand(unsigned char* command,int size) const
{ 
	 return sendData(command,size);
}
//------------------------------------------------------------------------------
/**
*	Reset ADT_iRobot.
*/
void ADT_iRobot::reset() 
{	
	RxStatus = 0;

	unsigned char command[1];
	command[0] = ADT_iRobot_RESET;
	sendCommand(command,1);
}
//------------------------------------------------------------------------------
/**
*	Beep ADT_iRobot.
*	Play beep song in the ADT_iRobot.
*/
void ADT_iRobot::beep() const
{
	unsigned char command[7] = {ADT_iRobot_SONG,3,1,64,16,141,3};
	sendCommand(command,7);
}
//------------------------------------------------------------------------------
/**
*	Stop ADT_iRobot.
*	Stops all functionalities of the ADT_iRobot.
*/
void ADT_iRobot::stop() const
{ 	
	unsigned char command[1];
	command[0] = ADT_iRobot_STOP;
	sendCommand(command,1);
}
//------------------------------------------------------------------------------
/**
*	Set the modes of ADT_iRobot.
*	Set the ADT_iRobot mode.
*	@param mode ADT_iRobot_MODE_COMMAND Mode.
*/
void ADT_iRobot::setMode(ADT_iRobot_MODE_COMMAND mode)const
{	
	unsigned char command[1];
	switch(mode)
	{
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
			break;
	}
}
//------------------------------------------------------------------------------
/**
*	Set speed move ADT_iRobot.
*	Control the motion of ADT_iRobot drive wheels independently.
* 	
*	@param speed_left Set speed left wheel.
*	@param speed_right Set speed Right wheel.
*/
void ADT_iRobot::setSpeed(int speed_right,int speed_left) const
{
	unsigned char command[5];
	unsigned char right0 = 0x00FF & speed_right;
	unsigned char right1 = 0x00FF & (speed_right >> 8);
	unsigned char left0 = 0x00FF & speed_left;
	unsigned char left1 = 0x00FF & (speed_left >> 8);

	command[0] = ADT_iRobot_DRIVEDIRECT;
	command[1] = right1;
	command[2] = right0;
	command[3] = left1;
	command[4] = left0;
	sendCommand(command,5);
}
//------------------------------------------------------------------------------
/**
*	Set the motors.
*	Control the motion of ADT_iRobot: main brush,
*	side brush, and vacuum independently.
*
*	@param motors ADT_iRobot_MOTORS_COMMAND Config options of motors.
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
*	Set the seven segments display.
*	Controls the four 7 segments displays, using ASCII character codes.
*
*	@param digit[4] Digits seven segments display.
*/
void ADT_iRobot::setSegments(const char digit[4]) const
{
	unsigned char command[5];
	command[0] = ADT_iRobot_SEGMENTS;
	command[1] = digit[0];
	command[2] = digit[1];
	command[3] = digit[2];
	command[4] = digit[3];
	sendCommand(command,5);
}
//------------------------------------------------------------------------------
/**
*	Set LEDs ADT_iRobot.
*
*	@param ledbits ADT_iRobot_LED_COMMAND Leds of the ADT_iRobot.
*	@param color Color of the led.
*	@param intensity Intensity of the led. 
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
*	Read status of sensors.
*	Checks if the checksum is correct, 
*	and writes the data status ADT_iRobot_Status.
*
*	@param streamBuffer The buffer to read into.
	@param streamLength The number of bytes to read. 
*/
ADT_iRobot_Status ADT_iRobot::readStatus(unsigned char* streamBuffer, int streamLength)
{	
	unsigned char checkSum;

	for (int i=0; i< streamLength; i++)
	{	
		checkSum += streamBuffer[i];
	}
	cout<<endl;
	if((checkSum & 0xFF) == 0)
	{	
		int byte=2;
		while(byte < (streamLength - 1))
		{	
			switch(streamBuffer[byte])
			{
				case ADT_iRobot_PACKETID_BUMPS:
					status.bumps = streamBuffer[byte+1];
					byte+=2;
					break;
				case ADT_iRobot_PACKETID_WALL:
					status.wall = streamBuffer[byte+1];
					byte+=2;
					break;
				case ADT_iRobot_PACKETID_CLIFF_LEFT:
					status.cliffLeft = ((streamBuffer[byte+1] << 8)+(streamBuffer[byte+2]));
					byte+=3;
					break;
				case ADT_iRobot_PACKETID_CLIFF_FRONT_LEFT:
					status.cliffFrontleft = ((streamBuffer[byte+1] << 8)+(streamBuffer[byte+2]));
					byte+=3;
					break;
				case ADT_iRobot_PACKETID_CLIFF_FRONT_RIGHT:
					status.cliffFrontright = ((streamBuffer[byte+1] << 8)+(streamBuffer[byte+2]));
					byte+=3;
					break;
				case ADT_iRobot_PACKETID_CLIFF_RIGHT:
					status.cliffRight = ((streamBuffer[byte+1] << 8)+(streamBuffer[byte+2]));
					byte+=3;
					break;
				case ADT_iRobot_PACKETID_DIRT_DETECT:
					status.dirtDetect = streamBuffer[byte+1];
					byte+=2;
					break;
				case ADT_iRobot_PACKETID_BUTTONS:
					status.buttons = streamBuffer[byte+1];
					byte+=2;
					break;
				case ADT_iRobot_PACKETID_VOLTAGE:
					status.voltage = ((streamBuffer[byte+1] << 8)+(streamBuffer[byte+2]));
					byte+=3;
					break;
				case ADT_iRobot_PACKETID_CURRENT:
					status.current = ((streamBuffer[byte+1] << 8)+(streamBuffer[byte+2]));
					byte+=3;
					break;
				case ADT_iRobot_PACKETID_TEMPERATURE:
					status.temperature = streamBuffer[byte+1];
					byte+=2;
					break;
				case ADT_iRobot_PACKETID_BATTERYCHARGE:
					status.batteryCharge = ((streamBuffer[byte+1] << 8)+(streamBuffer[byte+2]));
					byte+=3;
					break;
				case ADT_iRobot_PACKETID_VELOCITY_RIGHT:
					status.velocityRight = ((streamBuffer[byte+1] << 8)+(streamBuffer[byte+2]));
					byte+=3;
					break;
				case ADT_iRobot_PACKETID_VELOCITY_LEFT:
					status.velocityLeft = ((streamBuffer[byte+1] << 8)+(streamBuffer[byte+2]));
					byte+=3;
					break;
				case ADT_iRobot_PACKETID_INFRARED_CHARACTER_OMMI:
					status.infraredCharacterommi= streamBuffer[byte+1];
					byte+=2;
					break;
				case ADT_iRobot_PACKETID_INFRARED_CHARACTER_LEFT:
					status.infraredCharacterleft = streamBuffer[byte+1];
					byte+=2;
					break;
				case ADT_iRobot_PACKETID_INFRARED_CHARACTER_RIGHT:
					status.infraredCharacterright = streamBuffer[byte+1];
					byte+=2;
					break;
			}
		}
	}
}
//------------------------------------------------------------------------------
/**
*	Get status of sensors.
*
*	@return status Staus of sensors.
*/
ADT_iRobot_Status ADT_iRobot::getStatus() const
{	
	return status;
}
//------------------------------------------------------------------------------
/**
*	Pause the stream.
*/
void ADT_iRobot::pauseStream()
{
	RxStatus = 0;

	unsigned char command[2];
	command[0] = ADT_iRobot_CONTROL_STREAM;
	command[1] = 0;
	sendCommand(command,2);
}
//------------------------------------------------------------------------------
/**
*	Start a stream.
*	Start a stream of data packets.
*
* 	@param sensors ADT_iRobot_Sensors Sensors packets.	
*/
void ADT_iRobot::starStream(ADT_iRobot_Sensors sensors)
{	

	unsigned char command[ADT_iRobot_NUMBER_SENSORS+2];
	int pos=2;
	
	command[0] = ADT_iRobot_STREAM;

	if (sensors &  BUMPS)
	{
		command[pos]=ADT_iRobot_PACKETID_BUMPS;		
		pos++;
	}
	if (sensors &  WALL)
	{
		command[pos]=ADT_iRobot_PACKETID_WALL;		
		pos++;
	}
	if (sensors &  DIRT_DETECT)
	{
		command[pos]=ADT_iRobot_PACKETID_DIRT_DETECT;		
		pos++;
	}
	if (sensors & INFRARED_CHARACTER_OMMI)
	{
		command[pos]=ADT_iRobot_PACKETID_INFRARED_CHARACTER_OMMI;		
		pos++;
	}
	if (sensors &  BUTTONS)
	{
		command[pos]=ADT_iRobot_PACKETID_BUTTONS;		
		pos++;
	}
	if (sensors &  VOLTAGE)
	{
		command[pos]=ADT_iRobot_PACKETID_VOLTAGE;		
		pos++;
	}
	if (sensors &  CURRENT)
	{
		command[pos]=ADT_iRobot_PACKETID_CURRENT;		
		pos++;
	}
	if (sensors &  TEMPERATURE)
	{
		command[pos]=ADT_iRobot_PACKETID_TEMPERATURE;		
		pos++;
	}
	if (sensors &  BATTERYCHARGE)
	{
		command[pos]=ADT_iRobot_PACKETID_BATTERYCHARGE;		
		pos++;
	}
	if (sensors &  CLIFF_LEFT)
	{
		command[pos]=ADT_iRobot_PACKETID_CLIFF_LEFT;		
		pos++;
	}
	if (sensors &  CLIFF_FRONT_LEFT)
	{
		command[pos]=ADT_iRobot_PACKETID_CLIFF_FRONT_LEFT;		
		pos++;
	}
	if (sensors &  CLIFF_FRONT_RIGHT)
	{
		command[pos]=ADT_iRobot_PACKETID_CLIFF_FRONT_RIGHT;		
		pos++;
	}
	if (sensors &  CLIFF_RIGHT)
	{
		command[pos]=ADT_iRobot_PACKETID_CLIFF_RIGHT;		
		pos++;
	}
	if (sensors &  VELOCITY_RIGHT)
	{
		command[pos]=ADT_iRobot_PACKETID_VELOCITY_RIGHT;		
		pos++;
	}
	if (sensors &  VELOCITY_LEFT)
	{
		command[pos]=ADT_iRobot_PACKETID_VELOCITY_LEFT;		
		pos++;
	}
	if (sensors & INFRARED_CHARACTER_LEFT)
	{
		command[pos]=ADT_iRobot_PACKETID_INFRARED_CHARACTER_LEFT;		
		pos++;
	}
	if (sensors & INFRARED_CHARACTER_RIGHT)
	{
		command[pos]=ADT_iRobot_PACKETID_INFRARED_CHARACTER_RIGHT;		
		pos++;
	}
	if(pos != 2)
	{
		RxStatus = ADT_iRobot_STREAM;
		command[1] = pos - 2;

		cout<<"Start Stream: ";

		for(int i=0; i<pos; i++)
			cout << "<" <<(int)command[i]<<">";
		cout << endl;
		sendCommand(command,pos);
	}
	
}
