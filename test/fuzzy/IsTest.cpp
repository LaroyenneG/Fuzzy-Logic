
#include "IsTest.h"

void IsTest::testIsTriangle() {

    IsTriangle<double> isTriangle(0.1, 0.6, 0.7);

    CPPUNIT_ASSERT_EQUAL(0.1, isTriangle.getMin());
    CPPUNIT_ASSERT_EQUAL(0.6, isTriangle.getMid());
    CPPUNIT_ASSERT_EQUAL(0.7, isTriangle.getMax());
}
