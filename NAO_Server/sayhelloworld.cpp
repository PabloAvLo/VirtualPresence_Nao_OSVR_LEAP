// scp sayhelloworld nao@10.0.1.122:/home/nao

#include <iostream>
#include <alerror/alerror.h>
#include <alproxies/altexttospeechproxy.h>
#include "Sockets.h"
#include <string>
using namespace std;

#define CAMINAR 0
#define SENTARSE 1
#define HABLAR 2

Sockets server;

int main(int argc, char* argv[])
{
  bool loop=true;
  if(argc != 3)
  {
    cerr << "Wrong number of arguments!" << endl;
    cerr << "Usage: say NAO_IP" << endl;
    exit(2);
  }

  try{
    AL::ALTextToSpeechProxy tts(argv[1], 9559);
    /** Call the say method */

    while(loop){
      int codigo = atoi(server.receiveMessage(atoi(argv[2])));
      cout<< codigo <<endl;
      switch(codigo){
        case CAMINAR:
          tts.say("WALKING"); cout<< "CAMINAR = 0"<<endl; break;
        case SENTARSE:
          tts.say("SIT DOWN");  cout<< "SENTARSE =1"<<endl; break;
        case HABLAR:
          tts.say("SPEAK"); cout<< "HABLAR =2"<<endl; break;
        default:
          tts.say("Failed"); cout<< "INVALID CASE" <<endl; loop =false; break;
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
