///*****************************************************************************
///                           Universidad de Costa Rica
///                  					  Proyecto Eléctrico
///                                II Ciclo 2017
///
///                                 sockets.cpp
///
/// Author: Pablo Avila B30724
///
/// Description:
/// This file contains the description of the necessary functions to enable the
/// communication between devices thru TCP/IP sockets.
/// To get more information about sockets visit:
/// http://pubs.opengroup.org/onlinepubs/009696699/basedefs/sys/socket.h.html
///*****************************************************************************

/// Standard inclides
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <unistd.h>

/// Sockets includes
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

/// Puppeteer includes
#include "Sockets.h"

using namespace std;

/// Constructor and Destructor of class 'Sockets'
Sockets::Sockets(){}
Sockets::~Sockets(){}

//******************************************************************************
/// Displays error message when a unnexpected behavior happend.

void Sockets::error(const char *msg)
{
  perror(msg);
  exit(1);
}

///*****************************************************************************
/// Create a TCP (SOCK_STREAM) socket using an internet address of IPv4.
/// Also can be used SOCK_DATA for UDP an AF_INET FOR IPv6 for example.

void Sockets::openCom(unsigned int portno){
  this->sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if (this->sockfd < 0){
    error("ERROR opening socket");
  }
  else{
    cout<<"Communication by sockets open on port: "<< portno<<endl;
  }
}

///*****************************************************************************
/// Define the server struct to be compatible with the socket previously opened
/// and with the address of the host to be server.
/// Assign the opened address with the socket using 'bind()' and start listening
/// the socket, accepting incoming messages.

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

///*****************************************************************************
/// Reads the socket buffer for a message and write an acknowledge to the client
/// then returns an string with the message.

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

///*****************************************************************************
/// Get the server information and connect to the socket created if the
/// communication channel is already open.

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

///*****************************************************************************
/// Send message thru the socket and wait for server ack.

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

///*****************************************************************************
/// Close sockets for primary communication and replies.

void Sockets::closeCom(unsigned int portno){
  close(this->sockfd);
  close(this->newsockfd);
  cout<<"Close communication by sockets on port: "<< portno <<endl;
}
