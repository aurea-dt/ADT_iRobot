#-------------------------------------------------------------------------------
#
#
#	Notes:
#-------------------------------------------------------------------------------
APPNAME = ADT_iRobotTest
#Compiler:
	CC=g++

#Compiler flags
	CFLAGS=-c -g -Wall

#Directories
	DIRlib= /usr/local/lib	
	incDIR= /usr/local/include
	INCLUIDES=$(shell pkg-config --cflags glib-2.0)
	LIBS=$(shell pkg-config --libs glib-2.0)

#main function
	mainP= main
#-------------------------------------------------------------------------------
all: Project Project2

Project: mainP.o ADT_iRobot.o ADT_SerialPort.o	
	$(CC) -o $(APPNAME) \
	ADT_iRobot.o \
	ADT_SerialPort.o \
	$(mainP).o \
	-L $(DIRlib) \
	-I $(incDIR) \
	$(LIBS) 
	

ADT_SerialPort.o: ADT_SerialPort.cpp
	$(CC) $(INCLUIDES) $(CFLAGS) \
	ADT_SerialPort.cpp

ADT_iRobot.o: ADT_iRobot.cpp
	$(CC) $(INCLUIDES) $(CFLAGS) \
	ADT_iRobot.cpp

mainP.o: $(mainP).cpp
	$(CC) $(INCLUIDES) $(CFLAGS) \
	$(mainP).cpp

Project2: 
	cd ADT_iRobot_joystickControl;make
