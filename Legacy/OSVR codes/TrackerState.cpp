/** @file
    @brief Implementation

    @date 2014

    @author
    Sensics, Inc.
    <http://sensics.com/osvr>
*/

// Copyright 2014 Sensics, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Internal Includes
#include <osvr/ClientKit/Context.h>
#include <osvr/ClientKit/Interface.h>
#include <osvr/ClientKit/InterfaceStateC.h>
#include <osvr/sockets/Sockets.h>
#include <osvr/sockets/sockets.cpp>
#include <osvr/Util/TimeValue.h>
#include <osvr/Util/TimeValueC.h>

// Standard Includes
#include <iostream>
#include <ctime>

#define PRECISION 4
#define NEGATIVE 1
#define DECIMAL 2
#define COMMA 1

Sockets Tx;

using namespace std;
int main() {

  string IP = "127.0.0.1";
  const char *c_IP = IP.c_str();
  int Port = 3010;

  Tx.openCom(Port);
  Tx.initClient(c_IP, Port);

  char x[127];
  char y[127];
  char mensaje[256];
  mensaje[0] = '0';

  osvr::clientkit::ClientContext context(
      "com.osvr.exampleclients.TrackerState");

  // This is just one of the paths. You can also use:
  // /me/hands/right
  // /me/head
  osvr::clientkit::Interface head = context.getInterface("/me/head");

  clock_t t1 = clock();
  clock_t t2 = clock();
  double frec= 0.2;

  while(1){
    t2 = clock();
    clock_t milliseconds = t2 - t1;
    float timediff_sec = ((float)milliseconds) / CLOCKS_PER_SEC;

    if(timediff_sec >= frec){

      context.update();
      // Every so often let's read the tracker state.
      // Similar methods exist for all other stock report types.

      // Note that there is not currently a tidy C++ wrapper for
      // state access, so we're using the C API call directly here.
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

        snprintf(x, sizeof x, "%f", osvrQuatGetX(&(state.rotation)) );
        snprintf(y, sizeof y, "%f", osvrQuatGetY(&(state.rotation)) );

        int xLength = DECIMAL + PRECISION;
        int yLength = DECIMAL + PRECISION;

        if(x[0]=='-'){
          xLength += NEGATIVE;
        }

        if(y[0]=='-'){
          yLength += NEGATIVE;
        }

        for(int i=0; i< xLength; i++){
          mensaje[i] = x[i];
        }

        mensaje[xLength] = ',';

        for(int i= 0; i< yLength; i++){
          mensaje[ xLength + COMMA + i] = y[i];
        }

        for(int i=0; i< xLength + yLength + COMMA; i++){
          std::cout<<mensaje[i];
        }
        std::cout<< std::endl;
        Tx.sendMessage(mensaje);

        t1 = clock(); // Reset time count
        std::cout << "Printing Seconds diff: "<<  timediff_sec <<std::endl;
      }
    }
  }
    std::cout << "Library shut down, exiting." << std::endl;
    return 0;
}
