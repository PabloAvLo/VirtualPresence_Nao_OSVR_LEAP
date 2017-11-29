#!/bin/bash
##******************************************************************************
#                           Universidad de Costa Rica
#                  						   Proyecto Eléctrico
#                                  II Ciclo 2017
#
#                  					      make.sh: Puppet
#
# Author: Pablo Avila B30724
#
# Description:
# As any Naoqi program, is compile using qibuild with the Cross-Platform
# ToolChain provide by Aldebaran. This script, compiles 'Puppet.cpp' and copy
# the executable to the NAO using ssh, and run it inmediatly (optional).
#
# RUN:
#  ./make.sh <NAO_IP>
#*******************************************************************************

qibuild configure -c puppeteerTC
qibuild make -c puppeteerTC
cd build-puppeteerTC/sdk/bin/
scp Puppet nao@$1:/home/nao
#ssh nao@$1
#sshpass -pnao ssh -tt nao@$1 ./Puppet
#exit
