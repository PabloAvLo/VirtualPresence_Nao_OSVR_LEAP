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
  AL::ALMotionProxy motion(puppet.naoIP, 9559);
  AL::ALRobotPostureProxy posture(puppet.naoIP, 9559);
  AL::ALVideoDeviceProxy video(puppet.naoIP, 9559);
  AL::ALPhotoCaptureProxy photo(puppet.naoIP, 9559);
  AL::ALVideoRecorderProxy recorder(puppet.naoIP, 9559);

  //******************** Variables *********************************************
  string hello = "Hello, my name is SHE";
  float speed = 0.8f;
  bool rHandOpen = true;
  bool lHandOpen = true;
  bool topCamera = true;
  bool startRecording = true;
  bool ArmsUp = false;

  bool loop=true;
  try{
    while(loop){
      message = server.receiveMessage(puppet.port);
      code = atoi(message);

      switch(code){
        case TASK0:
          puppet.speak(tts, hello); cout<< "SPEAK"<<endl; break;

        case TASK1:
          puppet.stiffnessOnOff(motion, true, "Body"); cout<< "rigid"<<endl; break;

        case TASK2:
          puppet.stiffnessOnOff(motion, false, "Body"); cout<< "free"<<endl; break;

        case 3:
          puppet.standUp(motion, posture, speed); break;

        case 4:
          puppet.crouch(motion, posture, speed); break;

        case 5:
          puppet.sitDown(motion, posture, speed); break;

        case 6:
          lHandOpen = puppet.lHandOpenClose(motion, lHandOpen); break;

        case 7:
          rHandOpen = puppet.rHandOpenClose(motion, rHandOpen); break;

        case 8:
          puppet.walk(motion, posture, speed); break;

        case 9:
          puppet.rotate(motion, posture, speed); break;

        case 10:
          puppet.moveSide(motion, posture, speed); break;

        case 11:
          puppet.stopMove(motion, posture); break;

        case 12:
          puppet.cameraSetUp(video, photo, recorder); break;

        case 13:
          topCamera = puppet.selectCamera(video, photo, recorder, topCamera); break;

        case 14: {
          int pic = 0;
          string pictureName="ShePhoto_" + pic;
          puppet.takePicture(photo, pictureName);
          pic++;
        } break;

        case 15:{
          int vid =0;
          string videoName="SheVideo_" + vid;
          startRecording = puppet.recordVideo(recorder, videoName, startRecording);
          if(startRecording == false){
            vid++;
          }
        } break;

        case 16:
          ArmsUp = puppet.moveArms(motion, ArmsUp); break;

        case 17:
          puppet.reachObject(motion); break;

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