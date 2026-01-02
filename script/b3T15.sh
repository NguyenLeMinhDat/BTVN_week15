#!/bin/bash

if [ ! -d "build" ]; then
    mkdir build
fi
g++ ./src/bai3Tuan14-15.cpp -o ./build/bai3Tuan14-15
./build/bai3Tuan14-15