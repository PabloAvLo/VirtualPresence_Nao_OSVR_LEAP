///*****************************************************************************
///                           Universidad de Costa Rica
///                  					  Proyecto Eléctrico
///                                II Ciclo 2017
///
///                                 Movehead.cpp
///
/// Author: Pablo Avila B30724
///
/// Description:
/// This is the NAO-OSVR communication server process, that recieves the OSVR
/// orientation values in x and y axis to make the NAO move it's head the most
/// similar to the operator, in real time.
///*****************************************************************************

/// NAO includes
#include <alproxies/almotionproxy.h>
#include <alerror/alerror.h>
#include <qi/os.hpp>

/// Puppeteer includes
#include "../../../CommLib/Sockets.h"

/// Standard includes
#include <iostream>
#include <string>
using namespace std;

/// Definitions
#define MOVE_HEAD_PORT 3010
#define MESSAGE_LENGTH 256

Sockets server;

///*****************************************************************************
int main(int argc, char *argv[])
{
  string naoIP = "127.0.0.1";

  try{
    /// This IP is for run the process native in the NAO. NOT through PC.
    AL::ALMotionProxy motion(naoIP, 9559);

    /// Init communication Server by socket TCP
    server.openCom(MOVE_HEAD_PORT);
    server.initServer(MOVE_HEAD_PORT);

    /// Receive X and Y coordantes from OSVR.
    char* osvrMessage;
    int commaIndex;
    char osvrX[7];
    char osvrY[7];
    double x=0.0f;
    double y=0.0f;
    double pi = 3.14159265359;
    double yaw;
    double pitch;

    while(1){
      osvrMessage = server.receiveMessage(MOVE_HEAD_PORT);
      commaIndex =0;

      if(osvrMessage[0] != 'N'){
        for(int i=0; i<256; i++){
          if(osvrMessage[i] == ','){
            commaIndex = i;
            break;
          }
        }

        for(int j=0; j < commaIndex; j++){
          osvrX[j]= osvrMessage[j];
        }
        x = atof(osvrX);
        pitch   = -x * pi;

        for(int k=0; k<commaIndex+7; k++){
          osvrY[k]= osvrMessage[k+commaIndex+1];
        }
        y = atof(osvrY);
        yaw   = y * pi;

        /// Example showing how to set angles, using a fraction of max speed
        AL::ALValue names       = AL::ALValue::array("HeadYaw", "HeadPitch");
        AL::ALValue angles      = AL::ALValue::array(yaw, pitch);
        float fractionMaxSpeed  = 0.1f;
        motion.setStiffnesses(names, AL::ALValue::array(1.0f, 1.0f));
        motion.setAngles(names, angles, fractionMaxSpeed);
      }
      delete osvrMessage;
    }
  }
  catch (const AL::ALError& e)
  {
    cerr << "Caught exception: " << e.what() << endl;
    return -1;
  }
  return 0;
}
