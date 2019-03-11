#ifndef LOGIQUEFLOUE_ISTRIANGLETEST_H
#define LOGIQUEFLOUE_ISTRIANGLETEST_H

#include <cppunit/extensions/HelperMacros.h>

#include "IsTriangle.h"

using namespace fuzzy;
using namespace core;

class IsTest : public CppUnit::TestFixture {

CPPUNIT_TEST_SUITE(IsTest);
        CPPUNIT_TEST(testIsTriangle);
    CPPUNIT_TEST_SUITE_END();
public:
    void testIsTriangle();
};


#endif //LOGIQUEFLOUE_ISTRIANGLETEST_H
