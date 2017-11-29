///*****************************************************************************
///                           Universidad de Costa Rica
///                  					  Proyecto Eléctrico
///                                II Ciclo 2017
///
///                                LeapService.cpp
///
/// Author: Pablo Avila B30724
///
/// Description:
/// This program handles the human interface using Leap Motion to communicate
/// actions to NAO by manual gestures.
/// The Leap Motion SDK provides 4 dynamic gestures: Circle, Swipe, Key Tap and
/// Screen tap. And these movements are used with both hands bringing 8
/// different instructions.
///
/// Learn more about Leap Motion gestures in:
/// https://developer.leapmotion.com/documentation/v2/cpp/devguide/Leap_Gestures.html
//******************************************************************************

/******************************************************************************\
* Copyright (C) 2012-2014 Leap Motion, Inc. All rights reserved.               *
* Leap Motion proprietary and confidential. Not for distribution.              *
* Use subject to the terms of the Leap Motion SDK Agreement available at       *
* https://developer.leapmotion.com/sdk_agreement, or another agreement         *
* between Leap Motion and you, your company or other organization.             *
\******************************************************************************/

/// Standard Includes
#include <iostream>
#include <cstring>
#include <ctime>

/// LEAP Includes
#include "./Include/Leap.h"

/// Puppeteer Includes
#include "../CommLib/Sockets.h"
#include "../CommLib/Sockets.cpp"

using namespace std;
using namespace Leap;

///*****************************************************************************
/// Extends 'Listener' class with more attributes for Puppeteer project.
/// Timers and frequency can be used to slowdown the data transmition, in order
/// to avoid recogtition of a gesture more than once in 1 human action.

class SampleListener : public Listener {
  public:
    Sockets Tx;
    string IP;
    int Port;
    char message[256];
    clock_t t1;
	  clock_t t2;
  	double freq;
    virtual void onInit(const Controller&);
    virtual void onConnect(const Controller&);
    virtual void onFrame(const Controller&);
};

///*****************************************************************************
/// Initialize the Leap listener to get hands information.
/// Declare port number: 3000 as default port for Leap Motion-NAO communication.
/// Create and clean message char array, open socket and init client.
/// Starts timers.

void SampleListener::onInit(const Controller& controller) {
  std::cout << "Initialized" << std::endl;
  const char *c_IP = this->IP.c_str();
  this->Port = 3000;

  this->Tx.openCom(Port);
  this->Tx.initClient(c_IP, Port);

  for(int i =0; i<256; i++){
		this->message[i] =0;
	}

  this->t1 = clock();
  this->t2 = clock();
  this->freq= 0.01;
}

///*****************************************************************************
/// Enable all Leap gestures: Circle, Swipe, Key tap and Screen tap.

void SampleListener::onConnect(const Controller& controller) {
  std::cout << "Connected" << std::endl;
  controller.enableGesture(Gesture::TYPE_CIRCLE);
  controller.enableGesture(Gesture::TYPE_KEY_TAP);
  controller.enableGesture(Gesture::TYPE_SCREEN_TAP);
  controller.enableGesture(Gesture::TYPE_SWIPE);
}

///*****************************************************************************
/// This method retrieves Leap data from each frame, and interprate gestures.
/// If any gesture is recognized, a socket message will be send with an special
/// code that NAO will translate to an action.

void SampleListener::onFrame(const Controller& controller) {

/// Start timer to do a comparision and define a minimal gesture period between
/// symbols.

	this->t2 = clock();
//  clock_t milliseconds = this->t2 - this->t1;
//  float timediff_sec = ((float)milliseconds) / CLOCKS_PER_SEC;

/// Create a frame and assign 'hands' objects in that frame.
  const Frame frame = controller.frame();
  HandList hands = frame.hands();
	Hand hand = hands[0];

/// Get gestures
	Leap::GestureList gestures = frame.gestures();

	for (int g = 0; g < gestures.count(); ++g) {
	  Gesture gesture = gestures[g];

	  switch (gesture.type()) {

/// CIRCLE gesture with the LEFT hand will rise or down NAO arms as toggle.
/// With RIGHT hand will toggle open/close the right hand.
	    case Leap::Gesture::TYPE_CIRCLE:{
//	    	if(timediff_sec >= freq){
					if(hand.isRight()==false){
						this->message[0] = '1';  /// RISE/DOWN ARMS
						this->message[1] = '6';
					}
					else{
						this->message[0] = '7';  /// OPEN RIGHT HAND
						this->message[1] = 0;
  				  cout<<"RIGHT Circle: " <<this->message << endl;
					}
				  this->Tx.sendMessage(this->message);
//				  this->t1 = clock(); // Reset time count
//        }
	      break;
			}

/// KEY TAP makes the NAO crouch using RIGHT hand, and stand up with LEFT hand.
	    case Leap::Gesture::TYPE_KEY_TAP:{
		    if(hand.isRight()==false){
				  this->message[0] = '3';  /// STAND UP
				  this->message[1] = 0;
				}
				else{
					this->message[0] = '4';  /// CROUCH
				  this->message[1] = 0;
          cout<<"RIGHT Key Tap: "<< this->message << endl;
				}
		    this->Tx.sendMessage(this->message);
	      break;
			}

/// SWIPE with LEFT hand makes NAO to walk forward and with RIGHT hand stops
/// the movement.
	    case Leap::Gesture::TYPE_SWIPE:{
		    if(hand.isRight()==false){
				  this->message[0] = '8';  /// WALK FORWARD
				  this->message[1] = 0;
				}
				else{
					this->message[0] = '1';  /// STOP MOVE
				  this->message[1] = '1';
          cout<< "RIGHT Swipe: "<<this->message << endl;
				}
		    this->Tx.sendMessage(this->message);
			  break;
	    }

/// SCREEN TAP will switch the NAO enabled camera with LEFT hand and makes it
/// speak with RIGHT hand.
			case Leap::Gesture::TYPE_SCREEN_TAP:{
			  if(hand.isRight()==false){
				  this->message[0] = '1';  /// CAMERA SELECTION
				  this->message[1] = '3';
				}
				else{
					this->message[0] = '0';  /// SPEAK
				  this->message[1] = '0';
          cout<< "RIGHT Tap Screen:"<< this->message<< endl;
				}
//		    cout <<" End communication sending "<< endl;
		    this->Tx.sendMessage(this->message);
//		    Tx.closeCom(this->Port);
      break;
	    }

/// Unrecognized gestures will just been skiped.
	    default:
	      //this->t1 = clock(); // Reset time count
	      break;
		}
  }
}

int main(int argc, char *argv[]) {

  SampleListener listener;
  Controller controller;

	if(argc != 2){
     cout <<"Please enter NAO IP address"<<endl;
     cin>> listener.IP;
  }
  else{
  	  listener.IP = argv[1];
  }

  controller.addListener(listener);

///************** INITIALIZE SYSTEM ****************
		listener.message[0] = '0';  /// SPEAK
	  listener.message[1] = 0;
 	  listener.Tx.sendMessage(listener.message);
 	  listener.message[0] = '1';  /// CAMERA SETUP
	  listener.message[1] = '2';
		listener.Tx.sendMessage(listener.message);

/// Keep this process running until Enter is pressed
  std::cout << "Press Enter to quit..." << std::endl;
  std::cin.get();
  if(argc != 2){
  	std::cin.get();
  }

/// Remove the sample listener when done
  controller.removeListener(listener);
  return 0;
}
