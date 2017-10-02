//******************************************************************************
//                           Universidad de Costa Rica
//                  					  Proyecto Eléctrico
//                                II Ciclo 2017
//
//                                 TaskLib.cpp
//
// Author: Pablo Avila B30724
//******************************************************************************

//Project Includes
#include "TaskLib.h"

//************************** CONSTRUCTOR ***************************************
  TaskLib::TaskLib(){
    naoIP = "127.0.0.1";
    port = 3000;
  }

//************************** DESTRUCTOR ****************************************
  TaskLib::~TaskLib(){}

//************************** SPEAK *********************************************
 void TaskLib::speak(AL::ALTextToSpeechProxy tts, string textToSay){
  tts.post.say(textToSay);
}

//************************** STIFFNESS ON/OFF **********************************
 bool TaskLib::stiffnessOnOff(AL::ALMotionProxy motion, bool rigid=true, string bodyPart= "body"){
   float stiffnesses  = 1.0f;

   if(rigid == false){
     stiffnesses  = 0.0f;
   }
  motion.post.setStiffnesses(bodyPart, stiffnesses);

  return (!rigid);
}

//************************** STAND UP ******************************************
 void TaskLib::standUp(AL::ALMotionProxy motion, AL::ALRobotPostureProxy posture,float speed){
   string standInit = "StandInit";

   motion.setStiffnesses("body", 1.0f);
   posture.goToPosture(standInit,speed);
}

//************************** CROUCH ********************************************
void TaskLib::crouch(AL::ALMotionProxy motion, AL::ALRobotPostureProxy posture,float speed){
  string standInit = "Crouch";
  motion.setStiffnesses("body", 1.0f);
  posture.goToPosture(standInit,speed);

  motion.setStiffnesses("body", 0.0f);
  motion.setStiffnesses("Head", 1.0f);
}

//************************** SIT DOWN ******************************************
void TaskLib::sitDown(AL::ALMotionProxy motion, AL::ALRobotPostureProxy posture,float speed){
  string standInit = "Sit";

  motion.setStiffnesses("body", 1.0f);
  posture.goToPosture(standInit,speed);

  motion.setStiffnesses("body", 0.0f);
  motion.setStiffnesses("Head", 1.0f);
}

//************************** LEFT HAND OPEN/CLOSE ******************************
bool TaskLib::lHandOpenClose(AL::ALMotionProxy motion, bool open){

  motion.setStiffnesses("LHand", 1.0f);

  if(open == true){
    motion.openHand("LHand");
  }
  else{
    motion.closeHand("LHand");
  }

  return (!open);
}

//************************** RIGHT HAND OPEN/CLOSE ******************************
bool TaskLib::rHandOpenClose(AL::ALMotionProxy motion, bool open){

  motion.setStiffnesses("RHand", 1.0f);

  if(open == true){
    motion.openHand("RHand");
  }
  else{
    motion.closeHand("RHand");
  }

  return (!open);
}
