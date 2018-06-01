#!/bin/sh
echo "Making directories for compilation..."
mkdir -p ./obj/dpGPG-pendrive-generator
mkdir ./obj/dpGPG-daemon
mkdir ./bin
echo "Compiling dpGPG-pendrive-generator..."
g++ -Wall -fexceptions -O2 -std=c++11  -c ./src/dpGPG-pendrive-generator/highlevel.cpp -o ./obj/dpGPG-pendrive-generator/highlevel.o
g++ -Wall -fexceptions -O2 -std=c++11  -c ./src/dpGPG-pendrive-generator/main.cpp -o ./obj/dpGPG-pendrive-generator/main.o
g++ -Wall -fexceptions -O2 -std=c++11  -c ./src/dpGPG-pendrive-generator/partition.cpp -o ./obj/dpGPG-pendrive-generator/partition.o
g++ -o ./bin/dpGPG-pendrive-generator ./obj/dpGPG-pendrive-generator/highlevel.o ./obj/dpGPG-pendrive-generator/main.o ./obj/dpGPG-pendrive-generator/partition.o -s
echo "Compiling dpGPG-daemon..."
g++ -Wall -fexceptions -O2 -std=c++11  -c ./src/dpGPG-daemon/main.cpp -o ./obj/dpGPG-daemon/main.o
g++ -Wall -fexceptions -O2 -std=c++11 -c ./src/dpGPG-daemon/daemonskeleton.cpp -o ./obj/dpGPG-daemon/daemonskeleton.o
g++ -o ./bin/dpGPG-daemon ./obj/dpGPG-daemon/daemonskeleton.o ./obj/dpGPG-daemon/main.o -s
echo "Work done! See ./bin for binaries!"
