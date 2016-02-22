#!/bin/bash
g++ -std=c++11 -lstdc++ -O3 fundamental.cpp `pkg-config --libs opencv` -o Fundamental.app