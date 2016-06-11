#-------------------------------------------------------------------------------
#	AUTOR
#	Aurea Desarrollo Tecnológico.
#	FECHA
#	Notas:
#-------------------------------------------------------------------------------
APPNAME = joystickControlTest
#Compiler:
	CC=g++

#Compiler flags
	CFLAGS=-c -g -Wall
	INCLUIDES=$(shell pkg-config --cflags glib-2.0)
	LIBS=$(shell pkg-config --libs glib-2.0)
#Directories
	DIRlib= /usr/local/lib	
	incDIR= /usr/local/include
#main function
	mainP= main
#-------------------------------------------------------------------------------
all: Project

Project: mainP.o ADT_joystick.o ADT_iRobot.o ADT_SerialPort.o ADT_iRobot_joystickControl.o
	$(CC) -export-dynamic -o $(APPNAME) \
	$(mainP).o \
	ADT_joystick.o \
	ADT_iRobot.o  \
	ADT_SerialPort.o \
	ADT_iRobot_joystickControl.o \
	$(LIBS)
	
mainP.o: $(mainP).cpp
	$(CC) $(INCLUIDES) $(CFLAGS) \
	$(mainP).cpp
	
ADT_joystick.o: ADT_joystick.cpp
	$(CC) $(INCLUIDES) $(CFLAGS) \
	ADT_joystick.cpp 
ADT_SerialPort.o: ../ADT_SerialPort.cpp
	$(CC) $(INCLUIDES) $(CFLAGS) \
	../ADT_SerialPort.cpp
ADT_iRobot.o: ../ADT_iRobot.cpp
	$(CC) $(INCLUIDES) $(CFLAGS) \
	../ADT_iRobot.cpp
ADT_iRobot_joystickControl.o: ADT_iRobot_joystickControl.cpp
	$(CC) -I.. $(INCLUIDES) $(CFLAGS) \
	ADT_iRobot_joystickControl.cpp
	
