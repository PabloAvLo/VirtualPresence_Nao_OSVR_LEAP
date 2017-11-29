# Puppeteer 
A telepresence system using NAO robot, Leap Motion hand tracker and OSVR HDK glasses. 

# Synopsis
Puppeteer project main objective is to create a telepresence system, integrating devices in order to provide the user a real time experience of a remote place.

The system teleoperator robot is NAO, an humanoid robot with several functionalities which its main purpose in this project is perform simple actions controlled by the operator thru a Leap Motion. 

Leap Motion is a hand tracker that doesn't need additional tools as gloves or joysticks to work. This device will recognize human manual gestures to send instructions to NAO through TCP Sockets.

Finally, the Virtual Reality glasses OSVR HDK are used to bring the user the images of the remote enviroment, allowing to move the NAO head by retrieving orientation data of the OSVR.
The project is mostly developed using C++ on Linux. 

# Motivation
The motivation to develop Puppeteer is to create a tool for Limited movement people as elder and people with movement disabilities. In order to start and encourage investigation on this topic.

# Author
Pablo Avila at PRIS-Lab as Final Project of Electrical Enginnering, Universidad de Costa Rica.  
