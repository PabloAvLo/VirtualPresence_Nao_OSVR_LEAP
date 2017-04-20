#include <stdio.h>
#include <stdlib.h>
#include "Sockets.h"

Sockets client; 

int main(int argc, char *argv[])
{
	if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    else
    {
		client.sendMessage(argv[1], atoi(argv[2]));
	}
	return 0;
 
}
