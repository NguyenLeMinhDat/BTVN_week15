#!/bin/bash

if [ ! -d "build" ]; then
    mkdir build
fi
g++ ./src/bai1-2Tuan14-15.cpp -o ./build/bai1-2Tuan14-15
./build/bai1-2Tuan14-15