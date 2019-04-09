#ifndef LOGIQUEFLOUE_BINARYEXPRESSIONMODELTEST_H
#define LOGIQUEFLOUE_BINARYEXPRESSIONMODELTEST_H

#include <cppunit/extensions/HelperMacros.h>

#include "AndMin.h"
#include "OrMax.h"
#include "BinaryExpressionModel.h"

using namespace core;
using namespace fuzzy;

class BinaryExpressionModelTest : public CppUnit::TestFixture {

CPPUNIT_TEST_SUITE(BinaryExpressionModelTest);
        CPPUNIT_TEST(testOperandsNull);
        CPPUNIT_TEST(testOperatorNull);
    CPPUNIT_TEST_SUITE_END();

public:
    void testOperandsNull();

    void testOperatorNull();
};


#endif //LOGIQUEFLOUE_BINARYEXPRESSIONMODELTEST_H
