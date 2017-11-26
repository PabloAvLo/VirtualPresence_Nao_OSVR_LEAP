//******************************************************************************
//                           Universidad de Costa Rica
//                  					  Proyecto Eléctrico
//                                II Ciclo 2017
//
//                                  client_main.cpp
//
// Author: Pablo Avila B30724
//
// Description:
// This is an example to create a server which continuosly listen the
// communication channel for client message's throw a socket.
//******************************************************************************

// Standard inclides
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// Project includes
#include "../Sockets.h"

Sockets server;

int main(int argc, char** argv)
{
  char* codigo;
  codigo =new char [256];

  if (argc < 2) {
    fprintf(stderr,"ERROR, no port provided\n");
    exit(1);
  }

  else{
    server.openCom(atoi(argv[1]));
    server.initServer(atoi(argv[1]));

    while(1){
      codigo = server.receiveMessage(atoi(argv[1]));
    }
  }

	return 0;
}
