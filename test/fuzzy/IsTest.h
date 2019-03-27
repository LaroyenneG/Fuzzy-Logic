#ifndef LOGIQUEFLOUE_ISTRIANGLETEST_H
#define LOGIQUEFLOUE_ISTRIANGLETEST_H

#include <cppunit/extensions/HelperMacros.h>

#include "IsTriangle.h"
#include "isTrapezoid.h"
#include "IsSingleton.h"
#include "IsRampRight.h"
#include "IsRampLeft.h"
#include "IsBell.h"
#include "ValueModel.h"

using namespace fuzzy;
using namespace core;

class IsTest : public CppUnit::TestFixture {

CPPUNIT_TEST_SUITE(IsTest);
        CPPUNIT_TEST(testIsTriangle);
            CPPUNIT_TEST(testIsTrapezoid);
        CPPUNIT_TEST(testIsRampLeft);
        CPPUNIT_TEST(testIsSingleton);
        CPPUNIT_TEST(testIsRampRight);
            CPPUNIT_TEST(testIsBell);
    CPPUNIT_TEST_SUITE_END();
public:
    void testIsTriangle();

    void testIsTrapezoid();

    void testIsSingleton();

    void testIsRampRight();

    void testIsRampLeft();

    void testIsBell();
};


#endif //LOGIQUEFLOUE_ISTRIANGLETEST_H
