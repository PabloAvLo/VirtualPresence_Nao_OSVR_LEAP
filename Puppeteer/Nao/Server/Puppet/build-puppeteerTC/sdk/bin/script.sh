#!/bin/bash

cd ../../../
qibuild configure -c puppeteerTC
qibuild make -c puppeteerTC
cd build-puppeteerTC/sdk/bin/
scp Puppet nao@$1:/home/nao
#ssh nao@$1
sshpass -pnao ssh -tt nao@$1 ./Puppet
#exit
