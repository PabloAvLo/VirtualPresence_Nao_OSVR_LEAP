
// Standard Includes
#include <iostream>
#include <cstring>
#include <ctime>

// LEAP Includes
#include "./Include/Leap.h"

// Puppeteer Includes
#include "../CommLib/Sockets.h"
#include "../CommLib/Sockets.cpp"


using namespace std;
using namespace Leap;

class SampleListener : public Listener {
  public:
    Sockets Tx;
    string IP;
    int Port;
    char mensaje[256];
    clock_t t1;
	  clock_t t2;
  	double frec;
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
  
  for(int i =0; i<256; i++){
		this->mensaje[i] =0;
	}
  
  this->t1 = clock();
  this->t2 = clock();
  this->frec= 0.01;
}

void SampleListener::onConnect(const Controller& controller) {
  std::cout << "Connected" << std::endl;
  controller.enableGesture(Gesture::TYPE_CIRCLE);
  controller.enableGesture(Gesture::TYPE_KEY_TAP);
  controller.enableGesture(Gesture::TYPE_SCREEN_TAP);
  controller.enableGesture(Gesture::TYPE_SWIPE);
}

void SampleListener::onFrame(const Controller& controller) {
	this->t2 = clock();
  clock_t milliseconds = this->t2 - this->t1;
  float timediff_sec = ((float)milliseconds) / CLOCKS_PER_SEC;

  const Frame frame = controller.frame();	
  HandList hands = frame.hands();
	Hand hand = hands[0];

	// Get gestures
	Leap::GestureList gestures = frame.gestures();

	for (int g = 0; g < gestures.count(); ++g) {
	  Gesture gesture = gestures[g];
	  
	  switch (gesture.type()) {
	    case Leap::Gesture::TYPE_CIRCLE:{
				//Handle circle gestures

	    	if(timediff_sec >= frec){
					if(hand.isLeft()==false){
						this->mensaje[0] = '1';  // RISE/DOWN ARMS
						this->mensaje[1] = '6';
					}
					else{
						this->mensaje[0] = '7';  // OPEN RIGHT HAND
						this->mensaje[1] = 0;
					}
				  cout<<"RIGHT Circle: " <<this->mensaje << endl;
				  this->Tx.sendMessage(this->mensaje);
				  this->t1 = clock(); // Reset time count
	      }
	      break;
			}
			
	    case Leap::Gesture::TYPE_KEY_TAP:{
			  //Handle key tap gestures
	    	
	    	if(timediff_sec >= frec){
			    if(hand.isLeft()==false){
					  this->mensaje[0] = '3';  // STAND UP
					  this->mensaje[1] = 0;
					}
					else{
						this->mensaje[0] = '4';  // CROUCH
					  this->mensaje[1] = 0;
					}
			    cout<<"RIGHT Key Tap: "<< this->mensaje << endl;
			    this->Tx.sendMessage(this->mensaje);
			    this->t1 = clock(); // Reset time count
	      break;
	      }
			}
	    
	    case Leap::Gesture::TYPE_SWIPE:{
	      //Handle swipe gestures
	      if(timediff_sec >= frec){
			    if(hand.isLeft()==false){
					  this->mensaje[0] = '8';  // WALK FORWARD
					  this->mensaje[1] = 0;
					}
					else{
						this->mensaje[0] = '1';  // STOP MOVE
					  this->mensaje[1] = '1';
					}
			    cout<< "RIGHT Swipe: "<<this->mensaje << endl;
			    this->Tx.sendMessage(this->mensaje);
			    this->t1 = clock(); // Reset time count
	      }
	      break;
	    }

			case Leap::Gesture::TYPE_SCREEN_TAP:{
			if(timediff_sec >= frec){
			    //Handle screen tap gestures
			    if(hand.isLeft()==false){
					  this->mensaje[0] = '1';  // CAMERA SELECTION
					  this->mensaje[1] = '3';
					}
					else{
						this->mensaje[0] = '1';  // PICTURE CAPTURE
					  this->mensaje[1] = '4';
					}
			    cout<< "RIGHT Tap Screen:"<< this->mensaje<< endl; 
			    //<< endl <<" (End communication sending )"<< endl;
			    this->Tx.sendMessage(this->mensaje);
			    //Tx.closeCom(this->Port);
			    this->t1 = clock(); // Reset time count
				}
	      break;
	    }
	      
	    default:
	      //Handle unrecognized gestures
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

		//**************  INITIALIZE SYSTEM ****************
		listener.mensaje[0] = '0';  // SPEAK
	  listener.mensaje[1] = 0;					
 	  listener.Tx.sendMessage(listener.mensaje);
 	  listener.mensaje[0] = '1';  // CAMERA SETUP  
	  listener.mensaje[1] = '2';
		listener.Tx.sendMessage(listener.mensaje);

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
