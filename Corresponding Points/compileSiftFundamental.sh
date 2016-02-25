#!/bin/bash
g++ -std=c++11 -lstdc++ -O3 sift+fundamental.cpp `pkg-config --libs opencv` -o SiftFundamental.app