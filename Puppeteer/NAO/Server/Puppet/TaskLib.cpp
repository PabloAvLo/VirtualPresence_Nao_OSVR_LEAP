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
 bool TaskLib::stiffnessOnOff(AL::ALMotionProxy motion, bool rigid=true, string bodyPart= "Body"){
   float stiffnesses  = 1.0f;

   if(rigid == false){
     stiffnesses  = 0.0f;
   }
  motion.post.setStiffnesses(bodyPart, stiffnesses);

  return (!rigid);
}

//************************** STAND UP ******************************************
 void TaskLib::standUp(AL::ALMotionProxy motion, AL::ALRobotPostureProxy posture, float speed){
   string standInit = "StandInit";

   motion.setStiffnesses("Body", 1.0f);
   posture.goToPosture(standInit, speed);
}

//************************** CROUCH ********************************************
void TaskLib::crouch(AL::ALMotionProxy motion, AL::ALRobotPostureProxy posture, float speed){
  string crouch = "Crouch";
  motion.setStiffnesses("Body", 1.0f);
  posture.goToPosture(crouch, speed);

  motion.setStiffnesses("Body", 0.0f);
  motion.setStiffnesses("Head", 1.0f);
}

//************************** SIT DOWN ******************************************
void TaskLib::sitDown(AL::ALMotionProxy motion, AL::ALRobotPostureProxy posture, float speed){
  string sit = "Sit";

  motion.setStiffnesses("Body", 1.0f);
  posture.goToPosture(sit, speed);

  motion.setStiffnesses("Body", 0.0f);
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

//************************** RIGHT HAND OPEN/CLOSE *****************************
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

//************************** WALK **********************************************
void TaskLib::walk(AL::ALMotionProxy motion, AL::ALRobotPostureProxy posture, const float vX){
  string standInit = "StandInit";
  string actuator= "Body";
  float speed = 0.9f;

  motion.setStiffnesses(actuator, 1.0f);
  posture.goToPosture(standInit, speed);
  motion.moveToward(vX, 0.0f, 0.0f);
}

//************************** ROTATE ********************************************
void TaskLib::rotate(AL::ALMotionProxy motion, AL::ALRobotPostureProxy posture, const float vTheta){
  string standInit = "StandInit";
  string actuator= "Body";
  float speed = 0.9f;

  motion.setStiffnesses(actuator, 1.0f);
  posture.goToPosture(standInit, speed);
  motion.moveToward(0.0f, 0.0f, vTheta);
}

//************************** MOVE SIDE *****************************************
void TaskLib::moveSide(AL::ALMotionProxy motion, AL::ALRobotPostureProxy posture, const float vY){
  string standInit = "StandInit";
  string actuator= "Body";
  float speed = 0.9f;

  motion.setStiffnesses(actuator, 1.0f);
  posture.goToPosture(standInit, speed);
  motion.moveToward(0.0f, vY, 0.0f);
}

//************************** STOP MOVE *****************************************
void TaskLib::stopMove(AL::ALMotionProxy motion, AL::ALRobotPostureProxy posture){
  string standInit = "StandInit";
  float speed = 0.9f;

  motion.stopMove();
  posture.goToPosture(standInit, speed);
}

//************************** CAMERA SET UP *************************************
void TaskLib::cameraSetUp(AL::ALVideoDeviceProxy video, AL::ALPhotoCaptureProxy photo, AL::ALVideoRecorderProxy recorder){
  // Video Device

  // Take Pictures
  photo.setPictureFormat("png");
  photo.setResolution(2); // kQQVGA

  // Record Video
  recorder.setVideoFormat("MJPG");
  recorder.setResolution(2); // kQQVGA
  recorder.setFrameRate(15); //15 FPS max.
}

//************************** SELECT CAMERA  ************************************
bool TaskLib::selectCamera(AL::ALVideoDeviceProxy video, AL::ALPhotoCaptureProxy photo, AL::ALVideoRecorderProxy recorder, bool top){
  bool cameraId=0;

  if(top == false){
    cameraId  = 1;
  }

  photo.setCameraID(cameraId);
  recorder.setCameraID(cameraId);
  video.setActiveCamera(cameraId);
  return (!cameraId);
}

//************************** TAKE PICTURE **************************************
void TaskLib::takePicture(AL::ALPhotoCaptureProxy photo, string fileName){
  string path = "/home/Puppeteer/Picutures/";
  bool overWrite = false;
  system("mkdir /home/Puppeteer/Picutures/");
  photo.takePicture(path, fileName, overWrite);
}

//************************** RECORD VIDEO **************************************
bool TaskLib::recordVideo(AL::ALVideoRecorderProxy recorder, string fileName, bool startRec){
  if(startRec == true){
    string path = "/home/Puppeteer/Videos/";
    bool overWrite = false;
    system("mkdir /home/Puppeteer/Videos/");
    recorder.startRecording(path, fileName, overWrite);
  }
  else{
    recorder.stopRecording();
  }

  return(!startRec);
}

//************************** MOVE ARMS ***********************************
bool TaskLib::moveArms(AL::ALMotionProxy motion, bool up){
  AL::ALValue joints = AL::ALValue::array("LShoulderPitch", "RShoulderPitch");

  float angle = 1.571f; // PI/2
  float fractionMaxSpeed  = 0.3f;

  if(up == false){
    angle = angle * (-1);
  }

  AL::ALValue angles  = AL::ALValue::array(angle, angle);
  motion.setStiffnesses(joints, AL::ALValue::array(1.0f, 1.0f));
  motion.setAngles(joints, angles, fractionMaxSpeed);

  return (!up);
}

//************************** REACH OBJECT ***********************************
void TaskLib::reachObject(AL::ALMotionProxy motion){
  AL::ALValue shoulders = AL::ALValue::array("LShoulderPitch", "RShoulderPitch");
  AL::ALValue elbows = AL::ALValue::array("LShoulderPitch", "RShoulderPitch");
  AL::ALValue arms = AL::ALValue::array("LArm", "RArm");

  float shoulderAngle = 0.0f; // PI/2
  float elbowAngle = -1.54f; // -88.5 [deg]
  float fractionMaxSpeed  = 0.3f;

  AL::ALValue elbowAngles  = AL::ALValue::array(elbowAngle, elbowAngle);
  AL::ALValue shoulderAngles  = AL::ALValue::array(shoulderAngle, shoulderAngle);

  motion.setStiffnesses(arms, AL::ALValue::array(1.0f, 1.0f));
  motion.setAngles(elbows, elbowAngles, fractionMaxSpeed);
  motion.setAngles(shoulders, shoulderAngles, fractionMaxSpeed);
  motion.setAngles(elbows, shoulderAngles, fractionMaxSpeed);
}
