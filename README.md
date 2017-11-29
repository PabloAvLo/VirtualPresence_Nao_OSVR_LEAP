# VirtualPresence_Nao_OSVR_LEAP
# Release

This is an stable version of Puppeteer project where the main objective is to create a telepresence system, integrating devices in order to provide the user a real time experience of a remote place.

The system is teleoperator robot is NAO, an humanoid robot with several functionalities which it's main porpuse in this project is do simple actions commanded by the operator thru a Leap Motion. 
Leap Motion is a hand tracker that doesn't need additional tools as gloves or joysticks to work. This device will recognize human manual gestures to send instructions to NAO through TCP Sockets.
Finally, the Virtual Reality glasses OSVR HDK are used to bring the user the images of the remote enviroment, allowing to move NAO head by retrieving orientation data of the OSVR.

The motivation to develop Puppeteer is to create a tool for Limited movement people as elder and people with movement disabilities. In order to start and encourage investigation in this topic.

The project is mostly developed using C++ on Linux in PRIS-Lab of the Universidad de Costa Rica.  
