#include <iostream>
#include <cstring>
#include <GL/glu.h>
#include "Leap.h"
#include "LeapUtilGL.h"
#include "Sockets.h"
//#include "cinder/gl/gl.h"

using namespace std;
using namespace Leap;
using namespace LeapUtilGL;

class SampleListener : public Listener {
  public:
    virtual void onInit(const Controller&);
    virtual void onConnect(const Controller&);
    virtual void onFrame(const Controller&);
};

int turno =0;

void SampleListener::onInit(const Controller& controller) {
  std::cout << "Initialized" << std::endl;
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
  Sockets Tx;
  char* mensaje;
  mensaje =new char [256];

  string IP = "10.0.1.122";
  const char *c_IP = IP.c_str();

  // Get gestures
  Leap::GestureList gestures = frame.gestures();
  for (int g = 0; g < gestures.count(); ++g) {
    Gesture gesture = gestures[g];
    switch (gesture.type()) {

      case Leap::Gesture::TYPE_CIRCLE:
        //Handle circle gestures
        mensaje = "0";
        if(turno==0){
          cout<< "Circle"<< endl;
          Tx.sendMessage(c_IP, 9000, mensaje);
        turno=1;
        }
        break;

      case Leap::Gesture::TYPE_KEY_TAP:
        //Handle key tap gestures
        cout<< "Key"<< endl;
        break;

      case Leap::Gesture::TYPE_SCREEN_TAP:
        //Handle screen tap gestures
        cout<< "Tap"<< endl;
        break;

      case Leap::Gesture::TYPE_SWIPE:
        //Handle swipe gestures
        mensaje = "1";
        if(turno==1){
            cout<< "Swipe"<< endl;
            Tx.sendMessage(c_IP, 9000, mensaje);
            turno=0;
          }
        break;

      default:
        //Handle unrecognized gestures
        break;
    }
  }
}

int main(int argc, char *argv[]) {

  if(argc < 3) {
     cerr <<"Wrong number of arguments!"<< endl<<"Please enter IP address and Port"<<endl;
     exit(0);
  }
  //Sockets Tx;
  SampleListener listener;
  Controller controller;

  controller.addListener(listener);


/*
  GLVector4fv vBoneColor;
  GLVector4fv vJointColor;
  Hand hand;
  drawGrid(kPlane_XY, 10,10);
  drawSkeletonHand(hand,vBoneColor,vJointColor);
*/
/*
  ImageList images = frame.images();
  for(int i = 0; i < 2; i++){
      Image image = images[i];

      const unsigned char* image_buffer = image.data();

      //Draw the raw image data as a greyscale bitmap
      Surface surface(image.width(), image.height(), image.width() * 4, SurfaceChannelOrder::RGBA);
      int cursor = 0;
      Surface::Iter iter = surface.getIter();
      while( iter.line() ) {
          while( iter.pixel() ) {
              iter.r() = image_buffer[cursor];
              iter.g() = iter.b() = iter.r();
              iter.a() = 255;
              cursor++;
          }
      }
  }
*/

  // Keep this process running until Enter is pressed
  std::cout << "Press Enter to quit..." << std::endl;
  for(int i=0; i<4;i++)
    std::cin.get();

  controller.removeListener(listener);
}
