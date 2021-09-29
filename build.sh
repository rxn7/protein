cd protein
make

sudo cp ./bin/linux/libprotein.so /usr/lib -r

[ ! -d "/usr/include/pn" ] && sudo mkdir /usr/include/pn
sudo cp ./include/* /usr/include/pn -r

cd ..