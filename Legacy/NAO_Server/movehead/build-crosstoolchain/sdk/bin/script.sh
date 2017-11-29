cd ../../../
qibuild configure -c crosstoolchain
qibuild make -c crosstoolchain
cd build-crosstoolchain/sdk/bin/
scp setAngles nao@10.0.1.122:/home/nao
ssh nao@10.0.1.122
