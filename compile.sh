#!/bin/bash
#g++ -Wall -Wextra src/*.cpp -g -o build/prog.exe -std=c++11 -lSDL2 -lSDL2_image
g++ src/*.cpp src/Engine/*.cpp -g -o build/linux.exe -std=c++17 -lSDL2 -lSDL2_image