// scp setAngles nao@10.0.1.122:/home/nao

// Nao Includes
#include <alproxies/almotionproxy.h>
#include <alerror/alerror.h>
#include <qi/os.hpp>

// Sockets Library includes
#include "Sockets.h"

// Standard includes
#include <iostream>
#include <string>
using namespace std;

// Definitions
#define PI 3.14159265359
#define MOVE_HEAD_PORT 3020
#define MESSAGE_LENGTH 256

Sockets server;

int main(int argc, char *argv[])
{
  try{
    // This IP is for run the process native in the NAO. NOT through PC.
    string robotIp = "127.0.0.1";
    AL::ALMotionProxy motion(robotIp, MOVE_HEAD_PORT);

    // Receive X and Y coordantes from OSVR.
    char* osvrMessage;
    osvrMessage = new char [MESSAGE_LENGTH];
    int commaIndex;
    char osvrX[7];
    char osvrY[7];

    while(1){
      osvrMessage = server.receiveMessage(MOVE_HEAD_PORT);
      commaIndex =0;

      for(int i=0; i<MESSAGE_LENGTH; i++){
        if(commaIndex==0){
          if(osvrMessage[i] == ','){
            commaIndex = i;
          }
          else{
            osvrX[i]= osvrMessage[i];
          }
        }
        else {
          if( ( (osvrMessage[i] >= 48) && (osvrMessage[i] <=57)) || osvrMessage[i] =='-'){
            osvrY[i]= osvrMessage[i];
          }
        }
      }

      float yaw   = atoi(osvrX) * PI;
      float pitch = atoi(osvrY) * PI;

      // Example showing how to set angles, using a fraction of max speed
      AL::ALValue names       = AL::ALValue::array("HeadYaw", "HeadPitch");
      AL::ALValue angles      = AL::ALValue::array(yaw, pitch);
      float fractionMaxSpeed  = 0.1f;
      motion.setStiffnesses(names, AL::ALValue::array(1.0f, 1.0f));
      // qi::os::sleep(1.0f);
      motion.setAngles(names, angles, fractionMaxSpeed);
      // qi::os::sleep(1.0f);
      // motion.setStiffnesses(names, AL::ALValue::array(0.0f, 0.0f));
    }
  }
  catch (const AL::ALError& e)
  {
    cerr << "Caught exception: " << e.what() << endl;
    return -1;
  }
  return 0;
}
