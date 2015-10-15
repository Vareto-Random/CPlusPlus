/*
 * File:   newtestclass.cpp
 * Author: Vareto
 *
 * Created on Jan 22, 2015, 4:31:14 PM
 */

#include "newtestclass.h"


CPPUNIT_TEST_SUITE_REGISTRATION(newtestclass);

newtestclass::newtestclass() {
}

newtestclass::~newtestclass() {
}

void newtestclass::setUp() {
}

void newtestclass::tearDown() {
}

bool ascending(const int, const int);

void newtestclass::testAscending() {
    const int p0;
    const int p1;
    bool result = ascending(p0, p1);
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

void bubble(int[], const int, bool(*)(int, int));

void newtestclass::testBubble() {
    int* p0;
    const int p1;
    bool(*)(int, int) p2;
    bubble(p0, p1, p2);
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

bool descending(const int, const int);

void newtestclass::testDescending() {
    const int p0;
    const int p1;
    bool result = descending(p0, p1);
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

void swap(int* const element1Ptr, int* const element2Ptr);

void newtestclass::testSwap() {
    int* const element1Ptr;
    int* const element2Ptr;
    swap(element1Ptr, element2Ptr);
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

