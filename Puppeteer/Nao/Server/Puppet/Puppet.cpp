//******************************************************************************
//                           Universidad de Costa Rica
//                  					  Proyecto Eléctrico
//                                II Ciclo 2017
//
//                                 Puppet.cpp
//
// Author: Pablo Avila B30724
//******************************************************************************

//Project Includes
#include "TaskLib.h"
#include "../../../CommLib/Sockets.h"

//Standar Includes
#include <iostream>
#include <string>
using namespace std;

Sockets server;
TaskLib puppet;

int main(int argc, char* argv[])
{
  char* message;
  message = new char [256];
  int code = 0;

  server.openCom(puppet.port);
  server.initServer(puppet.port);

  //************************** NAO OBJECTS *************************************
  AL::ALTextToSpeechProxy tts(puppet.naoIP, 9559);

  //******************** PHRASES TO SAY ****************************************
  string hello = "Hello, my name is SHE";


  bool loop=true;
  try{
    while(loop){
      message = server.receiveMessage(puppet.port);
      code = atoi(message);

      switch(code){
        case TASK1:
          puppet.speak(tts, hello); cout<< "TASK1"<<endl; break;

        case TASK2:
          puppet.speak(tts, "SIT DOWN");  cout<< "TASK2"<<endl; break;

        case TASK3:
          puppet.speak(tts, "SPEAK"); cout<< "TASK3"<<endl; break;

        default:
          puppet.speak(tts, "Failed"); cout<< "INVALID CASE" <<endl; loop =false; break;
          server.closeCom(puppet.port);
      }
    }
  }
  catch (const AL::ALError& e)
  {
    cerr << "Caught exception: " << e.what() << endl;
    exit(1);
  }
  exit(0);
}
