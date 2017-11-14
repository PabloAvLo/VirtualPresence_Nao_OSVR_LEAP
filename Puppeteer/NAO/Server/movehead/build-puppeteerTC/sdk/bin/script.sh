#!/bin/bash

cd ../../../
qibuild configure -c puppeteerTC
qibuild make -c puppeteerTC
cd build-puppeteerTC/sdk/bin/
scp setAngles nao@$1:/home/nao
#ssh nao@$1
#sshpass -pnao ssh -tt nao@$1 ./setAngles <IPdelNAO>
#exit
