#include <stdio.h>
#include <stdlib.h>
#include "Sockets.h"
#include <iostream>

Sockets server;

int main(int argc, char** argv)
{
  char c;
    if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
    }else{

    while(c !='z'){
		  server.receiveMessage(atoi(argv[1]));
      std::cout<<"Enter z to quit"<<std::endl;
      std::cin.get(c);
    }
	}
	return 0;

}
