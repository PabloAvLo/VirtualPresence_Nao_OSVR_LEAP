///*****************************************************************************
///                           Universidad de Costa Rica
///                  					  Proyecto Eléctrico
///                                II Ciclo 2017
///
///                             PuppetGestures.cpp
///
/// Author: Pablo Avila B30724
///
/// Description:
/// To record a both hands gesture is recomended to place your left hand first
/// and then the right hand, to create clean/ordered data.
/// Or you can place both hands before start recording and ask someone to start
/// the program.
/// Is highly recommended to execute 'Visualizer' to ensure the correct possition
/// of the hands in the gesture.
///*****************************************************************************

/******************************************************************************\
* Copyright (C) 2012-2014 Leap Motion, Inc. All rights reserved.               *
* Leap Motion proprietary and confidential. Not for distribution.              *
* Use subject to the terms of the Leap Motion SDK Agreement available at       *
* https://developer.leapmotion.com/sdk_agreement, or another agreement         *
* between Leap Motion and you, your company or other organization.             *
\******************************************************************************/

/// Standard Includes
#include <iostream>
#include <fstream>
#include <cstring>

/// Puppeteer Includes
#include "./Include/Leap.h"

using namespace std;
using namespace Leap;

///*****************************************************************************
/// Extends Listener class to open and modify an output file.
/// The Leap Motion structure is:
/// Frame:
///       Hands (Left and Right)      Fingers
///       Arms                        Thumb, Index, Middel, Ring and Pinky
///       Elbow and Wristle           each finger has the next bones:
///                                   Metacarpal, Proximal, Middle and Distal.

class SampleListener : public Listener {
  public:
    virtual void onInit(const Controller&);
    virtual void onExit(const Controller&);
    virtual void onFrame(const Controller&);
    ofstream outputFile;
  private:
};

const std::string fingerNames[] = {"Thumb", "Index", "Middle", "Ring", "Pinky"};
const std::string boneNames[] = {"Metacarpal", "Proximal", "Middle", "Distal"};

///*****************************************************************************
/// Initialize Listener
void SampleListener::onInit(const Controller& controller) {
  cout << "Initialized" << endl;
}

///*****************************************************************************
///  Exit Listener
void SampleListener::onExit(const Controller& controller) {
  cout << "Exited" << endl;
}

///*****************************************************************************
/// This method make the transformation from absolute bones vectors to the
/// relative vectors, using the center of the hand as origin of the coordinate
/// system. The (x,y,z) vector of each bone of all fingers on every hand in the
/// frame will be retrieve and store in and .csv file in order to define a new
/// gesture based on these distances with +/- tolerance.

void SampleListener::onFrame(const Controller& controller) {

  // Get the most recent frame and report some basic information
  const Frame frame = controller.frame();
  HandList hands = frame.hands();

  for (HandList::const_iterator hl = hands.begin(); hl != hands.end(); ++hl) {
    // Get the first hand
    const Hand hand = *hl;
    Arm arm = hand.arm();

    if(hand.isLeft()==false && frame.hands().count() <2){
      this->outputFile <<", , , , , , , , , , , , , , , , , , , , ,";
    }
		else if(hand.isLeft()==true){
			this->outputFile <<"Left Hand,";
		}
    Vector handCenter = hand.palmPosition();

    // Get fingers
    const FingerList fingers = hand.fingers();
    for (FingerList::const_iterator fl = fingers.begin(); fl != fingers.end(); ++fl) {
      const Finger finger = *fl;

      // Get finger bones
      for (int b = 0; b < 4; ++b) {
        Bone::Type boneType = static_cast<Bone::Type>(b);
        Bone bone = finger.bone(boneType);

        Vector bonePos = bone.center();

/// Move the coordinated system to the center of the hand.
        Vector relBonePos = bonePos - handCenter;
        float relMagnitude = relBonePos.magnitude();
	      this->outputFile << relMagnitude<<",";
      }
    }
  }
  this->outputFile<<endl;
}


int main(int argc, char* argv[]) {

/// Create a sample listener and controller
  SampleListener listener;
  Controller controller;

  string fileName;
  string resultsFolder = "Gestures_Samples";
  if(argc != 2)
  {
    cout << "Enter name of output .csv file: " << endl;
    cin >> fileName;
  }
  else {
    fileName = argv[1];
  }

  string path = "./"+ resultsFolder +"/"+fileName;
  listener.outputFile.open(path);


  /// ************* PRINTS *************************
  listener.outputFile<<"    Universidad de Costa Rica   "<< endl
      							 <<"       Proyecto Eléctrico       "<< endl
      							 <<"         II Ciclo 2017          "<< endl
      							 <<"          "<<fileName<<"        "<< endl
      							 <<" Author: Pablo Avila B30724     "<< endl
      							 << endl
      							 <<" Media:"<< endl
     								 <<" Max Deviation:"<< endl
     								 <<" Standar Deviation:"<< endl
     								 << endl;

  listener.outputFile <<",LEFT HAND:, , , , , , , , , , , , , , , , , , , , RIGHT HAND:"<<endl;
  listener.outputFile << ",Thumb, , , ,Index, , , ,Middle, , , ,Ring, , , ,Pinky, , , ,"
       << "Thumb, , , ,Index, , , ,Middle, , , ,Ring, , , ,Pinky"<< endl << ",";
  for(int i=0; i<10; i++){
    listener.outputFile <<"Metacarpal, Proximal, Middle, Distal,";
  }
  listener.outputFile << endl;


  /// Have the sample listener receive events from the controller
  controller.addListener(listener);

  if (argc > 1 && strcmp(argv[1], "--bg") == 0)
    controller.setPolicy(Leap::Controller::POLICY_BACKGROUND_FRAMES);

  /// Keep this process running until Enter is pressed
  std::cout << "Press Enter to quit..." << std::endl;
  std::cin.get();
  if(argc != 2){
  	std::cin.get();
  }
  listener.outputFile.close();

  /// Remove the sample listener when done
  controller.removeListener(listener);
  return 0;
}
