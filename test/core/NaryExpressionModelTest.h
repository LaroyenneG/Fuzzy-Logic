#ifndef LOGIQUEFLOUE_NARYEXPRESSIONMODELTEST_H
#define LOGIQUEFLOUE_NARYEXPRESSIONMODELTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <NaryExpressionModel.h>


using namespace core;

class NaryExpressionModelTest : public CppUnit::TestFixture {

CPPUNIT_TEST_SUITE(NaryExpressionModelTest);
            CPPUNIT_TEST(testOperandsNull);
            CPPUNIT_TEST(testOperatorNull);
    CPPUNIT_TEST_SUITE_END();

public:
    void testOperandsNull();

    void testOperatorNull();
};


#endif //LOGIQUEFLOUE_NARYEXPRESSIONMODELTEST_H
