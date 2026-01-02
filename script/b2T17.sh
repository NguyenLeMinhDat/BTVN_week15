#!/bin/bash

if [ ! -d "build" ]; then
    mkdir build
fi
g++ ./src/bai2Tuan17.cpp -o ./build/bai2Tuan17
./build/bai2Tuan17