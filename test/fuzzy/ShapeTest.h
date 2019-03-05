#ifndef LOGIQUEFLOUE_SHAPETEST_H
#define LOGIQUEFLOUE_SHAPETEST_H

#include <cppunit/extensions/HelperMacros.h>

#include "Shape.h"

using namespace fuzzy;

class ShapeTest : public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE(ShapeTest);
        CPPUNIT_TEST(testAddPoint);
    CPPUNIT_TEST_SUITE_END();
public:
    void testAddPoint();
};


#endif //LOGIQUEFLOUE_SHAPETEST_H
