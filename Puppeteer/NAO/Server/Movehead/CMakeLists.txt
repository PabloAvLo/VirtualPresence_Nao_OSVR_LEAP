## USING Movehead on 2017
# Copyright (c) 2011 Aldebaran Robotics. All Rights Reserved.

cmake_minimum_required(VERSION 2.6.4 FATAL_ERROR)

# Give a name to the project.
project(Movehead)

# This include enable you to use our CMake framework
find_package(qibuild)

# Create an executable named Movehead,
# with the source file : movehead.cpp
qi_create_bin(Movehead movehead.cpp ../../../CommLib/Sockets.cpp ../../../CommLib/Sockets.h)

# Tell CMake that Movehead depends on ALCOMMON and ALPROXIES
# This will set the libraries to link Movehead with the include paths, and so on
qi_use_lib(Movehead ALCOMMON ALPROXIES)
