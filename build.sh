#!/bin/bash

./insertshaders.sh
cd pn 
make

sudo cp ./bin/linux/libprotein.a /usr/lib -r

[ ! -d "/usr/include/pn" ] && sudo mkdir /usr/include/pn
sudo cp ./include/* /usr/include/pn -r

cd ..


if [ $# -eq 0 ]
	then
		exit
else
	cd examples/$1
	./run.sh
	cd ../..
fi
