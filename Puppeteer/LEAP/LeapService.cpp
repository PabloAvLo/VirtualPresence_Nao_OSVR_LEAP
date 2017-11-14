#include <iostream>
#include <cstring>
#include "./Include/Leap.h"
#include "../CommLib/Sockets.h"
#include "../CommLib/Sockets.cpp"


using namespace std;
using namespace Leap;

class SampleListener : public Listener {
  public:
    Sockets Tx;
    string IP;
    int Port;
    virtual void onInit(const Controller&);
    virtual void onConnect(const Controller&);
    virtual void onFrame(const Controller&);
};

void SampleListener::onInit(const Controller& controller) {
  std::cout << "Initialized" << std::endl;
  const char *c_IP = this->IP.c_str();
  this->Port = 3000;

  this->Tx.openCom(Port);
  this->Tx.initClient(c_IP, Port);
}

void SampleListener::onConnect(const Controller& controller) {
  std::cout << "Connected" << std::endl;
  controller.enableGesture(Gesture::TYPE_CIRCLE);
  controller.enableGesture(Gesture::TYPE_KEY_TAP);
  controller.enableGesture(Gesture::TYPE_SCREEN_TAP);
  controller.enableGesture(Gesture::TYPE_SWIPE);
}

void SampleListener::onFrame(const Controller& controller) {
//    Controller controller;
  const Frame frame = controller.frame();	
  HandList hands = frame.hands();
	Hand hand = hands[0];

  char mensaje[256]; 
	for(int i =0; i<256; i++){
		mensaje[i] =0;
	}
	

  // Get gestures
  Leap::GestureList gestures = frame.gestures();
  for (int g = 0; g < gestures.count(); ++g) {
    Gesture gesture = gestures[g];
    switch (gesture.type()) {

      case Leap::Gesture::TYPE_CIRCLE:{
      	//Handle circle gestures
      	if(hand.isLeft()==false){
		      mensaje[0] = '1';  // RISE/DOWN ARMS
		      mensaje[1] = '6';
		    }
		    else{
			    mensaje[0] = '7';  // OPEN RIGHT HAND
		      mensaje[1] = 0;
		    }
        cout<<"RIGHT Circle: " <<mensaje << endl;
        this->Tx.sendMessage(mensaje);
        break;
				}
				
      case Leap::Gesture::TYPE_KEY_TAP:{
        //Handle key tap gestures
        if(hand.isLeft()==false){
		      mensaje[0] = '3';  // STAND UP
		      mensaje[1] = 0;
		    }
		    else{
			    mensaje[0] = '4';  // CROUCH
		      mensaje[1] = 0;
		    }
        cout<<"RIGHT Key Tap: "<< mensaje << endl;
        this->Tx.sendMessage(mensaje);
        break;
        }

      case Leap::Gesture::TYPE_SWIPE:{
        //Handle swipe gestures
        if(hand.isLeft()==false){
		      mensaje[0] = '8';  // WALK FORWARD
		      mensaje[1] = 0;
		    }
		    else{
			    mensaje[0] = '1';  // STOP MOVE
		      mensaje[1] = '1';
		    }
        cout<< "RIGHT Swipe: "<<mensaje << endl;
        this->Tx.sendMessage(mensaje);
        break;
        }

			case Leap::Gesture::TYPE_SCREEN_TAP:{
        //Handle screen tap gestures
        if(hand.isLeft()==false){
		      mensaje[0] = '1';  // CAMERA SELECTION
		      mensaje[1] = '3';
		    }
		    else{
			    mensaje[0] = '1';  // PICTURE CAPTURE
		      mensaje[1] = '4';
		    }
        cout<< "RIGHT Tap Screen:"<< mensaje<< endl; 
        //<< endl <<" (End communication sending )"<< endl;
        this->Tx.sendMessage(mensaje);
        //Tx.closeCom(this->Port);
        break;
        }
        
      default:
        //Handle unrecognized gestures
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

		//**************  INITIALIZE SYSTEM ****************
 	  char init[]={'0',0}; 							// SPEAK
 	  listener.Tx.sendMessage(init);
 	  char cameraInit[] = {'1','2',0};	// CAMERA SETUP  
		listener.Tx.sendMessage(cameraInit);

  // Keep this process running until Enter is pressed
  std::cout << "Press Enter to quit..." << std::endl;
  std::cin.get();
  if(argc != 2){
  	std::cin.get();
  }

  // Remove the sample listener when done
  controller.removeListener(listener);

  return 0;
}