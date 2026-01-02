#!/bin/bash

if [ ! -d "build" ]; then
    mkdir build
fi
g++ ./src/bai1Tuan17.cpp -o ./build/bai1Tuan17
./build/bai1Tuan17