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
  tts.say(textToSay);
}
