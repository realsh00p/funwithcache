### Linux

Project should run seamlessly in docker.


### Mac OS build instructions:

Install Docker desktop

Open Docker desktop -> Dev environments -> create -> Enter github repo
https://github.com/realsh00p/funwithcache
continue -> open in vs code

In terminal:
cd docker
./docker_build.sh

cd ..

Create a build directory and build
mkdir build-manual
cd build-manual
cmake ..
make



Note:(If cmake is not installed or cmake version requirements were not met, follow below steps)

sudo apt install build-essential libssl-dev
wget https://github.com/Kitware/CMake/releases/download/v3.20.2/cmake-3.20.2.tar.gz
tar -zxvf cmake-3.20.2.tar.gz
cd cmake-3.20.2
./bootstrap
make
sudo make install

if boost library is missing in the make process:
sudo apt-get install libboost-all-dev

if protobuf library is missing:
sudo apt-get install protobuf-compiler
