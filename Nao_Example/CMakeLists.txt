##
# Copyright (c) 2011 Aldebaran Robotics. All Rights Reserved.

cmake_minimum_required(VERSION 2.6.4 FATAL_ERROR)
# Give a name to the project.
project(sayhelloworld)

# This include enable you to use qibuild framework
find_package(qibuild)

#qi_create_lib(LEAP Leap.h LeapMath.h libLeap.so)

# Create an executable named sayhelloworld,
# with the source file : sayhelloworld.cpp
qi_create_bin(sayhelloworld sayhelloworld.cpp sockets.cpp Sockets.h)

# Tell CMake that sayhelloworld depends on ALCOMMON and ALPROXIES
# This will set the libraries to link sayhelloworld with,
# the include paths, and so on
qi_use_lib(sayhelloworld ALCOMMON ALPROXIES)
#qi_use_lib(sayhelloworld ALCOMMON ALPROXIES LEAP)
