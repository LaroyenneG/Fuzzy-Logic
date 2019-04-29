#ifndef LOGIQUEFLOUE_PHYSICOBJECT2DTEST_H
#define LOGIQUEFLOUE_PHYSICOBJECT2DTEST_H

#include <cppunit/extensions/HelperMacros.h>

#include "PhysicObject2D.h"

using namespace model;

class PhysicObject2DTest : public CppUnit::TestFixture {

CPPUNIT_TEST_SUITE(PhysicObject2DTest);
        CPPUNIT_TEST(testCircleSolver);
        CPPUNIT_TEST(testCircleSolverWithBigCircle);
        CPPUNIT_TEST(testEstimateOrdinateValue);
    CPPUNIT_TEST_SUITE_END();

public:
    void testCircleSolver();

    void testCircleSolverWithBigCircle();

    void testEstimateOrdinateValue();
};


#endif //LOGIQUEFLOUE_PHYSICOBJECT2DTEST_H
