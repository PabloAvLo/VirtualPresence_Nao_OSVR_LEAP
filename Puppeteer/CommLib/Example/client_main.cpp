///*****************************************************************************
///                           Universidad de Costa Rica
///                  					  Proyecto Eléctrico
///                                II Ciclo 2017
///
///                                  client_main.cpp
///
/// Author: Pablo Avila B30724
///
/// Description:
/// This is an example to create a client which continuosly ask the user for
/// messages and send them to an enabled server throw a socket.
/// 'z' characther ends the communication by closing the socket.
///*****************************************************************************

/// Standard inclides
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>

/// Puppeteer includes
#include "../Sockets.h"

Sockets client;

int main(int argc, char *argv[]){

	char mensaje[256];

	if(argc < 3) {
     std::cout<< stderr <<"Wrong number of arguments!\nPlease enter IP address and Port\n" << argv[0]<<std::endl;
     exit(0);
  }

	else{
		client.openCom(atoi(argv[2]));
		client.initClient(argv[1], atoi(argv[2]));
		while(mensaje[0] !='z'){
			fgets(mensaje,255,stdin);
			client.sendMessage(mensaje);
			std::cout<<"Press 'z' to quit"<<std::endl;
		}
		client.closeCom(atoi(argv[2]));
	}
	return 0;
}
