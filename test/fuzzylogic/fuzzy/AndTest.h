#ifndef LOGIQUEFLOUE_ANDTEST_H
#define LOGIQUEFLOUE_ANDTEST_H

#include <cppunit/extensions/HelperMacros.h>

#include "AndMin.h"
#include "AndMult.h"
#include "AndTest.h"
#include "ValueModel.h"

using namespace fuzzylogic::fuzzy;
using namespace fuzzylogic::core;


class AndTest : public CppUnit::TestFixture {

CPPUNIT_TEST_SUITE(AndTest);
        CPPUNIT_TEST(testAndMin);
        CPPUNIT_TEST(testAndMult);
    CPPUNIT_TEST_SUITE_END();

public:
    void testAndMin();

    void testAndMult();
};


#endif //LOGIQUEFLOUE_ANDTEST_H
