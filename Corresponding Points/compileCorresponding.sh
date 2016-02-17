#!/bin/bash
g++ -std=c++11 -lstdc++ -O3 corresponding.cpp `pkg-config --libs opencv` -o Executable