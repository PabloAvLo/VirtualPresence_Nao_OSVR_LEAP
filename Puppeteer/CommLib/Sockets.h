///*****************************************************************************
///                           Universidad de Costa Rica
///                  					  Proyecto Eléctrico
///                                II Ciclo 2017
///
///                                  Sockets.h
///
/// Author: Pablo Avila B30724
///
/// Description:
/// Defines the functions and attributes of the class 'Sockets'.
///*****************************************************************************

#ifndef SOCKETS_H
#define SOCKETS_H

class Sockets{

private: unsigned int portno;

public:
/// Type of Socket to create (TCP communication)
  int sockfd;
  int newsockfd;

/// Constructor
  Sockets();

/// Destructor
  ~Sockets();

/// Error handler
  void error(const char *msg);

/// Function to open socket
  void openCom(unsigned int portno);

/// Function to init server
  void initServer(unsigned int portno);

/// Function for server to receive messages
  char* receiveMessage(unsigned int portno);

/// Function to init client
  void initClient(const char* host, unsigned int portno);

/// Function for clients to send messages
  void sendMessage(char* mensaje);

/// Function to close socket
  void closeCom(unsigned int portno);
};
#endif
