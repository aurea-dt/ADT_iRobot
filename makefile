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
all: Project

Project: mainP.o ADT_iRobot.o ADT_SerialPortRx.o	
	$(CC) -o $(APPNAME) \
	ADT_iRobot.o \
	ADT_SerialPortRx.o \
	$(mainP).o \
	-L $(DIRlib) \
	-I $(incDIR) \
	$(LIBS) 
	

ADT_SerialPortRx.o: ADT_SerialPortRx.cpp
	$(CC) $(INCLUIDES) $(CFLAGS) \
	ADT_SerialPortRx.cpp

ADT_iRobot.o: ADT_iRobot.cpp
	$(CC) $(INCLUIDES) $(CFLAGS) \
	ADT_iRobot.cpp

mainP.o: $(mainP).cpp
	$(CC) $(INCLUIDES) $(CFLAGS) \
	$(mainP).cpp

