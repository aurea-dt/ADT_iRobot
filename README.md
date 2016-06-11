#iRobot create 2 C++ API

This code provides an API to control the iRobot create 2 platform
in form of a C++ object ADT_iRobot.
The code is based on the specifications described on 
the iRobot® Create® 2 Open Interface documentation [1] and our
serial port API [2].  It depends on glib for socket callbacks. 

[1] https://cdn-shop.adafruit.com/datasheets/create_2_Open_Interface_Spec.pdf

[2] https://github.com/aurea-dt/serialPortAPI

##Requisites to compile
To compile the code you will need glib develpment package libglib2.0-dev .

``` bash
$ sudo apt-get install libglib2.0-dev
```

##JoyStick example
An example program is provided to show how to use this API. The prgram alows to 
control the iRobot with a joystick or game pad. This program depends on our 
[ADT_joyStick API](https://github.com/aurea-dt/joystickAPI). 
