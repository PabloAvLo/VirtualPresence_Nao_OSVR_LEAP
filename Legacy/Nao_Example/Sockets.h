
#ifndef SOCKETS_H
#define SOCKETS_H
class Sockets{
private: unsigned int portno;

public:
Sockets();
~Sockets();

void error(const char *msg);

int receiveMessage(unsigned int portno);
int sendMessage(char* host, unsigned int portno);
};
#endif
