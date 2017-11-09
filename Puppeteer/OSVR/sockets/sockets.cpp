/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "Sockets.h"
#include <iostream>

using namespace std;

Sockets::Sockets(){}
Sockets::~Sockets(){}

void Sockets::error(const char *msg)
{
  perror(msg);
  exit(1);
}

void Sockets::openCom(unsigned int portno){
  this->sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if (this->sockfd < 0){
    error("ERROR opening socket");
  }
  else{
    cout<<"Communication by sockets open on port: "<< portno<<endl;
  }
}

void Sockets::initServer(unsigned int portno){
  struct sockaddr_in serv_addr, cli_addr;
  socklen_t clilen;
  int a =1;
  int* valor = & a;

  bzero((char *) &serv_addr, sizeof(serv_addr));
  //portno = atoi(argv[1]);
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);

  setsockopt(this->sockfd,SOL_SOCKET, SO_REUSEADDR, valor, sizeof(int));

  if(bind(this->sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
    error("ERROR on binding");
  }

  listen(this->sockfd,5);
  clilen = sizeof(cli_addr);
  this->newsockfd = accept(this->sockfd, (struct sockaddr *) &cli_addr, &clilen);

  if (this->newsockfd < 0){
    error("ERROR on accept");
  }
}

//******************************************************************************
char* Sockets::receiveMessage(unsigned int portno){
  char* buffer;
  buffer = new char[256];
  int n;

  bzero(buffer,256);
  n = read(this->newsockfd,buffer,255);

  if (n < 0){
    error("ERROR reading from socket");
  }

  cout<< "Here is the message: " << buffer << endl;
  n = write(this->newsockfd,"I got your message",18);

  if (n < 0){
    error("ERROR writing to socket");
  }
  return buffer;
}

//******************************************************************************

void Sockets::initClient(const char* host, unsigned int portno){
  struct sockaddr_in serv_addr;
  struct hostent *server;

  server = gethostbyname(host);
  if (server == NULL) {
    cout << stderr <<"ERROR, no such host"<< endl;
    exit(0);
  }

  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
  serv_addr.sin_port = htons(portno);

  if (connect(this->sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0){
    error("ERROR connecting");
  }
}

//******************************************************************************

void Sockets::sendMessage(char* buffer){
  int n;
  char receive[256];

  n = write(this->sockfd,buffer,strlen(buffer));
  if (n < 0){
    error("ERROR writing to socket");
  }

  bzero(receive,256);
  n = read(this->sockfd,receive,255);
  if (n < 0){
    error("ERROR reading from socket");
  }
  cout<< "Server answer: "<< receive <<endl;
}

//******************************************************************************

void Sockets::closeCom(unsigned int portno){
  close(this->sockfd);
  close(this->newsockfd);
  cout<<"Close communication by sockets on port: "<< portno <<endl;
}
