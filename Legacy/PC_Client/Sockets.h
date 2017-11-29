
#ifndef SOCKETS_H
#define SOCKETS_H
class Sockets{
private: unsigned int portno;

public:
Sockets();
~Sockets();

void error(const char *msg);

char* receiveMessage(unsigned int portno);
void sendMessage(const char* host, unsigned int portno, char* mensaje);
};
#endif
