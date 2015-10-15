/*
 * File:   newtestclass.h
 * Author: Vareto
 *
 * Created on Jan 22, 2015, 4:31:14 PM
 */

#ifndef NEWTESTCLASS_H
#define	NEWTESTCLASS_H

#include <cppunit/extensions/HelperMacros.h>

class newtestclass : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(newtestclass);

    CPPUNIT_TEST(testAscending);
    CPPUNIT_TEST(testBubble);
    CPPUNIT_TEST(testDescending);
    CPPUNIT_TEST(testSwap);

    CPPUNIT_TEST_SUITE_END();

public:
    newtestclass();
    virtual ~newtestclass();
    void setUp();
    void tearDown();

private:
    void testAscending();
    void testBubble();
    void testDescending();
    void testSwap();

};

#endif	/* NEWTESTCLASS_H */

