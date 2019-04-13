
#ifndef LOGIQUEFLOUE_DEFUZZTEST_H
#define LOGIQUEFLOUE_DEFUZZTEST_H

#include <cppunit/extensions/HelperMacros.h>

#include "CogDefuzz.h"
#include "IsTriangle.h"
#include "UnaryExpressionModel.h"
#include "SugenoDefuzz.h"
#include "SugenoConclusion.h"

using namespace fuzzylogic::fuzzy;
using namespace fuzzylogic::core;

class DefuzzTest : public CppUnit::TestFixture {

CPPUNIT_TEST_SUITE(DefuzzTest);
        CPPUNIT_TEST(testCogDefuzz);
        CPPUNIT_TEST(testSugenoDefuzz);
        CPPUNIT_TEST(testSugenoConclusion);
    CPPUNIT_TEST_SUITE_END();

public:
    void testCogDefuzz();

    void testSugenoDefuzz();

    void testSugenoConclusion();
};


#endif //LOGIQUEFLOUE_DEFUZZTEST_H
