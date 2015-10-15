/* 
 * File:   newsimpletest.cpp
 * Author: Vareto
 *
 * Created on Jan 22, 2015, 4:29:02 PM
 */

#include <stdlib.h>
#include <iostream>

/*
 * Simple C++ Test Suite
 */

bool ascending(const int, const int);

void testAscending() {
    const int p0;
    const int p1;
    bool result = ascending(p0, p1);
    if (true /*check result*/) {
        std::cout << "%TEST_FAILED% time=0 testname=testAscending (newsimpletest) message=error message sample" << std::endl;
    }
}

void bubble(int[], const int, bool(*)(int, int));

void testBubble() {
    int* p0;
    const int p1;
    bool(*)(int, int) p2;
    bubble(p0, p1, p2);
    if (true /*check result*/) {
        std::cout << "%TEST_FAILED% time=0 testname=testBubble (newsimpletest) message=error message sample" << std::endl;
    }
}

bool descending(const int, const int);

void testDescending() {
    const int p0;
    const int p1;
    bool result = descending(p0, p1);
    if (true /*check result*/) {
        std::cout << "%TEST_FAILED% time=0 testname=testDescending (newsimpletest) message=error message sample" << std::endl;
    }
}

void swap(int* const element1Ptr, int* const element2Ptr);

void testSwap() {
    int* const element1Ptr;
    int* const element2Ptr;
    swap(element1Ptr, element2Ptr);
    if (true /*check result*/) {
        std::cout << "%TEST_FAILED% time=0 testname=testSwap (newsimpletest) message=error message sample" << std::endl;
    }
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% newsimpletest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testAscending (newsimpletest)" << std::endl;
    testAscending();
    std::cout << "%TEST_FINISHED% time=0 testAscending (newsimpletest)" << std::endl;

    std::cout << "%TEST_STARTED% testBubble (newsimpletest)" << std::endl;
    testBubble();
    std::cout << "%TEST_FINISHED% time=0 testBubble (newsimpletest)" << std::endl;

    std::cout << "%TEST_STARTED% testDescending (newsimpletest)" << std::endl;
    testDescending();
    std::cout << "%TEST_FINISHED% time=0 testDescending (newsimpletest)" << std::endl;

    std::cout << "%TEST_STARTED% testSwap (newsimpletest)" << std::endl;
    testSwap();
    std::cout << "%TEST_FINISHED% time=0 testSwap (newsimpletest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

