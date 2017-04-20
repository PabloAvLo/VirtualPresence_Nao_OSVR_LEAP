#include <stdio.h>
#include <stdlib.h>
#include "Sockets.h"

Sockets server; 

int main(int argc, char** argv)
{
    if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
    }else{
		server.receiveMessage(atoi(argv[1]));
	}
	return 0;

} 
