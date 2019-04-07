#ifndef LOGIQUEFLOUE_AGGTEST_H
#define LOGIQUEFLOUE_AGGTEST_H

#include <cppunit/extensions/HelperMacros.h>


#include "AggMax.h"
#include "AggPlus.h"
#include "ValueModel.h"

using namespace core;
using namespace fuzzy;


class AggTest : public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE(AggTest);
        CPPUNIT_TEST(testAggMax);
        CPPUNIT_TEST(testAggPlus);
    CPPUNIT_TEST_SUITE_END();
public:
    void testAggMax();

    void testAggPlus();

};


#endif //LOGIQUEFLOUE_AGGTEST_H
