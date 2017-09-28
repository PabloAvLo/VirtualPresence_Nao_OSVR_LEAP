## USING SET_ANGLES on 15 August 2017


# Copyright (c) 2011 Aldebaran Robotics. All Rights Reserved.

cmake_minimum_required(VERSION 2.6.4 FATAL_ERROR)
# Give a name to the project.
project(movehead)
# This include enable you to use our CMake framework
find_package(qibuild)

# Create an executable named movehead,
# with the source file : movehead.cpp
#qi_create_bin(movehead movehead.cpp)

# Create an executable named setAngles,
# with the source file : almotion_setangles.cpp
qi_create_bin(setAngles almotion_setangles.cpp sockets.cpp Sockets.h)

# Tell CMake that movehead depends on ALCOMMON and ALPROXIES
# This will set the libraries to link movehead with,
# the include paths, and so on
#qi_use_lib(movehead ALCOMMON ALPROXIES)
qi_use_lib(setAngles ALCOMMON ALPROXIES)
