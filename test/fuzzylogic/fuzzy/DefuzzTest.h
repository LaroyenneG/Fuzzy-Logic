
#ifndef LOGIQUEFLOUE_DEFUZZTEST_H
#define LOGIQUEFLOUE_DEFUZZTEST_H

#include <cppunit/extensions/HelperMacros.h>

#include "CogDefuzz.h"

using namespace fuzzylogic::fuzzy;
using namespace fuzzylogic::core;

class DefuzzTest : public CppUnit::TestFixture {

CPPUNIT_TEST_SUITE(DefuzzTest);
        CPPUNIT_TEST(testCogDefuzz);
    CPPUNIT_TEST_SUITE_END();

public:
    void testCogDefuzz();
};


#endif //LOGIQUEFLOUE_DEFUZZTEST_H
