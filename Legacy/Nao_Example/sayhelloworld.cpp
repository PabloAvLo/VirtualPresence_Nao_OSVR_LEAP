#include <iostream>
#include <alerror/alerror.h>
#include <alproxies/altexttospeechproxy.h>
#include "Sockets.h"

Sockets server; 

int main(int argc, char* argv[])
{
  if(argc != 3)
  {
    std::cerr << "Wrong number of arguments!" << std::endl;
    std::cerr << "Usage: say NAO_IP" << std::endl;
    exit(2);
  }

  /** The desired phrase to be said. */
  const std::string phraseToSay = "Hello world";
  try
  {
    /** Create an ALTextToSpeechProxy so that we can call the say method
    * Arguments for the constructor are:
    *  - IP of the robot
    *  - port on which NAOqi is listening. Default is 9559
    */
    AL::ALTextToSpeechProxy tts(argv[1], 9559);
    /** Call the say method */
    tts.say(phraseToSay);
    server.receiveMessage(atoi(argv[2]));

  }
  catch (const AL::ALError& e)
  {
    std::cerr << "Caught exception: " << e.what() << std::endl;
    exit(1);
  }
  exit(0);
}
