#!/bin/bash
g++ -std=c++11 -lstdc++ -O3 homography.cpp `pkg-config --libs opencv` -o Homography.app