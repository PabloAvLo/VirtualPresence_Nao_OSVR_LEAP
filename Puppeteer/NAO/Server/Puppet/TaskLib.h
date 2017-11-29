///*****************************************************************************
///                           Universidad de Costa Rica
///                  					  Proyecto Eléctrico
///                                II Ciclo 2017
///
///                                  TaskLib.h
///
/// Author: Pablo Avila B30724
///
/// Description:
/// Definition of Task Library for NAO teleorator robot.
///*****************************************************************************

#ifndef TASKLIB_H
#define TASKLIB_H

/// Naoqi includes
#include <alerror/alerror.h>
#include <alproxies/altexttospeechproxy.h>
#include <alproxies/almotionproxy.h>
#include <alproxies/alrobotpostureproxy.h>
#include <alproxies/alphotocaptureproxy.h>
#include <alproxies/alvideodeviceproxy.h>
#include <alproxies/alvideorecorderproxy.h>

/// Standard includes
#include <iostream>
#include <string>
using namespace std;

///************************* TASK DEFINES **************************************
#define TASK0 0
#define TASK1 1
#define TASK2 2

class TaskLib{

public:
  string naoIP;
  unsigned int port;

  ///***************************************************************************
  /// Constructor
  TaskLib();

  ///***************************************************************************
  /// Destructor
  ~TaskLib();

  ///***************************************************************************
  /**             speak
   * Description: This function makes the Nao speak the input string.
   * @param AL::ALTextToSpeechProxy tts
   * @param string                  textToSay
   * return void
  **/
  void speak(AL::ALTextToSpeechProxy tts, const string textToSay);

  ///***************************************************************************
  /**             stiffnessOnOff
   * Description: This function sets the stiffness of the Nao On or Off in the
   * body part specified. Example of body parts are Names of joints, chains,
   * 'Body', 'JointActuators','Joints' or 'Actuators'.
   * Joints as: 'HeadYaw', 'HeadPitch','LHand'.
   * Chains as: 'Head', 'LArm', 'LLeg', 'RLeg', 'RArm'.
   * See: http://doc.aldebaran.com/2-1/family/robots/bodyparts.html
   * for more information.
   * @param AL::ALMotionProxy motion
   * @param bool              rigid
   * @param string            bodyPart
   * return void
  **/
  bool stiffnessOnOff(AL::ALMotionProxy motion, bool rigid, const string bodyPart);

  ///***************************************************************************
  /**             sandUp
   * Description: Gets the Nao in "Stand Init" position
   * See: http://doc.aldebaran.com/2-1/family/robots/postures_robot.html#robot-postures
   * for more information.
   * @param AL::ALMotionProxy       motion
   * @param AL::ALRobotPostureProxy posture
   * @param float                   speed
   * return void
  **/
  void standUp(AL::ALMotionProxy motion, AL::ALRobotPostureProxy posture, const float speed);

  ///***************************************************************************
  /**             Crouch
   * Description: Gets the Nao in "Crouch" position and set stiffnesses Off except its Head.
   * See: http://doc.aldebaran.com/2-1/family/robots/postures_robot.html#robot-postures
   * for more information.
   * @param AL::ALMotionProxy       motion
   * @param AL::ALRobotPostureProxy posture
   * @param float                   speed
   * return void
  **/
  void crouch(AL::ALMotionProxy motion, AL::ALRobotPostureProxy posture, const float speed);

  ///***************************************************************************
  /**             sitDown
   * Description: Gets the Nao in "Sit Down" position and set stiffnesses Off except its Head.
   * See: http://doc.aldebaran.com/2-1/family/robots/postures_robot.html#robot-postures
   * for more information.
   * @param AL::ALMotionProxy       motion
   * @param AL::ALRobotPostureProxy posture
   * @param float                   speed
   * return void
  **/
  void sitDown(AL::ALMotionProxy motion, AL::ALRobotPostureProxy posture, const float speed);

  ///***************************************************************************
  /**             lHandOpenClose
   * Description: Open or close the left hand of Nao based on 'open' parameter,
   * and return the oposite status. True for open, false for close.
   * @param AL::ALMotionProxy       motion
   * @param bool                    open
   * return bool                    handStatus
  **/
  bool lHandOpenClose(AL::ALMotionProxy motion, const bool open);

  ///***************************************************************************
  /**             rHandOpenClose
   * Description: Open or close the right hand of Nao based on 'open' parameter,
   * and return the oposite status. True for open, false for close.
   * @param AL::ALMotionProxy       motion
   * @param bool                    open
   * return bool                    handStatus
  **/
  bool rHandOpenClose(AL::ALMotionProxy motion, const bool open);

  ///***************************************************************************
  /**             walk
   * Description: This function makes the Nao move straight forward or backward
   * with negative numbers, with a constant (normalized) velocity 'vX'.
   * @param AL::ALMotionProxy       motion
   * @param AL::ALRobotPostureProxy posture
   * @param float                   vX
   * return void
  **/
  void walk(AL::ALMotionProxy motion, AL::ALRobotPostureProxy posture, const float vX);

  ///***************************************************************************
  /**             rotate
   * Description: Rotates the Nao with a constant (normalized) velocity 'vTHeta'
   * clockwise using negative numbers.
   * @param AL::ALMotionProxy       motion
   * @param AL::ALRobotPostureProxy posture
   * @param float                   vTheta
   * return void
  **/
  void rotate(AL::ALMotionProxy motion, AL::ALRobotPostureProxy posture, const float vTheta);

  ///***************************************************************************
  /**             moveSide
   * Description: Positive 'vY' values makes the Nao move to the left with a
   * constant velocity.
   * @param AL::ALMotionProxy       motion
   * @param AL::ALRobotPostureProxy posture
   * @param float                   vY
   * return void
  **/
  void moveSide(AL::ALMotionProxy motion, AL::ALRobotPostureProxy posture, const float vY);

  ///***************************************************************************
  /**             stopMove
   * Description: Stops current Nao movement, and goes to 'standInit' posture.
   * @param AL::ALMotionProxy       motion
   * @param AL::ALRobotPostureProxy posture
   * return void
  **/
  void stopMove(AL::ALMotionProxy motion, AL::ALRobotPostureProxy posture);

  //------------------------------------------------------------------------------------------

  ///***************************************************************************
  /**             cameraSetUp
   * Description: Initializa some camera parameters as picture and video format,
   * camera resolition and frames per second.
   * More information of NAO Video Camera on:
   * - http://doc.aldebaran.com/2-1/family/robots/video_robot.html#cameraindex-nao
   * @param AL::ALVideoDeviceProxy        video
   * @param AL::ALPhotoCaptureProxy       photo
   * @param AL::ALVideoRecorderProxy      recorder
   * return void
  **/
  void cameraSetUp(AL::ALVideoDeviceProxy video, AL::ALPhotoCaptureProxy photo, AL::ALVideoRecorderProxy recorder);

  ///***************************************************************************
  /**             selectCamera
   * Description: Switch the active camera.
   * @param AL::ALVideoDeviceProxy        video
   * @param AL::ALPhotoCaptureProxy       photo
   * @param AL::ALVideoRecorderProxy      recorder
   * @param bool                          top
   * return bool                          (!top)
  **/
  bool selectCamera(AL::ALVideoDeviceProxy video, AL::ALPhotoCaptureProxy photo, AL::ALVideoRecorderProxy recorder, bool top);

  ///***************************************************************************
  /**             takePicture
   * Description: Capture the current NAO camera image and save it in NAO memory.
   * @param AL::ALPhotoCaptureProxy       photo
   * @param string                        fileName
   * return void
  **/
  void takePicture(AL::ALPhotoCaptureProxy photo, string fileName);

  ///***************************************************************************
  /**             recordVideo
   * Description: Starts/Stops recording a video using NAO camera and store it
   * in it's memory.
   * @param AL::ALVideoRecorderProxy      recorder
   * @param string                        fileName
   * return bool                          (!startRec)
  **/
  bool recordVideo(AL::ALVideoRecorderProxy recorder, string fileName, bool startRec);

  ///***************************************************************************
  /**             moveArms
   * Description: Move both NAO arms up (+90 [deg]) or down (-90 [deg]).
   * @param AL::ALMotionProxy       motion
   * return bool                    (!up)
  **/
  bool moveArms(AL::ALMotionProxy motion, bool up);

  ///***************************************************************************
  /**             reachObject
   * Description:  Move both NAO arms to reach an object at y=0 [deg].
   * @param AL::ALMotionProxy       motion
   * return void
  **/
  void reachObject(AL::ALMotionProxy motion);

};
#endif
