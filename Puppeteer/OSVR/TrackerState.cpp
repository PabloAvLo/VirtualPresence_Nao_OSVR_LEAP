///*****************************************************************************
///                           Universidad de Costa Rica
///                  					  Proyecto Eléctrico
///                                II Ciclo 2017
///
///                              TrackerState.cpp
///
/// Modified by: Pablo Avila B30724
/// For educational purpose
///
/// Description:
/// The bridge between OSVR HDK glasses and NAO robot is this program.
/// The Orientation information of the glasses are retrieved and transformed for
/// NAO to move it's head, as the user does.
///
/// License:
/** @file
    @brief Implementation
    @date 2014
    @author
    Sensics, Inc.
    <http://sensics.com/osvr>

    Copyright 2014 Sensics, Inc.
*/
///*****************************************************************************

/// OSVR includes
#include <osvr/ClientKit/Context.h>
#include <osvr/ClientKit/Interface.h>
#include <osvr/ClientKit/InterfaceStateC.h>
#include <osvr/Util/TimeValue.h>
#include <osvr/Util/TimeValueC.h>

/// Standard includes
#include <iostream>
#include <ctime>

/// Puppeteer incldes
#include "../../../CommLib/Sockets.h"
#include "../../../CommLib/Sockets.cpp"

/// MACROS of quaternion data structure to be send thru a socket
#define PRECISION 4
#define NEGATIVE 1
#define DECIMAL 2
#define COMMA 1

Sockets Tx;

using namespace std;

int main(int argc, char *argv[])
{

/// Ask for NAO IP address if it is not provided as an argument
  string IP = "127.0.0.1";
  if(argc < 2)
  {
    cout <<"Wrong number of arguments! " << endl
         <<"Please enter the NAO IP address:"<< endl;
    cin >> IP;
  }
  else {
    IP = argv[1];
  }

/// Use Port 3010 as default for OSVR-NAO communication
  const char *c_IP = IP.c_str();
  int Port = 3010;

  Tx.openCom(Port);
  Tx.initClient(c_IP, Port);

  char x[127];
  char y[127];
  char message[256];
  message[0] = '0';

  osvr::clientkit::ClientContext context(
      "com.osvr.exampleclients.TrackerState");

/// This is just one of the paths. You can also use:
/// /me/hands/right
/// /me/head
  osvr::clientkit::Interface head = context.getInterface("/me/head");

/// Initialize timers to reduce transmition frequency to 200 [ms]
  clock_t t1 = clock();
  clock_t t2 = clock();
  double freq= 0.2;

  while(1){
    t2 = clock();
    clock_t milliseconds = t2 - t1;
    float timediff_sec = ((float)milliseconds) / CLOCKS_PER_SEC;

    if(timediff_sec >= freq){

      context.update();
/// Every so often let's read the tracker state.
/// Similar methods exist for all other stock report types.

/// Note that there is not currently a tidy C++ wrapper for
/// state access, so developers used the C API call directly here.
      OSVR_PoseState state;
      OSVR_TimeValue timestamp;
      OSVR_ReturnCode ret =
          osvrGetPoseState(head.get(), &timestamp, &state);
      if (OSVR_RETURN_SUCCESS != ret) {
          std::cout << "No pose state!" << std::endl;
      } else {

        //  std::cout << "Got POSE state: Orientation = ("
        //            << osvrQuatGetW(&(state.rotation)) << ", ("
        //            << osvrQuatGetX(&(state.rotation)) << ", "
        //            << osvrQuatGetY(&(state.rotation)) << ", "
        //            << osvrQuatGetZ(&(state.rotation)) << "))"
        //            << std::endl;

/// Get rotation state of HDK glasses on x and y axis
        snprintf(x, sizeof x, "%f", osvrQuatGetX(&(state.rotation)) );
        snprintf(y, sizeof y, "%f", osvrQuatGetY(&(state.rotation)) );

/// Build message string with quaternions information.
        int xLength = DECIMAL + PRECISION;
        int yLength = DECIMAL + PRECISION;

        if(x[0]=='-'){
          xLength += NEGATIVE;
        }

        if(y[0]=='-'){
          yLength += NEGATIVE;
        }

        for(int i=0; i< xLength; i++){
          message[i] = x[i];
        }

        message[xLength] = ',';

        for(int i= 0; i< yLength; i++){
          message[ xLength + COMMA + i] = y[i];
        }

        for(int i=0; i< xLength + yLength + COMMA; i++){
          std::cout<<message[i];
        }
        std::cout<< std::endl;
        Tx.sendMessage(message);

        t1 = clock(); // Reset time count
        std::cout << "Printing Seconds diff: "<<  timediff_sec <<std::endl;
      }
    }
  }
    std::cout << "Library shut down, exiting." << std::endl;
    return 0;
}
