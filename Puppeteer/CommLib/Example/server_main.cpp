#include <stdio.h>
#include <stdlib.h>
#include "../Sockets.h"
#include <iostream>

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
