# Copyright (c) 2011 Aldebaran Robotics. All Rights Reserved.

cmake_minimum_required(VERSION 2.6.4 FATAL_ERROR)
# Give a name to the project.
project(Puppet)

# This include enable you to use qibuild framework
find_package(qibuild)

# Create an executable named Puppet,
# with the source file : Puppet.cpp
qi_create_bin(Puppet Puppet.cpp TaskLib.cpp TaskLib.h ../../../CommLib/Sockets.cpp ../../../CommLib/Sockets.h)

# Tell CMake that Puppet depends on ALCOMMON and ALPROXIES
# This will set the libraries to link Puppet with,
# the include paths, and so on
qi_use_lib(Puppet ALCOMMON ALPROXIES)
