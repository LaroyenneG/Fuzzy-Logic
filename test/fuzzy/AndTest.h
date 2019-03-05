#ifndef LOGIQUEFLOUE_ANDTEST_H
#define LOGIQUEFLOUE_ANDTEST_H

#include <cppunit/extensions/HelperMacros.h>

#include "AndMin.h"
#include "AndTest.h"
#include "ValueModel.h"

using namespace fuzzy;
using namespace core;


class AndTest : public CppUnit::TestFixture {

CPPUNIT_TEST_SUITE(AndTest);
        CPPUNIT_TEST(testAndMin);
    CPPUNIT_TEST_SUITE_END();

public:
    void testAndMin();
};


#endif //LOGIQUEFLOUE_ANDTEST_H
