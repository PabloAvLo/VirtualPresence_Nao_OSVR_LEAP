##******************************************************************************
#                           Universidad de Costa Rica
#                  						   Proyecto Eléctrico
#                                  II Ciclo 2017
#
#                  Makefile: Leap_Service and PuppetGestures
#
# Author: Pablo Avila B30724
#
# This makefile compiles both the gesture data recorder and the Leap Service
# client.
#
# Before using any of this programs, 'sudo leapd' must be executed to
# initialize the Leap Server.
#
# Use:
#  	 make, make GESTURES or make LEAP_SERVICE		  To Compile both or each one
#		 make run 																		To run LEAP_SERVICE
#		 make record																	To run the Gesture recorder
# or make clean 																	To clean directory
#*******************************************************************************

Source = PuppetGestures.cpp ./Include/Leap.h ./Include/libLeap.so
Source2 = LeapService.cpp ./Include/Leap.h ./Include/libLeap.so

CC= g++ -std=c++0x
WFlags = -Wall -g
CFlags = -o

Target = GESTURES
Target2 = LEAP_SERVICE

all: $(Target) $(Target2)

$(Target): $(Source)
	$(CC) $(WFlags) $(CFlags) $(Target) $(Source)

$(Target2): $(Source2)
	$(CC) $(WFlags) $(CFlags) $(Target2) $(Source2)

run:
	./$(Target2)

record:
	./$(Target)

clean:
	rm -rf *.o *.out *~ *.db *.aux *.gch *.log  $(Target) $(Target2)
