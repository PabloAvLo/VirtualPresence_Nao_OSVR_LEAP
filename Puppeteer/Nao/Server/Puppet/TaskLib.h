//******************************************************************************
//                           Universidad de Costa Rica
//                  					  Proyecto Eléctrico
//                                II Ciclo 2017
//
//                                  TaskLib.h
//
// Author: Pablo Avila B30724
//******************************************************************************

#ifndef TASKLIB_H
#define TASKLIB_H

// Naoqi Includes
#include <alerror/alerror.h>
#include <alproxies/altexttospeechproxy.h>

// Standar Includes
#include <iostream>
#include <string>
using namespace std;

//************************** TASK DEFINES **************************************
#define TASK1 0
#define TASK2 1
#define TASK3 2

class TaskLib{

public:
  string naoIP;
  unsigned int port;

  //****************************************************************************
  // Constructor
    TaskLib();

  //****************************************************************************
  // Destructor
    ~TaskLib();

  //****************************************************************************
  /**             speak
   * Description: This function makes the Nao speak the input string.
   * @param string textToSay
   * return        void
  **/
  void speak(AL::ALTextToSpeechProxy tts, string textToSay);
};
#endif
