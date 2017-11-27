##******************************************************************************
#                           Universidad de Costa Rica
#                  						   Proyecto Eléctrico
#                                  II Ciclo 2017
#
#                           Makefile: Example Sockets
#
# Author: Pablo Avila B30724
# This makefile compiles and runs the server and client hosts for a socket
# communication in port number: 3000.
#*******************************************************************************

OBJ1=  server_main.cpp ../Sockets.cpp ../Sockets.h
OBJ2=  client_main.cpp ../Sockets.cpp ../Sockets.h

CC=g++

TARGET_1 = Server
TARGET_2 = Client

all: $(TARGET_1) $(TARGET_2)

$(TARGET_1): $(OBJ1)
	$(CC) -o $(TARGET_1) $(OBJ1)

$(TARGET_2): $(OBJ2)
	$(CC) -o $(TARGET_2) $(OBJ2)

run:
	gnome-terminal --tab -e "./$(TARGET_1) 3000" --tab -e "./$(TARGET_2) 127.0.0.1 3000"

clean:
	rm -f -R *.o *.out *~ *.db *.aux *.gch *.log $(TARGET_1) $(TARGET_2)
